//
// LedScrollBoard V1.0
//  
// ESP8266 firmware and web inteface for scrolltext / pixel editor  
// based on the WiFi-enabled Led Workshop by Rui (Ray) Wang - thanks to Ray !!
// visit: rayshobby.net/?p=10963   watch: https://www.youtube.com/watch?v=ZKuIWDocIiM
// 
// adapted for AI-Thinker ESP12 boards + WS2812 led pixels by chris veigl / chris@shifz.org
// additional features: 
// DNS/captive portal, big scrollboard size, icon animations, brightness & scroll speed control
//
// select NodeMCU 0.9 (ESP12-Module) in tools->board
// connect led pixels to GPIO3 (RX-Pin ! used for DMA-supported output by NeoPixelBus lilbrary) 
// connect a potentiometer for max brightness control to A0 
// connect an led to Pin5 (D1) to indicate main loop operation
// connect a momentary switch to Pin4 (D2) - when pressed at startup/reset, captive portal/DNS is not used
//

#include <FS.h>
#include <stdio.h>
#include <string.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <NeoPixelBus.h>
#include <ArduinoJson.h>
#include "font5x7.h"

#define BIG_BOARD
// #define UNIQUE_AP_NAME    // uncomment this if you want to use multiple boards

#define PIN_BUTTON  4    // marked as D2 on AI-Thinker ESP12 board !
#define PIN_LED     5    // marked as D1 on AI-Thinker ESP12 board !

#ifdef BIG_BOARD
  #define NUM_COLUMNS 41    // big board hast 41 columns
  #define ICON_OFFSET 44
#else
  #define NUM_COLUMNS 8     // small demo board has 8 columns
  #define ICON_OFFSET 6
#endif

#define NUM_LEDS    NUM_COLUMNS*7   // 7 leds (rows) per column

#define MAX_ICONS 10
#define ICON_PIXELS 35   // number of LED pixels per icon (5 x 7)

#define BG_MODE_FILL    0   // background modes
#define BG_MODE_RAINBOW 1

#define STRUCT_LEN 30   //max size of the struct for the posts

// Neopixel object
// this uses GPIO3 (marked as RX on the AT-Thinker ESP12 board)
// this is a hardware restriction because of DMA access, see NeoPixelBus documentation!
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> leds(NUM_LEDS);

const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress         apIP(192, 168, 4, 1);   // Private network for server

ESP8266WebServer server(80);  // create web server at HTTP port 80
DNSServer        dnsServer;   // create the DNS object
byte serve_dns_requests=1;    // shall we react (captive portal)

byte bg_mode = BG_MODE_RAINBOW;
byte bg_mode_new = BG_MODE_RAINBOW;
byte bg_brightness = 30;
byte bg_brightness_new = 30;
uint16_t bg_wait = 20;
uint16_t bg_wait_new = 20;
uint32_t bg_color = 0x0000a0;
uint32_t bg_color_new = 0x0000a0;

String scrolltext = "     hello!"; //  this is the open led billboard.    to post your message: connect to WiFi LedScrollBoard !
String scrolltext_new = "     hello!";
byte scrollindex = 0;
byte scroll_mode=1;
byte scroll_brightness = 200;
byte scroll_brightness_new = 200;
uint16_t scrollwait = 40;
uint16_t scrollwait_new = 40;
uint32_t scrollcolor = 0xa0a000;
uint32_t scrollcolor_new = 0xa0a000;

uint32_t icons[MAX_ICONS][ICON_PIXELS+1] = { 0 }; // icon buffer. this holds up to 10 icons
uint16_t anim_wait = 100;
uint16_t icon_pos=0;
uint16_t preview_acticon=0;
byte act_icon=0,act_anim=0;
byte icon_brightness = 200;

byte pixelupdate =1;
byte brightness = 80;         // default overall brightness
byte get_brightness_web = 0;  // default: set brightness from adc/potentiomenter
uint32_t pixels[NUM_LEDS];    // pixel buffer. this buffer allows you to set arbitrary

                              // brightness without destroying the original color values
// Forward declare functions
String get_ap_name();
void button_handler();
void on_status();
void on_change_color();
void on_background();
void on_scroll();
void on_icon();
void on_homepage();
void on_admin();
void on_error();
void show_leds();
void background_rainbow();
void update_background();
void update_scrolltext();
void update_icons();
void load_iconPixels(byte);
uint32_t adjust_brightness(uint32_t, byte);
bool handleFileRead(String);
String formatBytes(size_t);
void setToStruct();
void deletePost();
void nextPost();
void nextAdminPost();
void setDefaultPost();

uint32_t counter=0;
byte ledstate=0;

// The variable below is modified by interrupt service routine
// so declare it as volatile
volatile boolean button_clicked = false;
boolean load_admin_space = false;

//variables from admin interface
uint16_t modules = 1;
String user_ap_name = "MyLedScrollboard";
String default_post1 = "     DefaultPost1";
String default_post2 = "     DefaultPost2";
String default_post3 = "     DefaultPost3";
String password = "Admin1234";

struct Post{
  String scrolltext;
  byte scrollBrightness;
  uint16_t scrollWait;
  uint32_t scrollColor;
  byte bgMode;
  byte bgBrightness;
  uint16_t bgWait;
  uint32_t bgColor;
};

struct Post userposts[STRUCT_LEN];
struct Post adminposts[3];

int userstructelemnts = 0;
int adminstructelemnts = 2;
int userstructcounter = 0;
int adminstructcounter = 0;
boolean updateStruct = false;
int countpostsround = 1;


void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial attach
  //  Serial.setDebugOutput(true);
  //  Serial.println("\nESP8266 hotspot ready !");

  // Set pin mode
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LED,    OUTPUT);

  // Show files in FS
  Serial.printf("\n\nHi ! I have these files in my folder:\n");
  SPIFFS.begin();
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    Serial.printf("\n");
  }

  boolean successRead = read_config();
  setDefaultPost();

  // Set WiFi SSID
  //String ap_name = get_ap_name();
  WiFi.persistent(false);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  //WiFi.softAP(user_ap_name.c_str());

  // press button on startup if you do not want a captive portal
  if (digitalRead(PIN_BUTTON) == LOW) {
     dnsServer.start(DNS_PORT, "*", apIP);
     serve_dns_requests=1;
     bg_mode = BG_MODE_FILL;
     byte passwd_len = password.length();
     char pw[passwd_len+1];
     password.toCharArray(pw,(passwd_len+1));
     Serial.println(password);
     Serial.println(pw);
     WiFi.softAP(user_ap_name.c_str(),pw);
     load_admin_space=true;
  } else {
     dnsServer.start(DNS_PORT, "*", apIP);
     serve_dns_requests=1;
     bg_mode = BG_MODE_RAINBOW;
     WiFi.softAP(user_ap_name.c_str());
     load_admin_space=false;
  }

  // WiFi.printDiag(Serial);
  // IPAddress myIP = WiFi.softAPIP();
  // Serial.print("AP IP address: ");
  // Serial.println(myIP);

  // Set server callback functions
  server.on("/",   on_homepage);
  server.on("/admin/index.html", on_error);
  server.on("/js", on_status);
  server.on("/cc", on_change_color);
  server.on("/bg", on_background);
  server.on("/ic", on_icon);
  server.on("/sc", on_scroll);
  server.on("/as", on_admin);
  //server.onNotFound(on_homepage);
  server.onNotFound([](){               // try to serve another request (file?)
    if(!handleFileRead(server.uri()))
      on_homepage();                      // default reply: the index.html !
  });
  server.begin();



     
  // Set button handler
  attachInterrupt(PIN_BUTTON, button_handler, FALLING);


  
  // Initialize LEDs
  leds.Begin();
  leds.Show();
  setToStruct();
}

void loop() {
  
  if (serve_dns_requests)
    dnsServer.processNextRequest();

  server.handleClient();
  ledstate=!ledstate;
  digitalWrite(PIN_LED,ledstate);

  if(button_clicked) {
    bg_mode ++;  // upon button click, change background mode
    button_clicked = false;
    pixelupdate=1;
  }

  update_background();
  update_scrolltext();
  update_icons ();
  
  if(updateStruct){
    setToStruct();
    updateStruct = false;
  }
  
  if (pixelupdate) {
    pixelupdate=0;
    show_leds();
    
  }

  if ((!(counter % 100)) && (!get_brightness_web)) {
    byte new_brightness=analogRead(A0)>>2;
    if (brightness!=new_brightness) {
      Serial.print("set brightness to "); 
      Serial.println(new_brightness);
    }
    brightness=new_brightness;
  }
  counter++;   // global counter for timing activities
  delay(2);

  // maybe add later: emergency handling / sw-"watchdog"
  // see: https://github.com/esp8266/Arduino/issues/1532
  // seems not necessary as stability improved afer switching to NeopixelBus library !

  // maybe add later: 
  // store settings / scroll + animation patterns to eeprom via admin command
}

/* ----------------
 *  Helper functions 
 * ---------------- */


void load_iconPixels(byte num) {
  String val = server.arg("pixels");
  for(uint16_t i=0;i<ICON_PIXELS;i++) {
    // every pixel color is 6 bytes storing the hex value
    // pixels are specified in row-major order
    // here we need to flip it to column-major order to 
    // match the physical connection of the leds
    byte r=i/5, c=i%5;
    if (!(c%2)) r=6-r;   // reverse every second column !
    icons[num][c*7+r] = strtol(val.substring(i*6, i*6+6).c_str(), NULL, 16);
  }
}

char dec2hex(byte dec) {
  if(dec<10) return '0'+dec;
  else return 'A'+(dec-10);
}

// AP name is ESP_ following by 
// the last 6 bytes of MAC address
/*String get_ap_name() {
 static String ap_name = "BacLedScrollBoard";

 #ifdef UNIQUE_AP_NAME 
    byte mac[6];
    WiFi.macAddress(mac);
    for(byte i=3;i<6;i++) {
      ap_name += dec2hex((mac[i]>>4)&0x0F);
      ap_name += dec2hex(mac[i]&0x0F);
    }
  #endif 
  return ap_name;
}*/

void button_handler() {
  button_clicked = true;
}

uint32_t adjust_brightness(uint32_t c, byte brightness) {
  uint32_t r, g, b;
    r = (c>>16)& 0xFF;
    g = (c>>8)& 0xFF;
    b = c & 0xFF;
    r = r*brightness/255;
    g = g*brightness/255;
    b = b*brightness/255;
    return ((r<<16) + (g<<8) + b);
}

void show_leds() {
  for(int i=0;i<NUM_LEDS;i++) {
      leds.SetPixelColor(i, RgbColor(HtmlColor(adjust_brightness(pixels[i],brightness))));
  }
  
  leds.Show();
}


//----------------------------------------------------------------------
String getContentType(String filename){
  if(server.hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".svg")) return "image/svg+xml";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
//----------------------------------------------------------------------
bool handleFileRead(String path){
  Serial.println("handleFileRead: " + path);
  // if(path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(path)){
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    Serial.println("Sent bytes!");
    file.close();
    return true;
  }
  Serial.println("Send failed!");
  return false;
}


//format bytes
String formatBytes(size_t bytes){
  if (bytes < 1024){
    return String(bytes)+"B";
  } else if(bytes < (1024 * 1024)){
    return String(bytes/1024.0)+"KB";
  } else if(bytes < (1024 * 1024 * 1024)){
    return String(bytes/1024.0/1024.0)+"MB";
  } else {
    return String(bytes/1024.0/1024.0/1024.0)+"GB";
  }
}

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}






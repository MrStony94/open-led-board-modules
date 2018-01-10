// this returns device variables in JSON, e.g.
// {"pixels":xxxx,"blink":1}
void on_status() {
  String html = "";
  html += "{\"brightness\":";
  html += brightness;
  html += ",\"act_icon\":";
  html += act_icon;
  html += ",\"bg_brightness\":";
  html += bg_brightness;
  html += ",\"scroll_brightness\":";
  html += scroll_brightness;
  html += ",\"icon_brightness\":";
  html += icon_brightness;
  html += "}";
  server.send(200, "text/html", html);
}

uint16_t scale_wait(int16_t val) {
  int16_t v=35-val;   // the max position of the speed slider is 30
  if (v<3) v=3;
  if (v>10) v=10+(v-10)*(v-10)*2;  // waittime progresses by ^2
  return((uint16_t)v);
}

byte scale_brightness(byte val) {
  if (val>10) return(10+(val-10)*(val-10)/1.8);
  return(val);
}

void on_background() {
  if(server.hasArg("mode")) {
    bg_mode = server.arg("mode").toInt();
  }
  if(server.hasArg("wait")) {
    bg_wait = scale_wait(server.arg("wait").toInt());
  }
  if(server.hasArg("color")) {
    bg_color = strtol(server.arg("color").c_str(), NULL, 16);
  }
  if(server.hasArg("brightness")) {
    bg_brightness = scale_brightness(server.arg("brightness").toInt());
  }
  server.send(200, "text/html", "{\"result\":1}");
  pixelupdate=1;
}

void on_icon() {
  if(server.hasArg("icon")) {
    act_icon = server.arg("icon").toInt()-1;
    if (act_icon<0) act_icon=0;
    if (act_icon>=MAX_ICONS) act_icon=MAX_ICONS-1;
  }
  if(server.hasArg("anim")) {
    icons[act_icon][ICON_PIXELS]= server.arg("anim").toInt();
  }
  if(server.hasArg("wait")) {
    anim_wait = scale_wait(server.arg("wait").toInt());
  }
  if(server.hasArg("pixels")) {
       load_iconPixels(act_icon);
       preview_acticon=200;
  }
  if(server.hasArg("brightness")) {
    icon_brightness = scale_brightness(server.arg("brightness").toInt());
  }
  server.send(200, "text/html", "{\"result\":1}");
  pixelupdate=1;
}

void on_scroll() {
  int iconpos=0;
  if(server.hasArg("scrolltext")) {
    scrolltext = server.arg("scrolltext");
    scrolltext = " "+scrolltext;
    // check for icon in scrolltext
    while ((iconpos=scrolltext.indexOf('$',iconpos)) > -1)
    {
       uint8_t c =scrolltext[iconpos+1];
       if ((c>='1') && (c<='9')) {
          scrolltext[iconpos+1]= c-'0'+9;  // this will identify the icon number !
          scrolltext.remove(iconpos,1);
       } else iconpos++;
    }
    scrollindex = 0;
  }
  if(server.hasArg("wait")) {
    scrollwait = scale_wait(server.arg("wait").toInt());
  }
  if(server.hasArg("color")) {
    scrollcolor = strtol(server.arg("color").c_str(), NULL, 16);
  }
  if(server.hasArg("mode")) {
    scroll_mode = server.arg("mode").toInt();
  }
  if(server.hasArg("brightness")) {
    scroll_brightness = scale_brightness(server.arg("brightness").toInt());
  }
  server.send(200, "text/html", "{\"result\":1}");
  pixelupdate=1;
}

void on_change_color() {
  uint16_t i;
  if(server.hasArg("pixels")) {
       load_iconPixels(0);
  }
  if(server.hasArg("brightness")) {
    get_brightness_web=1;
    brightness = scale_brightness(server.arg("brightness").toInt());
  }
  server.send(200, "text/html", "{\"result\":1}");
  pixelupdate=1;
}

void on_admin(){
  if(server.hasArg("modules")){
    modules = server.arg("modules").toInt();
  }
  if(server.hasArg("wifiname")){
    ap_name=server.arg("wifiname");
  }
  if(server.hasArg("wifipassword")){
    //char* pass = server.arg("wifipassword");
    //byte pass_len = pass.length;
    //password = toCharArray(pass,pass_len);
  }
  if(server.hasArg("post")){
    post = server.arg("post");
  }
  boolean succes = writeConfig(modules, post);
}

uint32_t getRGBColor(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

uint32_t wheel(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return adjust_brightness(getRGBColor(255 - WheelPos * 3, 0, WheelPos * 3),bg_brightness);  
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return adjust_brightness(getRGBColor(0, WheelPos * 3, 255 - WheelPos * 3),bg_brightness);  }
  WheelPos -= 170;
  return adjust_brightness(getRGBColor(WheelPos * 3, 255 - WheelPos * 3, 0),bg_brightness);
}

void background_rainbow() {
  static byte idx = 0;

  if (!(counter%bg_wait)) { 
    idx++; 
    pixelupdate=1; 
  }

  for(int i=0;i<NUM_LEDS;i++) {
    pixels[i] = wheel((i+idx)&0xFF);
  }
}


void update_background()  {
  switch(bg_mode) {
    case BG_MODE_FILL:
      for(int i=0;i<NUM_LEDS;i++) 
        pixels[i]=adjust_brightness(bg_color,bg_brightness);
      break;
      
    case BG_MODE_RAINBOW:
        background_rainbow();
      break;
  
    default: bg_mode=BG_MODE_FILL;
      break;
  }
}   

void blit_icon(byte icon, int pos) {
  uint16_t i,p;
  if (icon>=MAX_ICONS) return;
  for(i=0;i<ICON_PIXELS;i++) {
      p=pos*7+i; 
      if ((p>=0) && (p<NUM_LEDS))  {
        byte c=i/7, r=i%7;
        if (pos%2) r=6-r;   // reverse every second column !
        if (icons[icon][c*7+r])        
           pixels[pos*7+i]=adjust_brightness(icons[icon][c*7+r],icon_brightness);
      }
  }
}

void update_icons() {
  if (preview_acticon) {
    blit_icon(act_icon+act_anim, icon_pos);
    if (!(counter%anim_wait)) {
      // icon_pos=(icon_pos+1)%(NUM_COLUMNS+20);
      if (icons[act_icon][ICON_PIXELS]) act_anim++;
      else act_anim=0; 
    }
    preview_acticon--;
  }
}

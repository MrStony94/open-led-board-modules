void drawIcon(byte icon_num, int offset) {
  byte anim_count;
  anim_count=icons[icon_num][ICON_PIXELS]; 
  if (anim_count) {
    if (!(counter%anim_wait)) { 
      anim_count++; 
      if ((icon_num+anim_count>=MAX_ICONS) || (!(icons[icon_num+anim_count-1][ICON_PIXELS])))
         anim_count=1;
      icons[icon_num][ICON_PIXELS]=anim_count;
      pixelupdate=1;
    }
    blit_icon(icon_num+anim_count-1,NUM_COLUMNS-ICON_OFFSET-offset);
  }
  else blit_icon(icon_num,NUM_COLUMNS-ICON_OFFSET-offset);
}

void drawFontCol(char c, int i){
  int pos;
  if(i >= 0 && i < NUM_COLUMNS){
      for(int j = 0; j < 7; j++){
        if (!(i%2)) pos=6-j; else pos=j; // reverse every second column !
        if(c & 0x1){
            pixels[i*7+pos]=adjust_brightness(scrollcolor,scroll_brightness);
        } 
        c >>= 1;
      }    
  }
}

void drawChar(char c, int offset){
  char col;
  if (c<20) drawIcon (c-10,offset); // not a readable ASCII-character -> must be icon number!
  else {
    for(int i = 0; i < 5; i++){
      if(i - offset >= 0 && i - offset < NUM_COLUMNS){
        col = pgm_read_byte(font+(c*5)+i);
        drawFontCol(col,i - offset);
      }
    }
  }
}

void update_scrolltext() {
  static byte pos_in_char=0;
  if (!scrolltext.length()){
    return;
  }
  if (!(counter%scrollwait)) {
    pos_in_char=(pos_in_char+1)%6; 
    if (!pos_in_char){
      scrollindex = (scrollindex+1)%scrolltext.length();
    }
    pixelupdate=1;
  }

  for(byte k = 0; k < (NUM_COLUMNS/5)+1; k++){
      drawChar(scrolltext.charAt(scrollindex+k),(pos_in_char - k*6));
      drawFontCol(0,(5-pos_in_char+k*6));
  }
  if ((scrollindex == (scrolltext.length()-1)) && (pos_in_char == 5)){
        scrollindex = 0;
        if(countpostsround == 3){
          nextAdminPost();
          countpostsround = 0;
        }else{
          nextPost(); 
          countpostsround++;
        }
        Serial.println(scrolltext);
        Serial.println(countpostsround);
  }
}

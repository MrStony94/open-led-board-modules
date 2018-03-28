void setToStruct(){
  if (userstructelemnts >= (STRUCT_LEN - 1)){
    deletePost();
    userstructelemnts = (STRUCT_LEN -1);
  }
  userposts[userstructelemnts].scrolltext = scrolltext_new;
  userposts[userstructelemnts].scrollBrightness = scroll_brightness_new;
  userposts[userstructelemnts].scrollWait = scrollwait_new;
  userposts[userstructelemnts].scrollColor = scrollcolor_new;
  userposts[userstructelemnts].bgMode = bg_mode_new;
  userposts[userstructelemnts].bgBrightness = bg_brightness_new;
  userposts[userstructelemnts].bgWait = bg_wait_new;
  userposts[userstructelemnts].bgColor = bg_color_new;
  userstructelemnts++;  
}

void deletePost(){
  struct Post helperStruct;
  for (int c = 1;c<STRUCT_LEN;c++){
    helperStruct = userposts[c];
    userposts[c-1] = helperStruct;
  }
  
}

void nextPost(){
  if (userstructcounter >= userstructelemnts){
    userstructcounter = 0;
  }
  scrolltext = userposts[userstructcounter].scrolltext;
  scroll_brightness = userposts[userstructcounter].scrollBrightness;
  scrollwait = userposts[userstructcounter].scrollWait;
  scrollcolor = userposts[userstructcounter].scrollColor;
  bg_mode = userposts[userstructcounter].bgMode;
  bg_brightness = userposts[userstructcounter].bgBrightness;
  bg_wait = userposts[userstructcounter].bgWait;
  bg_color = userposts[userstructcounter].bgColor;
  userstructcounter++;
}

void setDefaultPost(){
  adminposts[0].scrolltext=default_post1;
  adminposts[1].scrolltext=default_post2;
  adminposts[2].scrolltext=default_post3;
  for (int i = 0; i<3;i++){
    adminposts[i].scrollBrightness = scroll_brightness;
    adminposts[i].scrollWait = scrollwait;
    adminposts[i].scrollColor = scrollcolor;
    adminposts[i].bgMode = bg_mode_new;
    adminposts[i].bgBrightness = bg_brightness;
    adminposts[i].bgWait = bg_wait;
    adminposts[i].bgColor = bg_color;  
  }
}

void nextAdminPost(){
  if(adminstructcounter == 3){
    adminstructcounter = 0;
  }
  scrolltext = adminposts[adminstructcounter].scrolltext;
  scroll_brightness = adminposts[adminstructcounter].scrollBrightness;
  scrollwait = adminposts[adminstructcounter].scrollWait;
  scrollcolor = adminposts[adminstructcounter].scrollColor;
  bg_mode = adminposts[adminstructcounter].bgMode;
  bg_brightness = adminposts[adminstructcounter].bgBrightness;
  bg_wait = adminposts[adminstructcounter].bgWait;
  bg_color = adminposts[adminstructcounter].bgColor;
  adminstructcounter++;
}



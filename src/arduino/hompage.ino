void on_homepage() {
  // String html = FPSTR(index_html);   // get string constant which contains all client-side webcode
  //server.send(200, "text/html", html);
  if (load_admin_space){
    Serial.println("got homepage request - sending index.html");
    handleFileRead("/admin/index.html");
  } else {
    Serial.println("got homepage request - sending index.html");
    handleFileRead("/index.html");
  }
  
}

void on_error(){
  if (!load_admin_space){
    server.send(403, "text/html", "html");
  }
  else{
    handleFileRead("/admin/index.html");
  }
}


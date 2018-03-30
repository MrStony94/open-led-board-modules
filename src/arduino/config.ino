//-------------------Write and Read in SPIFFS------------------------
bool read_config() {
  File configFile = SPIFFS.open("/config.json", "r+");
  if (!configFile){
    Serial.print("Failed to open config file");
    Serial.println(configFile);
    return false;
  }
  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  json.printTo(Serial);
  if (!json.success()) {
    Serial.println("Failed to parse config file");
    return false;
  }
  json.printTo(Serial);
  default_post1 = json["default_post1"].asString();
  default_post2 = json["default_post2"].asString();
  default_post3 = json["default_post3"].asString();
  modules = (int) json["modules"];
  password = json["password"].asString();
  user_ap_name = json["apname"].asString();
  return true;
}

bool write_config(int mod, String apname, String post1, String post2, String post3, String passwd) {
  SPIFFS.remove("/config.json");
  File configFile = SPIFFS.open("/config.json", "w+");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }
  StaticJsonBuffer<200> jsonBuffer2;
  JsonObject& json = jsonBuffer2.createObject();
  json["default_post1"] = post1;
  json["default_post2"] = post2;
  json["default_post3"] = post3;
  json["modules"] = mod;
  json["password"] = passwd;
  json["apname"] = apname;
  
  json.printTo(Serial);
  json.printTo(configFile);
  return true;
}

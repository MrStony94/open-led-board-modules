bool readConfig(){
  File configFile = SPIFFS.open("/config.json","r");
  if (!configFile){
    Serial.print("Failed to open config file");
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
  post = json["adminposts"];
  modules = json["modules"]
  //password = json["password"];
  //Serial.println(password);
}

boolean writeConfig(int mod, String post){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["modules"] = "1";
  //json["password"] = "NewPassword";
  json["adminposts"] = "neuertext";
  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }
  json.printTo(Serial);
  json.printTo(configFile);
  return true;
}

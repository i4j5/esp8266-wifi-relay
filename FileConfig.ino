// Загрузка данных сохраненных в файл  config.json
bool loadConfig() {
  // Открываем файл для чтения
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
  // если файл не найден  
    Serial.println("Failed to open config file");
  //  Создаем файл запиав в него аные по умолчанию
    saveConfig();
    return false;
  }
  // Проверяем размер файла, будем использовать файл размером меньше 1024 байта
  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

// загружаем файл конфигурации в глобальную переменную
  jsonConfig = configFile.readString();
  // Резервируем памяь для json обекта буфер может рости по мере необходимти предпочтительно для ESP8266 
    DynamicJsonBuffer jsonBuffer;
  //  вызовите парсер JSON через экземпляр jsonBuffer
  //  строку возьмем из глобальной переменной String jsonConfig
    JsonObject& root = jsonBuffer.parseObject(jsonConfig);
  // Теперь можно получить значения из root  ;
    devece_name = root["devece_name"].as<String>();
    wifi_ssid = root["wifi_ssid"].as<String>();
    wifi_pass = root["wifi_pass"].as<String>();
    devece_id = root["devece_id"].as<String>();
    devece_key = root["devece_key"].as<String>();
    String url = root["server"].as<String>();
    for(int i=0; i < sizeof(url); i++) {
      server[i] = url[i];
    }
    return true;
}

// Запись данных в файл config.json
bool saveConfig() {
  // Резервируем памяь для json обекта буфер может рости по мере необходимти предпочтительно для ESP8266 
  DynamicJsonBuffer jsonBuffer;
  //  вызовите парсер JSON через экземпляр jsonBuffer
  JsonObject& json = jsonBuffer.parseObject(jsonConfig);
  // Заполняем поля json 
  json["devece_name"] = devece_name;
  json["wifi_ssid"] = wifi_ssid;
  json["wifi_pass"] = wifi_pass;
  json["devece_id"] = devece_id;
  json["devece_key"] = devece_key;
  json["server"] = server;
  // Помещаем созданный json в глобальную переменную json.printTo(jsonConfig);
  json.printTo(jsonConfig);
  // Открываем файл для записи
  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    //Serial.println("Failed to open config file for writing");
    return false;
  }
  // Записываем строку json в файл 
  json.printTo(configFile);
  return true;
  }






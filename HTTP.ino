void HTTP_init(void) {

  HTTP.on("/configs.json", handle_ConfigJSON); // формирование configs.json страницы для передачи данных в web интерфейс
  // API для устройства
  HTTP.on("/devece", setDevece);
  HTTP.on("/server", setServer);
  HTTP.on("/ssid", handle_Set_Ssid);     // Установить имя и пароль роутера по запросу вида /ssid?ssid=home2&password=12345678
  HTTP.on("/restart", handle_Restart);   // Перезагрузка модуля по запросу вида /restart?device=ok
  // Запускаем HTTP сервер
  HTTP.begin();
}

void setDevece() {
  devece_id = HTTP.arg("id");
  devece_key = HTTP.arg("key");
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

void setServer() {
  String url = HTTP.arg("url");
  for(int i=0; i < sizeof(url); i++) {
    server[i] = url[i];
  }
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

// Установка параметров для подключения к внешней AP по запросу вида http://192.168.0.101/ssid?ssid=home2&password=12345678
void handle_Set_Ssid() {
  wifi_ssid = HTTP.arg("ssid");            // Получаем значение ssid из запроса сохраняем в глобальной переменной
  wifi_pass = HTTP.arg("pass");    // Получаем значение password из запроса сохраняем в глобальной переменной
  saveConfig();                        // Функция сохранения данных во Flash пока пустая
  HTTP.send(200, "text/plain", "OK");   // отправляем ответ о выполнении
}

//Установка параметров внутренней точки доступа по запросу вида http://192.168.0.101/ssidap?ssidAP=home1&passwordAP=8765439 
void handle_Set_Ssidap() {              //
  //_ssidAP = HTTP.arg("ssidAP");         // Получаем значение ssidAP из запроса сохраняем в глобальной переменной
  //_passwordAP = HTTP.arg("passwordAP"); // Получаем значение passwordAP из запроса сохраняем в глобальной переменной
  saveConfig();                         // Функция сохранения данных во Flash пока пустая
  HTTP.send(200, "text/plain", "OK");   // отправляем ответ о выполнении
}

// Перезагрузка модуля по запросу вида http://192.168.0.101/restart?device=ok
void handle_Restart() {
  String restart = HTTP.arg("device");          // Получаем значение device из запроса
  if (restart == "ok") {                         // Если значение равно Ок
    HTTP.send(200, "text / plain", "Reset OK"); // Oтправляем ответ Reset OK
    ESP.restart();                                // перезагружаем модуль
  }
  else {                                        // иначе
    HTTP.send(200, "text / plain", "No Reset"); // Oтправляем ответ No Reset
  }
}

void handle_ConfigJSON() {
  String json = "{";  // Формировать строку для отправки в браузер json формат
  //{"SSDP":"SSDP-test","ssid":"home","password":"i12345678","ssidAP":"WiFi","passwordAP":"","ip":"192.168.0.101"}
  // Имя SSDP
  json += "\"devece_name\":\"";
  json += devece_name;
  // Имя сети
  json += "\",\"wifi_ssid\":\"";
  json += wifi_ssid;
  // Пароль сети
  json += "\",\"wifi_pass\":\"";
  json += wifi_pass;
  
  json += "\",\"devece_id\":\"";
  json += devece_id;
  json += "\",\"devece_key\":\"";
  json += devece_key;
  
  json += "\",\"server\":\"";
  json += server;

  json += "\",\"ip\":\"";
  json += WiFi.localIP().toString();
  json += "\"}";
  HTTP.send(200, "text/json", json);
}






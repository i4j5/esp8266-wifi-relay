void SSDP_init(void) {
  // SSDP дескриптор
  HTTP.on("/description.xml", HTTP_GET, []() {
    SSDP.schema(HTTP.client());
  });
  //Если версия  2.0.0 закаментируйте следующую строчку
  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName(devece_name);
  SSDP.setSerialNumber("00166788102201");
  SSDP.setURL("/");
  SSDP.setModelName(devece_name);
  SSDP.setModelNumber("000000000001");
  SSDP.setModelURL("http://___");
  SSDP.setManufacturer("Sazhin Sergey");
  SSDP.setManufacturerURL("http://___");
  SSDP.begin();
}


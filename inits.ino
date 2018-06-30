// ADDR 0 - Wifi Mode
// ADDR 1 - SSID End Addr
// ADDR 2 - Password End Addr
// ADDR 3 - SSID begin
// ADDR 255 - SSID End Max
// ADDR 256 - Password Begin
// ADDR 512 - Password End Max




void initMode(bool modex)
{
  WiFi.hostname("HatchSwitch"+String(ID0));
  if(modex == true)
  {
   //getallAP();
   initClient();
   //initAP(); 
  }
  else
  {
    initClient();
  }
}








bool getMode1()
{
  byte wifiMode;
  bool md;
  wifiMode = EEPROM.read(0);
  byte pops = false;
//  pops = readSSID();
 
  if(wifiMode == 0xFF)
  {
    md = true;
  }
  else
  {
    md = false;
  }
  return md;
}







void initAP()
{
  //Serial.println("APMODE");
  APmode();
}




void initClient()
{
  bool ream = readCred();
  if(ream == false)
  {
   
 
  
  EEPROM.write(0,0xCA);
  EEPROM.commit();
 // Serial.println("Connection OK");
  }
  else
  {
    //Serial.println("Starting in AP mode");
    //initAP();
  }
}














































int getallAP()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  int n = WiFi.scanNetworks();
  if(n>0)
  {
    for(int i=0;i<n;i++)
    {
      SSIDS[i] = WiFi.SSID(i);
    }
    for(int i=0;i<n;i++)
    {
      ssidRet = ssidRet +","+WiFi.SSID(i);
    }
  }
  
 return n;
}


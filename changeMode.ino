void APmode()
{
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.hostname("HatchSwitch"+String(ID0));
  WiFi.begin(APssid,APpassword); 
  EEPROM.write(0,0xFF);
  EEPROM.commit();
  
}

void CLmode(String s11, String p11)
{
  int dst,tst;
  dst = s11.length();
  tst = p11.length();
   char xsi[dst];
  char xpw[tst];

  s11.toCharArray(xsi,dst+1);
  p11.toCharArray(xpw,tst+1);
  //Serial.println(xsi);
  //Serial.println(xpw);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.hostname("HatchSwitch"+String(ID0));
  
  WiFi.begin(xsi, xpw);
  
}






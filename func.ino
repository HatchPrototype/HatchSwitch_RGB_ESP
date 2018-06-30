bool writeCredi(String ssi,String passi)
{
  clearEEPROM();
  
  char ssidmx[255],passimx[255];
  byte sea,pea;
  ssi.toCharArray(ssidmx, ssi.length()+1);
  passi.toCharArray(passimx, passi.length() +1);
  sea = ssi.length()+3;
  pea = passi.length();
  EEPROM.write(0,0xDA);
  EEPROM.commit();
  EEPROM.write(1,sea);
  EEPROM.commit();
  EEPROM.write(2,pea);
  EEPROM.commit();
  for(int i=3;i<sea;i++)
  {
    EEPROM.write(i,ssidmx[i-3]);
     delay(2);
     EEPROM.commit();
  }
  for(int i=255;i<= 256+pea;i++)
  {
    EEPROM.write(i,passimx[i-255]);
    delay(2);
    EEPROM.commit();
  }

  readCred();
  

  return true;
}






void clearEEPROM()
{
  for(int i=0;i<=512;i++)
  {
    EEPROM.write(i,0xFF);
    EEPROM.commit();
    delay(2);
  }
}


void readall()
{
  for(int i=0;i<512;i++)
  {
    Serial.print(i,HEX);
    Serial.print("=");
    Serial.println(EEPROM.read(i),HEX);
    delay(1);
  }
}


void populate()
{
  for(int i=0;i<512;i++)
  {
    Serial.print(i,HEX);
    Serial.print("=");
    EEPROM.write(i,0xCA);
    EEPROM.commit();
    Serial.println(EEPROM.read(i),HEX);
    delay(1);
  }
}




bool readCred()
{
  bool zeroFlag = false;
  
  byte sidEnd,pwdEnd;
  bool ret;
  ret = false;
  String newSSi,newPWD;
  newSSi = "";
  newPWD = "";
  sidEnd = EEPROM.read(1);
  pwdEnd = EEPROM.read(2);

  char sid[sidEnd-3];
  char pwd[pwdEnd];

 
  

  
  //Serial.println("----1-----");
  //Serial.println(sidEnd-3);
  //Serial.println(pwdEnd);
  //Serial.println("----2-----");
  
  for(int i=0;i<sidEnd-3;i++)
  {
    sid[i] = EEPROM.read(i+3);
    if((sid[i] == 0x00)||(sid[i] == 0xFF))
    {
      zeroFlag = true;
    }
    newSSi = newSSi+sid[i];
    //Serial.println(sid[i],HEX);
    
  }
  //Serial.println("-----");
  for(int i=255;i<255+pwdEnd;i++)
  { 
    pwd[i-255] = EEPROM.read(i);

    if((pwd[i-255] == 0x00)||(pwd[i-255] == 0xFF))
    {
      zeroFlag = true;
    }
    //Serial.println(pwd[i-255],HEX);
    
    newPWD = newPWD + pwd[i-255];
  }
  //ssid = sid;
  //password = pwd;
  
  //Serial.println(sizeof(sid));
  //Serial.println(sizeof(pwd));
  WiFi.mode(WIFI_STA);
  //Serial.println("Starting Client Mode");
  ssid2 = newSSi;
  passwd2 = newPWD;

  ssid2 = "home";
  passwd2 = "CYRIL12345";


  //Serial.println("Connecting");
  
  
  CLmode(ssid2,passwd2);
  
  return zeroFlag;
}


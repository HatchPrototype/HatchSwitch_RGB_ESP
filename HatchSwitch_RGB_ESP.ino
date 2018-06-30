#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <EEPROM.h>

#define ID0 0x04


bool SS1,SS2,SS3,SS4;
byte ONR,ONG,ONB;
byte OFFR,OFFG,OFFB;


bool WMode = true; // True = AP/ False = Client
String SSIDS[255];
String ssidRet = "ssids";
String ssid11 = "";
WiFiUDP Udp;
String ssid2;
String passwd2;
char ipack[255];
unsigned int localUdpPort = 39150;
unsigned int replyUdpPort = 36150;
unsigned int discoverUdpPort = 33150;
const char* APssid = "HatchSwitch" ;
const char* APpassword = "hatch1";

void setup() {
  EEPROM.begin(512);
  Serial.begin(9600);
  byte gs = EEPROM.read(511);
  //readall();
  
  
  
  initMode(getMode1());
  while (WiFi.status() != WL_CONNECTED) {
    serialStuff();
    //Serial.println(".");
  }
  Udp.begin(localUdpPort);
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
 getPacket();
 serialStuff();
}

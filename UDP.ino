bool getPacket()
{
int packetSize = Udp.parsePacket();
bool ret = false;
if (packetSize)
{
  //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
  int len = Udp.read(ipack, 255);
  if (len > 0)
  {
    ipack[len] = 0;
  }
  //Serial.printf("UDP packet contents: %s\n", incomingPacket);
  processIncomming();
ret = true;
}
return ret;
}




bool processIncomming()
{
  if((ipack[0] == 'd')&&(ipack[1] == 'i')&&(ipack[2] == 's')&&(ipack[3] == 'c')&&(ipack[4] == 'o')&&(ipack[5] == 'v')&&(ipack[6] == 'e')&&(ipack[7] == 'r'))
  {
    String reply = "response," + Udp.remoteIP().toString() + ",switch,RGB";
    Udp.beginPacket(Udp.remoteIP(), discoverUdpPort);
    Udp.write(reply.c_str());
    Udp.endPacket();
    
  }
  else if((ipack[0] == 'a')&&(ipack[1] == 'u')&&(ipack[2] == 't')&&(ipack[3] == 'h')&&(ipack[4] == 'w')&&(ipack[5] == 'i')&&(ipack[6] == 'f')&&(ipack[7] == 'i'))
  {
    byte ssidLen,passLen;
    String sssid,passs;
    ssidLen = ipack[8];
    passLen = ipack[9];
    for(int l = 10;l<ssidLen+10;l++)
    {
      sssid = sssid + ipack[l];
    }

    for(int l = 10+ssidLen;l<10+ssidLen+passLen;l++)
    {
      passs = passs + ipack[l];
    }

    Serial.println(sssid);
    Serial.println(passs);

    writeCredi(sssid,passs);
    
    
  }
  else if((ipack[0] == 's')&&(ipack[1] == 'w')&&(ipack[2] == 'i')&&(ipack[3] == 't')&&(ipack[4] == 'c')&&(ipack[5] == 'h')&&(ipack[6] == 's')&&(ipack[7] == 't'))
  {
    writeState(ipack[8],ipack[9],ipack[10],ipack[11]);
  }
  else if((ipack[0] == 'r')&&(ipack[1] == 'g')&&(ipack[2] == 'b')&&(ipack[3] == 's')&&(ipack[4] == 't')&&(ipack[5] == 'o')&&(ipack[6] == 'n')&&(ipack[7] == 'n'))
  {
    setRGB(HIGH,ipack[8],ipack[9],ipack[10]);
  }
  else if((ipack[0] == 'r')&&(ipack[1] == 'g')&&(ipack[2] == 'b')&&(ipack[3] == 's')&&(ipack[4] == 't')&&(ipack[5] == 'o')&&(ipack[6] == 'f')&&(ipack[7] == 'f'))
  {
    setRGB(LOW,ipack[8],ipack[9],ipack[10]);
  }
  else if((ipack[0] == 'g')&&(ipack[1] == 'e')&&(ipack[2] == 't')&&(ipack[3] == 's')&&(ipack[4] == 't')&&(ipack[5] == 'a')&&(ipack[6] == 't')&&(ipack[7] == 'e'))
  {
    sendStats();
  }
  else if((ipack[0] == 'r')&&(ipack[1] == 'e')&&(ipack[2] == 's')&&(ipack[3] == 'e')&&(ipack[4] == 't')&&(ipack[5] == 'e')&&(ipack[6] == 's')&&(ipack[7] == 'p'))
  {
    ESP.restart();
  }
  else if((ipack[0] == 'a')&&(ipack[1] == 'p')&&(ipack[2] == 'm')&&(ipack[3] == 'o')&&(ipack[4] == 'd')&&(ipack[5] == 'e')&&(ipack[6] == '1')&&(ipack[7] == '1'))
  {
    APmode();
  }
  else if((ipack[0] == 'c')&&(ipack[1] == 'l')&&(ipack[2] == 'm')&&(ipack[3] == 'o')&&(ipack[4] == 'd')&&(ipack[5] == 'e')&&(ipack[6] == '1')&&(ipack[7] == '1'))
  {
   // CLmode();
  }
}


void udpReply(String outdata)
{
    Udp.beginPacket(Udp.remoteIP(), replyUdpPort);
    Udp.write(outdata.c_str());
    Udp.endPacket();
}


void sendStats()
{
  String nout = "switchStatus,";
  if(SS1 == LOW)
  {
    nout = nout + "0,";
  }
  else
  {
    nout = nout + "1,";
  }
  if(SS2 == LOW)
  {
    nout = nout + "0,";
  }
  else
  {
    nout = nout + "1,";
  }
  if(SS3 == LOW)
  {
    nout = nout + "0,";
  }
  else
  {
    nout = nout + "1,";
  }
  if(SS4 == LOW)
  {
    nout = nout + "0,";
  }
  else
  {
    nout = nout + "1,";
  }

  nout = nout + ONR + "," + ONG + "," + ONB + ","; 
  nout = nout + OFFR + "," + OFFG + "," + OFFB;

 udpReply(nout);
  
}


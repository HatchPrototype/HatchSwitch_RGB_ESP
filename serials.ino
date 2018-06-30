byte buff[13];

void writeState(byte SW1,byte SW2,byte SW3,byte SW4)
{
  buff[0] = 0xCC;
  buff[1] = 0x77;
  buff[2] = 0xCC;
  buff[3] = 0x77;
  buff[4] = 0xDC;
  buff[5] = 0x01;
  buff[6] = 0x06;
  buff[7] = 0xAC;
  buff[8] = SW1;
  buff[9] = SW2;
  buff[10] = SW3;
  buff[11] = SW4;
  buff[12] = calcCRC();
  Serial.write(buff,13);
 }


byte calcCRC()
{
  byte crcx = 0x00;
  for(int i=0;i<12;i++)
  {
    crcx ^=buff[i];
  }
  return crcx;
}


void setRGB(bool tate,byte rdd,byte grr,byte bll)
{
  buff[0] = 0xCC;
  buff[1] = 0x77;
  buff[2] = 0xCC;
  buff[3] = 0x77;
  buff[4] = 0xDC;
  buff[5] = 0x01;
  buff[6] = 0x06;
  buff[7] = 0xC0;
  if(tate == true)
  {
    buff[8] = 0x01;
  }
  else
  {
    buff[8] = 0x00;
  }
  buff[9] = rdd;
  buff[10] = grr;
  buff[11] = bll;
  buff[12] = calcCRC();
  Serial.write(buff,13);
}




void serialStuff()
{
  byte inbuff[10];
  if(Serial.available() == 10)
  {
    for(int i=0;i<10;i++)
    {
      inbuff[i] = Serial.read();
    }
  }

  if((inbuff[0]==0xCC)&&(inbuff[1]==0x77)&&(inbuff[2]==0xCC)&&(inbuff[3]==0x77))
  {
    Serial.println("in1");
    if(inbuff[4]==0x01)
    {
      if(inbuff[5]==0x00)
      {
        SS1 = false;
      }
      else
      {
        SS1 = true;
      }

      if(inbuff[6]==0x00)
      {
        SS2 = false;
      }
      else
      {
        SS2 = true;
      }

      if(inbuff[7]==0x00)
      {
        SS3 = false;
      }
      else
      {
        SS3 = true;
      }

      if(inbuff[8]==0x00)
      {
        SS4 = false;
      }
      else
      {
        SS4 = true;
      }
      sendStats();
    }

    else if(inbuff[4] == 0x02)
    {
      if(inbuff[5] == 0x01)
      {
      ONR = inbuff[6];
      ONG = inbuff[7];
      ONG = inbuff[8];
      }
      else if(inbuff[5] == 0x00)
      {
      OFFR = inbuff[6];
      OFFG = inbuff[7];
      OFFG = inbuff[8];
      }
    }

    else if(inbuff[4] == 0xAA)
    {
      APmode();
      
    }
    else if(inbuff[4] == 0xAC)
    {
     // CLmode();
      //Serial.println("OK");
    }
    
  }
}


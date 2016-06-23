/*
Author: Shirish Jadav
Project: Bytelens Rating Devices 
Date: 06/21/2016
Your are allowed to copy the code and use it in any project Related to Bytelens
Any outside use is not allowed.
*/
#ifndef PACKET_H
#define PACKET_H

char dName[]= "BLM"; //ByteLens Mesh
uint8_t myMac[6];

enum advtype_t{ CONFIG = 0X01, DATA, DATA_ACK, TIME };
typedef enum advtype_t AdvType;

enum src{SOURCE, RELAY};

typedef struct Packets{
  uint16_t token=0;
  uint8_t mac[6]={0,0,0,0,0,0};
  uint8_t data[5]={0,0,0,0,0};
  uint8_t org=SOURCE;
  AdvType at=DATA;
  uint8_t ttime=6;
 }Packet;

 Packet myp;

void packetinfo(Packet q)
{
  Serial.print("Mac Addr: ");
                for(int i=0;i<6;i++)
                {
                  Serial.print(q.mac[i],HEX);
                  if(i<5)
                  Serial.print(" : ");
                  else
                  Serial.println("");
                }
                Serial.print("Data: ");
                for(int i=0;i<5;i++)
                {
                  Serial.print(q.data[i]);
                  if(i<4)
                  Serial.print(" : ");
                  else
                  Serial.println("");
                }
                Serial.print("Ttime: "); Serial.println(q.ttime);
}
uint8_t nrfRandom()
{
     NRF_RNG->TASKS_START = 1; 
     NRF_RNG->EVENTS_VALRDY = 0;
     while ( NRF_RNG->EVENTS_VALRDY == 0){}
     return (uint8_t)NRF_RNG->VALUE;
}

void setPackMac(uint8_t *_m)
{
 for(int i=0;i<6;i++)
  myp.mac[i]=_m[i];
}
void setPack(uint8_t *_d,uint8_t ln, AdvType _a) // data, data len, AdType
{
  myp.token=nrfRandom()<<7 | nrfRandom();
//  p.token[1]=nrfRandom();
  for(int i=0;i<ln;i++)// copy data to packet
  {
    myp.data[i]=_d[i];
  }
  myp.at=_a;
}
#endif
/*
Author: Shirish Jadav
Project: Bytelens Rating Devices 
Date: 06/21/2016
Your are allowed to copy the code and use it in any project Related to Bytelens
Any outside use is not allowed.
*/

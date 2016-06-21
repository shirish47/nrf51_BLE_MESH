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

enum advtype_t{ CONFIG = 0X01, DATA, TIME };
typedef enum advtype_t AdvType;

typedef struct Packets{
  uint8_t token[2]={0,0};
  uint8_t mac[6]={0,0,0,0,0,0};
  uint8_t data[5]={1,2,3,4,5};
  AdvType at=DATA;
  uint8_t ttime=0;
 }Packet;

 Packet p;

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
  p.mac[i]=_m[i];
}
void setPack(uint8_t *_d,uint8_t ln, AdvType _a) // data, data len, AdType
{
  p.token[0]=nrfRandom();
  p.token[1]=nrfRandom();
  for(int i=0;i<ln;i++)// copy data to packet
  {
    p.data[i]=_d[i];
  }
  p.at=_a;
}
#endif
/*
Author: Shirish Jadav
Project: Bytelens Rating Devices 
Date: 06/21/2016
Your are allowed to copy the code and use it in any project Related to Bytelens
Any outside use is not allowed.
*/

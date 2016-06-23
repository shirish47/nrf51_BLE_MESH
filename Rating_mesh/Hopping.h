/*
Author: Shirish Jadav
Project: Bytelens Rating Devices 
Date: 06/21/2016
Your are allowed to copy the code and use it in any project Related to Bytelens
Any outside use is not allowed.
*/
#ifndef HOPPING_H
#define HOPPING_H
#include "Packet.h"


void HPMSG(char msg[])
{
  Serial.print("HPMSG: ");
  Serial.println(msg);
}
#define TOKEN_LIST_SIZE 5
#define MAX_TOKEN_LIFE 5
//tokenlist
typedef uint16_t Token;

Token tokenlist[TOKEN_LIST_SIZE];
Packet packlist[TOKEN_LIST_SIZE];
//uint8_t tkType[];

void printAllPackinfo()
{
  HPMSG("TOKEN LIST INFO ");
  for(int i=0;i<TOKEN_LIST_SIZE;i++)
  {
   Serial.print("Token :");
   Serial.println(tokenlist[i]);
   packetinfo(packlist[i]);
  }
  
}
uint8_t getMostSentPack()
{
  int i=0;
  int _tt=0;
  int _ix=0;
  for(;i<TOKEN_LIST_SIZE;i++)
  {
    if(packlist[i].ttime>_tt)
    {
        _tt=packlist[i].ttime;
        _ix=i;
    }
  }
return _ix;
}
void clearAckPack()// clear ack packs if they are transmited for max tttime
{
 HPMSG("CLR_PACK");
 for(int i=0;i<TOKEN_LIST_SIZE;i++) 
 {
  if(packlist[i].ttime >= MAX_TOKEN_LIFE)
  {
    packlist[i].ttime=MAX_TOKEN_LIFE+2;// just keep this high
  }
 }
}

uint8_t leastSentPack()
{
  HPMSG("LEAST_SENT");
  int i=0;
  int _tt=packlist[getMostSentPack()].ttime;//highest sent packet.
  int _ix=0;
  for(;i<TOKEN_LIST_SIZE;i++)
  {
    if(packlist[i].ttime <= _tt)
    {
      _tt = packlist[i].ttime;
        _ix=i;
    }
  }
  Serial.print("least sent index: ");  Serial.println(_ix);
  
return _ix;
}
void addPack(Packet *p)
{
  HPMSG("NEW_PACK");
  int i=getMostSentPack();
  HPMSG("ADDING NEW PACK");
  packlist[i].token = p->token;
  packlist[i].mac[0]=p->mac[0]  ; packlist[i].mac[1]=p->mac[1]  ; packlist[i].mac[2]=p->mac[2]  ; packlist[i].mac[3]=p->mac[3]  ; packlist[i].mac[4]=p->mac[4]  ;  packlist[i].mac[5]= p->mac[5];
  packlist[i].data[0]=p->data[0]  ;packlist[i].data[1]=p->data[1]  ;packlist[i].data[2]=p->data[2]  ;packlist[i].data[3]=p->data[3]  ;packlist[i].data[4]=p->data[4]  ;  packlist[i].data[5]=p->data[5] ;
  packlist[i].at=p->at ;
  packlist[i].ttime=0;

  tokenlist[i]=p->token;
}
void findPack(Packet *q)
{
   Token ft=(Token)q->token;
   
   uint8_t index=0;// index of token
   bool tkfound=false; //token found flag
   for(;index<TOKEN_LIST_SIZE;index++)
   {
    if(ft==tokenlist[index])
     {
      tkfound=true;
      break;
     }
   }
  if(tkfound)// token is in list what to do?? check if the type is same as the pervious one.
  { 
     HPMSG("OLD TOKEN");
     if(q->at==DATA_ACK)// packet types?
      {
        HPMSG("ACK PACKET");
        packlist[index].at=q->at;
        packlist[index].ttime=0;
      }
  }else// found a new pack.
  {
     HPMSG("NEW TOKEN");       
     addPack(q);
  }
}
#endif
/*
Author: Shirish Jadav
Project: Bytelens Rating Devices 
Date: 06/21/2016
Your are allowed to copy the code and use it in any project Related to Bytelens
Any outside use is not allowed.
*/

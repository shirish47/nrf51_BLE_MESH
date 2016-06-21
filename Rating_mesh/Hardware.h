/*
Author: Shirish Jadav
Project: Bytelens Rating Devices 
Date: 21/04/2016
Your are allowed to copy the code and use it in any project Related to Bytelens
Any outside use is not allowed.
*/
#ifndef HARDWARE_H
#define HARDWARE_H
#include "Arduino.h"

enum devRole{GATE=0x01,NODE};
uint8_t dRole=GATE;

void HMSG(char msg[])
{
  Serial.print("#HARDWARE ");
  Serial.println(msg);
}

//Outputs
#define LED_1 6  //P0.16
#define LED_2 11 // P0.12
//#define LED_3 2  //P0.10
#define LED_3  A4   //0.03
#define LED_4  A5   //0.04
#define B1 8 //p0.19   SW2
#define B2 A5 //p0.06  SW3
#define B3 18  //p0.20 SW5
#define B4  9 //p0.18  SW4
#define B5  A4 //p0.05 SW1

//
//static uint8_t butp1=0;
//static uint8_t butp2=0;
//static uint8_t butp3=0;
//static uint8_t butp4=0;
//static uint8_t butp5=0;

uint8_t bButtons[]={0,0,0,0,0};

//static uint8_t but=0;
bool isData=false;

void ledBlink()
{
  digitalWrite(LED_1,HIGH);
  delay(500);
  digitalWrite(LED_1,LOW);
//  delay(500);
}
void ledBlink2()
{
  digitalWrite(LED_2,HIGH);
  delay(500);
  digitalWrite(LED_2,LOW);
  delay(500);
}
void but1()
{
  ledBlink();
//  but= 0x01;
  bButtons[2]++;
 HMSG("But 3 Press");
Serial.print(": "); Serial.println(bButtons[2]);
  isData=true;
}
void but2()
{
  //but=0x02;
  ledBlink();
  bButtons[4]++;
   HMSG("But 5 Press");
Serial.print(": "); Serial.println(bButtons[4]);
  isData=true;
}
void but3()
{
// but=0x04; 
  ledBlink();
  bButtons[0]++;
  HMSG("But 1 Pressed");
Serial.print(": "); Serial.println(bButtons[0]);
  isData=true;
}
void but4()
{
//  but=0x08;
  ledBlink();
  bButtons[1]++;
   HMSG("But 2 Pressed");
Serial.print(": "); Serial.println(bButtons[1]);
  isData=true;
}
void but5()
{
//but=0x10;
  ledBlink();
  bButtons[3]++;
   HMSG("But 3 Pressed");
Serial.print(": "); Serial.println(bButtons[3]);
  isData=true;
}
void RoleSelector()
{
  HMSG("device Role Select");
  HMSG("Press but 1 for making dev as NODE ");
  int i=0;
  delay(1000);
  digitalWrite(LED_2,HIGH);
  while(i<6)
  {
    if(digitalRead(B3)==LOW)
      dRole=NODE;
    delay(500);
    i++;
  }
 digitalWrite(LED_2,LOW);
  delay(500);
if(dRole==NODE)
 {
  ledBlink2();  ledBlink2();
 }else
 {
    ledBlink2();  ledBlink2();  ledBlink2();
 }
 HMSG("Done Select");
}

//hardware init functions
//@params en: enable interrupts
void initHardware(bool en)
{
 //Outputs
 pinMode(LED_1,OUTPUT);
 pinMode(LED_2,OUTPUT);
// pinMode(LED_3,OUTPUT);
 
 //Inputs
 pinMode(B1,INPUT_PULLUP);
 pinMode(B2,INPUT_PULLUP);
 pinMode(B3,INPUT_PULLUP);
 pinMode(B4,INPUT_PULLUP);
 pinMode(B5,INPUT_PULLUP);
 if(en){
   attachInterrupt(B1,but1,FALLING);
   attachInterrupt(B2,but2,FALLING);
   attachInterrupt(B3,but3,FALLING);
   attachInterrupt(B4,but4,FALLING);
   attachInterrupt(B5,but5,FALLING); 
 }
}
#endif
/*
Author: Shirish Jadav
Project: Bytelens Rating Devices 
Date: 21/04/2016
Your are allowed to copy the code and use it in any project related of Bytelens
Any outside use is not allowed.
*/

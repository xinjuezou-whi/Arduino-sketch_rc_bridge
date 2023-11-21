/******************************************************************
Bridge the PWM between Remote controller and other IIC devices

Features:
- I2C with master
- xxx

Dependency:
- xxx

Written by Xinjue Zou, xinjue.zou@outlook.com

Apache License Version 2.0, check LICENSE for more information.
All text above must be included in any redistribution.

Changelog:
2023-11-21: initial version
2023-xx-xx: xxx
******************************************************************/
#include <Wire.h>
#include "rc_bridge.h"

uint8_t pins[] =
{
  2, 3, 4, 5
};

int fromMinMax[8][2] = 
{ 
  {994, 1998}, 
  {994, 1998}, 
  {994, 1998}, 
  {994, 1998}, 
  {994, 1998}, 
  {994, 1998}, 
  {994, 1998}, 
  {994, 1998}
};

int toMinMax[8][2] = 
{ 
  {50, -50}, 
  {50, -50}, 
  {50, -50}, 
  {50, -50}, 
  {50, -50}, 
  {50, -50}, 
  {50, -50}, 
  {50, -50}
};

RcBridge bridge(pins, sizeof(pins));

void setup() {
  //Starting Serial
  Serial.begin(9600);
  Serial.println("Ready");

  bridge.setMinMax(fromMinMax, toMinMax);
}

void loop() {
   //prints receiver raw val
   Serial.print(bridge.readRaw(0));
   Serial.print("\t");  
   Serial.print(bridge.readRaw(1));
   Serial.print("\t");  
   Serial.print(bridge.readRaw(2));
   Serial.print("\t");  
   Serial.print(bridge.readRaw(3));
   Serial.print("\t");  
   Serial.println();
}

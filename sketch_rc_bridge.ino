/******************************************************************
Bridge the PWM between Remote controller and other IIC devices

Features:
- PWM signal
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

const String VERSION("00.03");

// RC related
const uint8_t MAX_CHANNELS = 4;
uint8_t pins_[] =
{
  2, 3, 4, 5
};

int from_min_max_[8][2] = 
{ 
  {994, 1988}, 
  {994, 1988}, 
  {994, 1988}, 
  {994, 1988}, 
  {994, 1998}, 
  {994, 1998}, 
  {994, 1998}, 
  {994, 1998}
};

int to_min_max_[8][2] = 
{ 
  {0, 100}, 
  {0, 100}, 
  {0, 100}, 
  {0, 100}, 
  {0, 100}, 
  {0, 100}, 
  {0, 100}, 
  {0, 100}
};

RcBridge bridge_(pins_, sizeof(pins_), from_min_max_, to_min_max_);

// iic related
const int DEVICE_ADDR = 8;
const uint8_t SEND_DATA_SIZE = MAX_CHANNELS; // 1 byte for ecah rc channel, totally 16 channels
const uint8_t RECV_DATA_SIZE = 32; // Wire library has a softlimit up to 32 bytes
byte raw_data_[SEND_DATA_SIZE] = { 0 };
byte send_data_[SEND_DATA_SIZE] = { 0 };
byte recv_data_[RECV_DATA_SIZE] = { 0 };

// function that executes whenever data is read by master
// this function is registered as an event, see setup()
void requestEvent()
{
  // check if data is valid
  for (uint8_t i = 0; i < SEND_DATA_SIZE; ++i)
  {
    send_data_[i] = raw_data_[i];
    if (send_data_[i] < to_min_max_[i][0] || send_data_[i] > to_min_max_[i][1])
    {
      for (uint8_t j = 0; j < SEND_DATA_SIZE; ++j)
      {
        send_data_[j] = 255;
      }

      break;
    }
  }
  Wire.write(send_data_, SEND_DATA_SIZE);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int Length)
{
  for (int i = 0; i < Length; ++i)
  {
    recv_data_[i] = Wire.read();
  }
}

void setup() {
  //Starting Serial
  Serial.begin(9600);
  Serial.println(VERSION);
  Serial.println("\nReady");

  // iic
  Wire.begin(DEVICE_ADDR);      // join i2c bus with address
  Wire.onRequest(requestEvent); // register events
  Wire.onReceive(receiveEvent);
}

void loop() {
  for (uint8_t i = 0; i < MAX_CHANNELS; ++i)
  {
    raw_data_[i] = bridge_.readRaw(i);
  }
}

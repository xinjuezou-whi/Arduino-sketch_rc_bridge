/******************************************************************
Remote Controller bridge class

Features:
- pulseIn
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
#pragma once
#include "Arduino.h"

class RcBridge
{
  static const uint8_t MAX_CHANEL_COUNT = 16;
  static const uint8_t MIN_MAX_LEN = 2;

public:
	RcBridge(const uint8_t* PinArray, uint8_t ArraySize);
  RcBridge(const uint8_t* PinArray, uint8_t ArraySize, int FromMinMax[][MIN_MAX_LEN], int ToMinMax[][MIN_MAX_LEN]);
	void setMinMax(int FromMinMax[][MIN_MAX_LEN], int ToMinMax[][MIN_MAX_LEN]);
	long readRaw(int ChanelIndex);

private:
	uint8_t active_pin_count_{ MAX_CHANEL_COUNT };
	uint8_t pin_ch_[MAX_CHANEL_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int from_min_max_[MAX_CHANEL_COUNT][MIN_MAX_LEN] = { {1010, 2020}, {1010, 2020}, {1010, 2020}, {1010, 2020},
		{1010, 2020}, {1010, 2020}, {1010, 2020}, {1010, 2020},
		{1010, 2020}, {1010, 2020}, {1010, 2020}, {1010, 2020},
		{1010, 2020}, {1010, 2020}, {1010, 2020}, {1010, 2020}};
	int to_min_max_[MAX_CHANEL_COUNT][MIN_MAX_LEN] = { {0, 100}, {0, 100}, {0, 100}, {0, 100},
    {0, 100}, {0, 100}, {0, 100}, {0, 100},
    {0, 100}, {0, 100}, {0, 100}, {0, 100},
		{0, 100}, {0, 100}, {0, 100}, {0, 100}};
};

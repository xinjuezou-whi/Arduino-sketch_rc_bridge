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

******************************************************************/
#include "rc_bridge.h"

RcBridge::RcBridge(const uint8_t* PinArray, uint8_t ArraySize)
{
	if (ArraySize <= MAX_CHANEL_COUNT)
	{
		active_pin_count_ = ArraySize;
		
		for (uint8_t i = 0; i < active_pin_count_; ++i)
		{
			pin_ch_[i] = PinArray[i];
			pinMode(pin_ch_[i], INPUT);
		}
	}
}

RcBridge::RcBridge(const uint8_t* PinArray, uint8_t ArraySize, int FromMinMax[][MIN_MAX_LEN], int ToMinMax[][MIN_MAX_LEN])
  : RcBridge(PinArray, ArraySize)
{
  setMinMax(FromMinMax, ToMinMax);
}

void RcBridge::setMinMax(int FromMinMax[][MIN_MAX_LEN], int ToMinMax[][MIN_MAX_LEN])
{
	for (int i = 0; i < active_pin_count_; ++i)
	{
		from_min_max_[i][0] = FromMinMax[i][0];
		from_min_max_[i][1] = FromMinMax[i][1];
		to_min_max_[i][0] = ToMinMax[i][0];
		to_min_max_[i][1] = ToMinMax[i][1];
	}
}

long RcBridge::readRaw(int ChanelIndex)
{		
	return ChanelIndex < MAX_CHANEL_COUNT ?
		map(pulseIn(pin_ch_[ChanelIndex], HIGH), from_min_max_[ChanelIndex][0], from_min_max_[ChanelIndex][1],
			to_min_max_[ChanelIndex][0], to_min_max_[ChanelIndex][1]) : 0;
}

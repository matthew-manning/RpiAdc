#ifndef _ADC_LIB_H__
#define _ADC_LIB_H__
#include <stdlib.h>
#include "i2c.h"

struct AdcBoard
{
	struct i2c_handle * I2cHandle;
	uint8_t PortSel; //adc pin currently muxxed in
	uint8_t BusAddr; //i2c bus address of board
	float StepVolt; //micro volts per adc step
	uint8_t SampRate; //ADC samples per second 

};

void initAdc(struct AdcBoard * Board, int BusAddr);
void selAdcPort(struct AdcBoard * Board, uint8_t PortNum);
float readAdc(struct AdcBoard * Board);

#endif

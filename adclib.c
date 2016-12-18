#include "adclib.h"
#include <stdlib.h>
#include "i2c.h"
#include <stdio.h>//only needed for debug

void initAdc(struct AdcBoard * Board, int BusAddr)
//takes a adc board pointer
{
	uint16_t ConWord;
	uint8_t ReadBack[2];
	uint8_t  ConBytes[2];

//	struct AdcBoard NewBoard;
	Board->PortSel = 0;
	Board->BusAddr = BusAddr;
	Board->SampRate = 16;
	Board->I2cHandle = i2c_init(1, BusAddr, 0);
	Board->StepVolt = 187.5 /1000000.0;
	
	ConWord = 0x4020;//16 bits of config data
	ConBytes[0] = (ConWord >> 8) & 0xff;
	ConBytes[1] = (ConWord >> 0) & 0xff;
	i2c_write_to_reg(Board->I2cHandle, 1, (char *)ConBytes, 2);
	
	i2c_read_from_reg(Board->I2cHandle, 1, (char *)ReadBack, 2);
	printf("read back is %02x%02x\n", ReadBack[0], ReadBack[1]);
	
}

void selAdcPort(struct AdcBoard * Board, uint8_t PortNum)
{
	uint8_t PortMap;//three bits to write for port select
	uint8_t CurMap[2];//currentMap
	uint8_t WriteMap[2];//i2c writen map

	Board->PortSel = PortNum;
	switch (PortNum)
	{
		default:
		case 0: PortMap = 4;
			break;
		case 1: PortMap = 5;
			break;
		case 2: PortMap = 6;
			break;
		case 3: PortMap = 7;
	}
	
	i2c_read_from_reg(Board->I2cHandle, 1, (char *)CurMap, 2);
	WriteMap[1] = CurMap[1];
	WriteMap[0] = CurMap[0] & 0x8f;//scrub the three bits 
	WriteMap[0] |= (PortMap << 4);
	i2c_write_to_16reg(Board->I2cHandle, 1, (char *)WriteMap, 2);
	
} 
float readAdc(struct AdcBoard * Board)
//reads currently selected pin
{
	uint8_t ReadBytes[2];
	uint16_t  ReadU16;
	float	ReadVolts;

	i2c_read_from_reg(Board->I2cHandle, 0, (char *)ReadBytes, 2);

	ReadU16 = ReadBytes[0] << 8 | ReadBytes[1];

	ReadVolts = (float)((int16_t)ReadU16);

	ReadVolts *= Board->StepVolt;

	printf("raw value from adc is %u   float %f\n", ReadU16, ReadVolts);
	printf("pin being read %d\n", Board->PortSel);

	
	return ReadVolts;
	
}

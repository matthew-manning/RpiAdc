#include "adclib.h"
#include <stdlib.h>
#include "i2c.h"
#include <stdio.h>//only needed for debug

void initAdc(struct AdcBoard * Board, int BusAddr)
//takes a adc board pointer
{
//	uint16_t ConWord;
	uint16_t ReadBack;

//	struct AdcBoard NewBoard;
	Board->PortSel = 0;
	Board->BusAddr = BusAddr;
	Board->SampRate = 16;
	Board->I2cHandle = i2c_init(1, BusAddr, 0);
	Board->StepVolt = 187.5;
	
	//ConWord = 0x8020;//16 bits of config data
	
	//i2c_write_to_16reg(Board->I2cHandle, 1, &ConWord, 1);
	system("i2cset -y 1 0x48 1 0x8020 w");
	
	//i2c_read_from_16reg(Board->I2cHandle, 1, &ReadBack, 1);
	ReadBack = system("i2cget -y 1 0x48 1  w"); 
	printf("read back is %x\n", ReadBack);
	
}

void selAdcPort(struct AdcBoard * Board, uint8_t PortNum)
{
	int PortMap;//three bits to write for port select
	int CurMap;//currentMap
	int WriteMap;//i2c writen map
	Board->PortSel = PortNum;
	switch (PortNum)
	{
		case 0: PortMap = 4;
		case 1: PortMap = 5;
		case 2: PortMap = 6;
		case 3: PortMap = 7;
	}
	
	i2c_read_from_16reg(Board->I2cHandle, 1, &CurMap, 1);
	WriteMap = CurMap & 0x8fff;//scrub the three bits 
	WriteMap = WriteMap | (PortMap << 12);
	i2c_write_to_16reg(Board->I2cHandle, 1, &WriteMap, 1);
	
} 
float readAdc(struct AdcBoard * Board)
//reads currently selected pin
{
	float ReadVolts;
	//i2c_read_from_16reg(Board->I2cHandle, 0, &ReadVolts, 1);
	ReadVolts =  system("i2cget -y 1 0x48 0  w");

	printf("raw value from adc is %0.4f\n", ReadVolts);
	printf("pin being read %d\n", Board->PortSel);
	ReadVolts *= (Board->StepVolt / 1000000);
	
	return ReadVolts;
	
}

#include "adclib.h"
#include <stdlib.h>
#include "i2c.h"

void initADC(struct AdcBoard * Board, int BusAddr)
//takes a adc board pointer
{
	uint16_t ConWord;

//	struct AdcBoard NewBoard;
	Board->PortSel = 1;
	Board->BusAddr = BusAddr;
	Board->SampRate = 16;
	Board->I2cHandle = i2c_init(1, BusAddr, 0);
	Board->StepVolt = 187.5;
	
	ConWord = 0x8020;//16 bits of config data
	
	i2c_write_to_16reg(Board->I2cHandle, 1, &ConWord, 1);
	
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
	i2c_read_from_16reg(Board->I2cHandle, 0, &ReadVolts, 1);
	ReadVolts *= (Board->StepVolt / 1000000);
	
	return ReadVolts;
	
}

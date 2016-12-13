#include "adclib.h"
#include <unistd.h>
#include <stdio.h>

struct AdcBoard TestBrd;
float Voltage;

int main(void)
{	

	initAdc(&TestBrd, 0x48);
	selAdcPort(&TestBrd,0);
	
	while(1)
	{
		Voltage = readAdc(&TestBrd);	
		printf("voltage read is %0.2f volts\n", Voltage);
		
		usleep(500*1000);
		
	}
	
	return 0;
}

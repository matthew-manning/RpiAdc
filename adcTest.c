#include "adclibalt.h"
#include <unistd.h>
#include <stdio.h>

struct AdcBoard TestBrd;
float Voltage;
int i;

int main(void)
{	

	initAdc(&TestBrd, 0x48);
	selAdcPort(&TestBrd,0);
	
	while(1)
	{
	
		for(i = 0; i < 4; i++)
		{
			printf("*********************************************************************************************************************\n");
			selAdcPort(&TestBrd, i);
		
			Voltage = readAdc(&TestBrd);	
			printf("voltage read is %0.2f volts\n", Voltage);
			
			usleep(500*1000);
		}
	}
	
	return 0;
}

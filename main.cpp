#include "mbed.h"

//DigitalOut led1(LED1);
Serial pc(USBTX, USBRX);
// main() runs in its own thread in the OS
int main()
{
	for(;;)
	{
		pc.printf("Hello World!\r\n");
		wait(0.3);
	}
}

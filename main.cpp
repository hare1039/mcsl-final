#include "mbed.h"
#include "Serial.h"
#include "PinNames.h"
#include <queue>

#define sample_freq 16000.0

Serial bt(D10, D2, 9600);
Serial pc(USBTX, USBRX, 115200);
AnalogOut speaker(A2);
Ticker tick;

std::queue<int> data;
void audio_sample()
{
	if (not data.empty())
	{
//		pc.printf("%d ", data.front());
		speaker.write_u16(data.front());
		data.pop();
	}
}

unsigned char buffer[16*1024];

int main()
{
	tick.attach(&audio_sample, 1.0 / sample_freq);
	for(;;)
	{
//		bt.printf("hi");
		pc.read (buffer, 16*1024, [](int x)
		    {
			    bt.printf("reads\r\n");
			    for (int i(0); i < 16*1024; i += 2)
			    {
				    int p = ((static_cast<int>(buffer[i]) << 8) | buffer[i+1]);
				    bt.printf("%d ", p);
			        data.push(p);
			    }
//			    pc.printf("data size %d\r\n", data.size());
		    });
	}
}

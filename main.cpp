#include "mbed.h"
#include "Serial.h"
#include "PinNames.h"
#include "xz.h"
#include <queue>

#define sample_freq 16000.0

Serial bt(D10, D2, 9600);
Serial pc(USBTX, USBRX, 9600);
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

constexpr int buffer_size = 8*1024;
unsigned char buffer[buffer_size];
unsigned char buffer_next[buffer_size];


int main()
{
	tick.attach(&audio_sample, 1.0 / sample_freq);
	for(;;)
	{
		bt.read (buffer, buffer_size, [](int x)
		    {
			    bt.printf("reads\r\n");
			    
			    for (int i(0); i < buffer_size; i += 2)
			    {
				    int p = ((static_cast<int>(buffer_next[i]) << 8) | buffer_next[i+1]);
				    pc.printf("%d ", p);
			        data.push(p);
			    }
//			    pc.printf("data size %d\r\n", data.size());
		    });
	}
}

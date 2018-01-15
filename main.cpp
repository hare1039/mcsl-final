#include "mbed.h"
#include "Serial.h"
#include "PinNames.h"
#include <deque>

#define sample_freq 16000.0

Serial bt(D10, D2);
Serial pc(USBTX, USBRX);
AnalogOut speaker(A2);
Ticker sampletick;

std::deque<unsigned short> data;
void audio_sample()
{
	if (not data.empty())
	{
		speaker.write_u16(data.front());
		data.pop_front();
	}
}

unsigned short buffer[128];

int main()
{
//	sampletick.attach(&audio_sample, 1.0 / sample_freq);
	for(int i(0);;i++)
	{
		bt.read (buffer, 128, [](){
			for (int i(0); i<128; i++)			
				data.push_back(data[i]);			
	   	});
        if (i % 10000 == 0)
	        pc.printf(">> %d \r\n", data.back());
	}
}

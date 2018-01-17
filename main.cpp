#include "mbed.h"
#include "Serial.h"
#include "PinNames.h"
#include <queue>
#include <string>


constexpr float sample_freq = 16000.0;

Serial bt(D10, D2);
Serial pc(USBTX, USBRX, 230400);
AnalogOut speaker(A2);
Ticker tick, tick2;

constexpr int buffer_size = 19000; 
std::queue<int> data;
bool play_started = false;
void audio_sample()
{
	if (data.size() > buffer_size || play_started)
	{
		speaker.write_u16(data.front());
		data.pop();
	    play_started = data.empty()? false: true;
	}
} 

int main()
{
	std::string command;
	for (;;)
	{
		char c = pc.getc();
		if (c == '\r')
		{
			bt.printf("%s", command.c_str());
			while (bt.readable())
			{
				pc.putc(bt.getc());
			}
		}
		else
		{
			command += c;
		}
		pc.putc(c);
	}
		
	
	tick.attach(&audio_sample, 1.0 / sample_freq);
	tick2.attach([](){pc.printf("data size: %d && start: %d\r\n", data.size(), play_started);}, 1.0 );

	for (;;)
	{
		int i = bt.getc() << 8 | bt.getc();
		data.push(i);
	}
}

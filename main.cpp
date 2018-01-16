#include "mbed.h"
#include "Serial.h"
#include "PinNames.h"
#include <queue>

#define sample_freq 16000.0

Serial bt(D10, D2, 230400);
Serial pc(USBTX, USBRX, 230400);
AnalogOut speaker(A2);
Ticker tick, tick2;

std::queue<int> data;
void audio_sample()
{
	if (not data.empty())
	{
		speaker.write_u16(data.front());
		data.pop();
	}
}

constexpr int buffer_size = 8*1024;
unsigned char buffer0[buffer_size];
bool buffer0_ok = false;
unsigned char buffer1[buffer_size];
bool buffer1_ok = false;


int main()
{
	tick.attach(&audio_sample, 1.0 / sample_freq);
	tick2.attach([](){pc.printf("data size: %d\r\n", data.size());}, 1.0 );
	bt.read (buffer0, buffer_size, [](int x){ buffer0_ok = true; });
	for(;;)
	{
		if (buffer0_ok)
		{
			pc.printf("buffer0_ok\r\n");
			buffer0_ok = false;
			for (int i(0); i < buffer_size; i += 2)
			{
				int p = ((static_cast<int>(buffer0[i]) << 8) | buffer0[i+1]);
				data.push(p);
			}
			bt.read (buffer0, buffer_size, [](int x){ buffer0_ok = true; });
		}
		if (buffer1_ok)
		{
			pc.printf("buffer1_ok\r\n");
			buffer1_ok = false;
			for (int i(0); i < buffer_size; i += 2)
			{
				int p = ((static_cast<int>(buffer1[i]) << 8) | buffer1[i+1]);
//x				pc.printf("%d ", p);
				data.push(p);
			}
			bt.read (buffer0, buffer_size, [](int x){ buffer0_ok = true; });
		}
	}
}

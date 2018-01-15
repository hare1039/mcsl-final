#include "mbed.h"
#include "Serial.h"
#include "PinNames.h"
#include "wav.h"
#include <deque>

#define sample_freq 16000.0

Serial bt(D10, D2);
Serial pc(USBTX, USBRX);
AnalogOut speaker(A2);
Ticker sampletick;

// std::deque<unsigned short> data;
void audio_sample()
{
	static int i(0);
	speaker.write_u16(data[i]);
	i++;
}

int main()
{
//	for(int i(0); i < 100; i++)
//	{
//		char c = pc.getc();
//		bt.printf("%c\n\r", c);
//		audio.period(2.0f);
//		audio.write(0.50f);
//	}
	for(;;)
	{
//		bt.printf("waiting...\n\r");
		wait(1.0);
        sampletick.attach(&audio_sample, 1.0 / sample_freq);
    }
}

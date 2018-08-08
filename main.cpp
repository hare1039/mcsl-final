#include "mbed.h"
#include "Serial.h"
#include "PinNames.h"
//#include "p.h"
#include <queue>
#include <string>


constexpr float sample_freq = 11200.0;

Serial bt(D10, D2, 230400);
Serial pc(USBTX, USBRX);
AnalogOut speaker(A2);
Ticker tick, tick2;

constexpr int buffer_size = 19000; 
std::queue<int> data;
bool play_started = false;
//static int x = 0;
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
    tick.attach(&audio_sample, 1.0 / sample_freq);
    tick2.attach([](){pc.printf("data size: %d && start: %d\r\n", data.size(), play_started);}, 3.0 );

    for (;;)
    {
        int i = bt.getc() << 8 | bt.getc();
        data.push(i);
//      pc.printf("%d", i);
    }
}

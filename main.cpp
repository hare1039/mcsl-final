#include "mbed.h"
#include "PinNames.h"
#include "TextLCD.h"
#include <string>

TextLCD lcd(D2, D3, D4, D5, D6, D7); // rs, e, d4-d7
Serial pc(USBTX, USBRX);

int main()
{
	for(;;)
	{
		std::string s;
		for(;;)
		{
			char c = pc.getc();
			if (c == 13)
			{
				pc.printf("\n\r");
				break;
			}
			pc.printf("%c", c);
			s += c;
		}
		lcd.cls();
		lcd.printf("%s", s.c_str());
		pc.printf("%s showed\n\r", s.c_str());
	}
}

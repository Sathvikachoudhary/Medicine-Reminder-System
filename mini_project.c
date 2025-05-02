#include <LPC21XX.H>
#include "lcd.h"
#include "rtc.h"
#include "lcd_defines.h"
#include "keypad.h"
#include "defines.h"
#include "types.h"
#include "delay.h"
#include "mini.h"
#define SW1 27
int main()
{
				Init_BUZZER(); //buzzer initialization
        InitLCD();     //LCD initialization
        Init_RTC();    //RTC initialization
				Keypad_Init(); //Keypad intialization 
				setCLK();      //Set RTC clock
        while(1)
        {
                displayCLK(); //display RTC clock
								if(READBIT(IOPIN1,SW1)==0)
								{
										CmdLCD(CLEAR_LCD);
										CmdLCD(GOTO_LINE1_POS0);
										StrLCD("1.RTC EDIT");
										CmdLCD(GOTO_LINE2_POS0);
										StrLCD("2.M.TIME UPDATE");
										SetCursor(3,4);
										StrLCD("3.BACK");
										Get_Key();  //function from main menu
								}
							Alarm(); //alarm function if RTC time and medicine time matches
        }
}

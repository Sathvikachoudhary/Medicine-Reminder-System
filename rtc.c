#include <LPC21xx.H>
#include "rtc_defines.h"
#include "types.h"
#include "lcd.h"

s8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

void Init_RTC(void)
{

        CCR = RTC_CTC_RESET;    //Reset RTC

        PREINT = PREINT_VAL;   //PRESCALAR Integer Part

        PREFRAC = PREFRAC_VAL; //PRESCALAR Fractional Part

        CCR = RTC_CCR_EN;      //Enable RTC for LPC2148 with External CLK source

}
/////////////////////////////////////////////////
void GetTime_RTC(u32 *hr,u32 *min,u32 *sec)
{
	*hr = HOUR;
	*min = MIN;
	*sec = SEC;	
}
void DisplayTime_RTC(u32 hr,u32 min,u32 sec)
{
	SetCursor(1,0);
	CharLCD((hr/10)+48);
	CharLCD((hr%10)+48);
	CharLCD(':');
	CharLCD((min/10)+48);
	CharLCD((min%10)+48);
	CharLCD(':');
	CharLCD((sec/10)+48);
	CharLCD((sec%10)+48);	
}
void GetDate_RTC(u32 *dt,u32 *mon,u32 *yr)
{
	*dt = DOM;
	*mon = MONTH;
	*yr = YEAR;	
}
void DisplayDate_RTC(u32 dt,u32 mon,u32 yr)
{
	SetCursor(2,0);
	CharLCD((dt/10)+48);
	CharLCD((dt%10)+48);
	CharLCD('/');
	CharLCD((mon/10)+48);
	CharLCD((mon%10)+48);
	CharLCD('/');
	U32LCD(yr);	
}
void GetDay_RTC(u32 *day)
{
	*day = DOW;
}
void DisplayDay_RTC(u32 day)
{
	SetCursor(1,10);
	StrLCD(week[day]);	
}

void SetTime_RTC(u32 hr,u32 min,u32 sec)
{
	HOUR = hr;
	MIN = min;
	SEC =sec;
}
void SetDate_RTC(u32 dt,u32 mon,u32 yr)
{
	DOM = dt;
	MONTH = mon;
	YEAR = yr;
}
void SetDay_RTC(u32 day)
{
	DOW = day;
}

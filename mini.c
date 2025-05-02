#include<LPC21XX.H>
#include "rtc.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"
#include "defines.h"

#define SW2 28
#define BUZZER 24

u32 KeyC,Key;
u32 hour,min,sec,date,month,year,day;
s32 m_hour=-1,m_min=-1,m_sec;
void Init_BUZZER(void)
{
	IODIR0 = 1<<BUZZER;
}
void BUZZER_ON(void)
{
	IOSET0 = 1<<BUZZER;
}
void BUZZER_OFF(void)
{
	IOCLR0 = 1<<BUZZER;
}
void setCLK(void)
{
				CmdLCD(DSP_ON_CUR_OFF);
				CmdLCD(CLEAR_LCD);
				SetCursor(2,2);
				StrLCD("MEDICINE REMIND");
				SetCursor(3,10);
				StrLCD("SYSTEM");
				delay_s(1);
				CmdLCD(CLEAR_LCD);
				SetTime_RTC(7,30,45);
				SetDate_RTC(10,2,2025);
				SetDay_RTC(1);
}
void displayCLK(void)
{
          GetTime_RTC(&hour,&min,&sec); //current time fetches from RTC
          DisplayTime_RTC(hour,min,sec); //display current time from RTC
          GetDate_RTC(&date,&month,&year);//current date fetches from RTC
          DisplayDate_RTC(date,month,year);//display current from RTC
          GetDay_RTC(&day);//current day fetches from RTC
          DisplayDay_RTC(day);//display current day from RTC
}
void Display_MTtime(s32 m_hour,s32 m_min)
{
	CharLCD((m_hour/10)+48); 
	CharLCD((m_hour%10)+48);
	CharLCD(':');
	CharLCD((m_min/10)+48);
	CharLCD((m_min%10)+48);
	CharLCD(':');
	CharLCD((m_sec/10)+48);
	CharLCD((m_sec%10)+48);
}
void Hour(u32 *hour)
{
	s32 res=0,num;
	int digit_count=0;
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		SetCursor(1,0);
		StrLCD("Edit Hour: ");
		num=KeyDetect();
		if(num!=14 && num!=15) //if num not equal to back and enter, num will be stored in res
		{
			res=(res*10)+num; //for accessing multi digit numbers
			U32LCD(res); //display +ve integer values on LCD
			digit_count++;			
		}
		SetCursor(2,8);
		StrLCD("=SAVE");
		if(num==14 && res>0)
		{
			res=res/10;
			if(digit_count>0)
			{
				SetCursor(1,11+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				CharLCD(' ');
				SetCursor(1,11+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				digit_count--;
			}
		}
		else if(num==14)
		{
			return;
		}
		else if(num==15 && res<=23) //hours logic
		{
			HOUR=res;
			*hour=HOUR;
		   return;
		}
		else if(res==24 && num==15) //if hr is 24 reset to 0 again
		{
			HOUR=0;
			CmdLCD(CLEAR_LCD);
			SetCursor(2,2);
			StrLCD("HOUR == 24");
			SetCursor(3,8);
			StrLCD("RESET TO 0");
			delay_s(1);
		return;
		}
		else if(res>24 && num==15) // if >24 display error
		{
			CmdLCD(CLEAR_LCD);
			SetCursor(2,4);
			StrLCD("HOUR > 24");
			SetCursor(3,8);
			StrLCD("DONT EXIST");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			res=0;
		}
	}
}
void Min(u32 *min)
{
	s32 res=0,num;
	int digit_count=0;
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		SetCursor(1,0);
		StrLCD("Edit Min: ");
		num=KeyDetect();
		if(num!=14 && num!=15)
		{
			res=(res*10)+num;
			U32LCD(res);
			digit_count++;
		}
		SetCursor(2,8);
		StrLCD("=SAVE");
		if(num==14 && res>0)
		{
			res=res/10;
			if(digit_count>0)
			{
				SetCursor(1,10+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				CharLCD(' ');
				SetCursor(1,10+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				digit_count--;
			}
		}
		else if(num==14)
		{
			return;
		}
		else if(num==15 && res<=59)
		{
			MIN=res;
			*min=MIN;
			return;
		}
		else if(res==60 && num==15)
		{
			MIN=0;
			CmdLCD(CLEAR_LCD);
			SetCursor(2,2);
			StrLCD("MIN == 60");
			SetCursor(3,8);
			StrLCD("RESET TO 0");
			delay_s(1);
			return;
		}
		else if(res>60 && num==15)
		{
			CmdLCD(CLEAR_LCD);
			SetCursor(2,4);
			StrLCD("MIN > 60");
			SetCursor(3,8);
			StrLCD("DONT EXIST");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			res=0;
		}
	}
}
void Sec(u32 *sec)
{
	s32 res=0,num;
	int digit_count=0;
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		SetCursor(1,0);
		StrLCD("Edit Sec: ");
		num=KeyDetect();
		if(num!=14 && num!=15)
		{
			res=(res*10)+num;
			U32LCD(res);
			digit_count++;
		}
		SetCursor(2,8);
		StrLCD("=SAVE");
		if(num==14 && res>0)
		{
			res=res/10;
			if(digit_count>0)
			{
				SetCursor(1,10+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				CharLCD(' ');
				SetCursor(1,10+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				digit_count--;
			}
		}
		else if(num==14)
		{
			return;
		}
		else if(num==15 && res<=59)
		{
			SEC=res;
			*sec=SEC;
			return;
		}
		else if(res==60 && num==15)
		{
			SEC=0;
			CmdLCD(CLEAR_LCD);
			SetCursor(2,2);
			StrLCD("SEC == 60");
			SetCursor(3,8);
			StrLCD("RESET TO 0");
			delay_s(1);
			return;
		}
		else if(res>60 && num==15)
		{
			CmdLCD(CLEAR_LCD);
			SetCursor(2,4);
			StrLCD("SEC > 60");
			SetCursor(3,8);
			StrLCD("DONT EXIST");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			res=0;
		}
	}
}
void Day(u32 *day)
{
	s32 res=0,num;
	int digit_count=0;
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		SetCursor(1,0);
		StrLCD("Edit Day: ");
		num=KeyDetect();
		if(num!=14 && num!=15)
		{
			res=(res*10)+num;
			U32LCD(res);
			digit_count++;
		}
		SetCursor(2,8);
		StrLCD("=SAVE");
		if(num==14 && res>0)
		{
			res=res/10;
			if(digit_count>0)
			{
				SetCursor(1,10+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				CharLCD(' ');
				SetCursor(1,10+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				digit_count--;
			}
		}
		else if(num==14)
		{
			return;
		}
		else if(num==15 && res<=6)
		{
			DOW=res;
			*day=DOW;
			return;
		}
		else if(res==7 && num==15)
		{
			DOW=0;
			CmdLCD(CLEAR_LCD);
			SetCursor(2,2);
			StrLCD("DAY == 7");
			SetCursor(3,8);
			StrLCD("RESET TO SUN");
			delay_s(1);
			return;
		}
		else if(res>7 && num==15)
		{
			CmdLCD(CLEAR_LCD);
			SetCursor(2,4);
			StrLCD("DAY > 7");
			SetCursor(3,8);
			StrLCD("DONT EXIST");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			res=0;
		}
	}
}
void Date(u32 *date)
{
	s32 res=0,num;
	int digit_count = 0;
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		SetCursor(1,0);
		StrLCD("Edit Date: ");
		num=KeyDetect();
		if(num!=14 && num!=15)
		{
			res=(res*10)+num;
			U32LCD(res);
			digit_count++;
		}
		SetCursor(2,8);
		StrLCD("=SAVE");
		if(num==14 && res>0)
		{
			res = res/10;
			if(digit_count>0)
			{
				SetCursor(1,11+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				CharLCD(' ');
				SetCursor(1,11+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				digit_count--;
			}
		}
		else if(num==14)
		{
			return;
		}
		else if(num==15 && res<=31)
		{
			DOM=res;
			*date=DOM;
			return;
		}
		else if(res>31 && num==15)
		{
			CmdLCD(CLEAR_LCD);
			SetCursor(2,4);
			StrLCD("DATE > 31");
			SetCursor(3,8);
			StrLCD("DONT EXIST");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			res=0;
		}
		
	}
}
void Mon(u32 *month)
{
	s32 res=0,num;
	int digit_count=0;
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		SetCursor(1,0);
		StrLCD("Edit Month: ");
		num=KeyDetect();
		if(num!=14 && num!=15)
		{
			res=(res*10)+num;
			U32LCD(res);
			digit_count++;
		}
		SetCursor(2,8);
		StrLCD("=SAVE");
		if(num==14 && res>0)
		{
			res=res/10;
			if(digit_count>0)
			{
				SetCursor(1,12+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				CharLCD(' ');
				SetCursor(1,12+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				digit_count--;
			}
		}
		else if(num==14)
		{
			return;
		}
		else if(num==15 && res<=12)
		{
			MONTH=res;
			*month=MONTH;
			return;
		}
		else if(res>12 && num==15)
		{
			CmdLCD(CLEAR_LCD);
			SetCursor(2,4);
			StrLCD("MONTH > 12");
			SetCursor(3,8);
			StrLCD("DONT EXIST");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			res=0;
		}
	}
}
void Year(u32 *year)
{
	s32 res=0,num;
	int digit_count=0;
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		SetCursor(1,0);
		StrLCD("Edit Year: ");
		num=KeyDetect();
		if(num!=14 && num!=15)
		{
			res=(res*10)+num;
			U32LCD(res);
			digit_count++;
		}
		SetCursor(2,8);
		StrLCD("=SAVE");
		if(num==14 && res>0)
		{
			res=res/10;
			if(digit_count>0)
			{
				SetCursor(1,11+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				CharLCD(' ');
				SetCursor(1,11+digit_count);
				CmdLCD(SHIFT_CUR_LEFT);
				digit_count--;
			}
		}
		else if(num==14)
		{
			return;
		}
		else if(num==15 && res<=2025)
		{
			YEAR=res;
			*year=YEAR;
			return;
		}
		else if(res>2025 && num==15)
		{
			CmdLCD(CLEAR_LCD);
			SetCursor(2,4);
			StrLCD("YEAR > 2025");
			SetCursor(3,8);
			StrLCD("NOT SUPPORTED");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			res=0;
		}
	}
}
void RTC_SubMenu(void)
{ 
	u32 Key;
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("1.Hour 2.Min");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("3.Sec 4.Day");
		SetCursor(3,4);
		StrLCD("5.Date 6.Month");
		CmdLCD(0xD4);
		StrLCD("7.Year 8.Exit");
		Key=KeyDetect();
		switch(Key)
		{
			case 1:Hour(&hour);
						 break;
			case 2:Min(&min);
							break;
			case 3:Sec(&sec);
							break;
		  case 4:Day(&day);
						 break;
			case 5:Date(&date);
							break;
			case 6:Mon(&month);
							break;
			case 7:Year(&year);
						break;
		  case 8:break;
			default:StrLCD("Invalid Key");
							break;
		}
		CmdLCD(CLEAR_LCD);
		break;
		}
}
void MT_hour(s32 *m_hour)
{
	s32 res=0,num;
	int digit_count=0;
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		SetCursor(1,0);
		StrLCD("Edit MT_Hour: ");
		num=KeyDetect();
		if(num!=14 && num!=15)
		{
			res=(res*10)+num;
			U32LCD(res);
			digit_count++;
		}
		SetCursor(2,8);
		StrLCD("=SAVE");
		if(num==14 && res>0)
		{
				res=res/10;
				if(digit_count>0)
				{
					SetCursor(1,14+digit_count);
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					SetCursor(1,14+digit_count);
					CmdLCD(SHIFT_CUR_LEFT);
					digit_count--;
				}
			}
		else if(num==14)
		{
			return;
		}
		else if(num==15 && res<=23)
		{
			*m_hour=res;
		   return;
		}
		else if(res==24 && num==15)
		{
			*m_hour=-1 ;
			CmdLCD(CLEAR_LCD);
			SetCursor(2,2);
			StrLCD("MT_HOUR == 24");
			SetCursor(3,8);
			StrLCD("RESET TO 0");
			delay_s(1);
			return;
		}
		else if(res>24 && num==15)
		{
			CmdLCD(CLEAR_LCD);
			SetCursor(2,4);
			StrLCD("HOUR > 24");
			SetCursor(3,8);
			StrLCD("NOT SUPPORTED");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			res=0;
		}
	}
}
void MT_min(s32 *m_min)
{
	s32 res=0,num;
	int digit_count=0;
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		SetCursor(1,0);
		StrLCD("Edit MT_min: ");
		num=KeyDetect();
		if(num!=14 && num!=15)
		{
			res=(res*10)+num;
			U32LCD(res);
			digit_count++;
		}
		SetCursor(2,8);
		StrLCD("=SAVE");
		if(num==14 && res>0)
		{
				res=res/10;
				if(digit_count>0)
				{
					SetCursor(1,13+digit_count);
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					SetCursor(1,13+digit_count);
					CmdLCD(SHIFT_CUR_LEFT);
					digit_count--;
				}
			}
		else if(num==14)
		{
			return;
		}
		else if(num==15 && res<=59)
		{
			*m_min=res;
		   return;
		}
		else if(res==60 && num==15)
		{
			*m_min=-1;
			CmdLCD(CLEAR_LCD);
			SetCursor(2,2);
			StrLCD("MT_MIN == 60");
			SetCursor(3,8);
			StrLCD("RESET TO 0");
			delay_s(1);
			return;
		}
		else if(res>60 && num==15)
		{
			CmdLCD(CLEAR_LCD);
			SetCursor(2,4);
			StrLCD("MIN > 60");
			SetCursor(3,8);
			StrLCD("NOT SUPPORTED");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			res=0;
		}
	}
}
void PILL_SubMenu(void)
{
	u32 Key;
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("Enter M.Time: ");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("HH:MM:SS");
		Key=KeyDetect();
		switch(Key)
		{
			case 1:MT_hour(&m_hour);
			case 2:MT_min(&m_min);
						 break;
			case 3:break;
		}
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("M.Time:");
		SetCursor(1,8);
		Display_MTtime(m_hour,m_min);
		SetCursor(2,0);
		StrLCD("Want to update? ");
		SetCursor(3,4);
		StrLCD("1.Yes 2.No");
		Key=KeyDetect();
		switch(Key)
		{
			case 1:CmdLCD(CLEAR_LCD);
						 SetCursor(2,5);
					   StrLCD("UPDATED");
						 SetCursor(3,7);
			       StrLCD("SUCCESSFULLY");
			       delay_s(1);
						 break;
			case 2:CmdLCD(CLEAR_LCD);
						 continue;
		}
		CmdLCD(CLEAR_LCD);
		SetCursor(2,4);
		StrLCD("PILL TIME ON");
		delay_s(1);
		break;
	}
}
void Get_Key() 
{
	KeyC=KeyDetect();
	switch(KeyC)
	{
		case 1:RTC_SubMenu(); 
					 CmdLCD(CLEAR_LCD);
					 break;
		case 2:PILL_SubMenu();
		       CmdLCD(CLEAR_LCD);
						break;
		case 3:break;
	}
	CmdLCD(CLEAR_LCD);
}
void Alarm(void)
{
	if((hour==m_hour)&&(min==m_min)) //if RTC and Med time matches alarm on condition
	{
			CmdLCD(0x01);
			StrLCD("TAKE PILL NOW");
		while(((IOPIN1>>SW2)&1)!=0) //if switch2 not pressed buzzer on
		{
			IOSET0=1<<BUZZER;
		}
		IOCLR0=1<<BUZZER; //if switch2 press buzzer off 
		m_hour=-1; //reset medicine hour time
		m_min=-1;  //reset medicine min time
		CmdLCD(0x01);
	}
}

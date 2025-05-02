#ifndef _RTC_H
#define _RTC_H

#include "types.h"
void Init_RTC(void);
void GetTime_RTC(u32 *,u32 *,u32 *);
void DisplayTime_RTC(u32,u32,u32);
void GetDate_RTC(u32 *,u32 *,u32 *);
void DisplayDate_RTC(u32,u32,u32);
void GetDay_RTC(u32 *);
void DisplayDay_RTC(u32);
void SetTime_RTC(u32,u32,u32);
void SetDate_RTC(u32,u32,u32);
void SetDay_RTC(u32);
#endif

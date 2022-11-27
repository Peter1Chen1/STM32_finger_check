#ifndef _LCD_H_
#define _LCD_H_
#include <stdint.h>
//#include "rtc.h"

//int flag_center=0;
//int flag_lr=0;
//int flag_ud=0;

typedef enum{
	LCD_SLEEP_OUT = 0x11,
	LCD_Pixel_Format = 0x3a,
  LCD_Memory_Data_Access_Control = 0x36,
	LCD_Display_On  		   = 0x29,
	LCD_Display_Off 		   = 0x28, 
	LCD_Column_Address_Set = 0x2a,
	LCD_Row_Address_Set 	 = 0x2b,
	LCD_Memory_Write       = 0x2c,
	LCD_Software_Reset 	   = 0x01,
	LCD_Scroll_Area_Set    = 0x33,
  LCD_Scroll_Start_Address = 0x37,
}LCD_CMD_t;

enum{
  DIGITAL_0 = 0,
	DIGITAL_1 = 1,
	DIGITAL_2 = 2,
	DIGITAL_3 = 3,
	DIGITAL_4 = 4,
	DIGITAL_5 = 5,
	DIGITAL_6 = 6,
	DIGITAL_7 = 7,
	DIGITAL_8 = 8,
	DIGITAL_9 = 9,
	
	CHINESE_1 = 0,
	CHINESE_2 = 1,
	CHINESE_3 = 2,
	CHINESE_4 = 3,
	CHINESE_5 = 4,
	CHINESE_6 = 5,
	CHINESE_WEEK_1 = 6,
	CHINESE_WEEK_2 = 7,
	CHINESE_YEAR   = 8,
	CHINESE_MONTH  = 9,
	CHINESE_DAY    = 10, 
  
  SYMBOL_CONOL = 0,
  SYMBOL_LINE  = 1,  
};

#define COLOR_NAVY   0x000f
#define COLOR_WHITE  0xffff
#define COLOR_DGREEN 0x03E0
#define Green  0x07e0

#define ENGLISH_H_SIZE 8
#define ENGLISH_V_SIZE 16
#define CHINESE_H_SIZE 16
#define CHINESE_V_SIZE 16

extern void LCD_Test(void);
//extern void LCD_Task(RTC_TimeTypeDef time,RTC_DateTypeDef date);
//extern void LCD_Task1(RTC_TimeTypeDef time,RTC_DateTypeDef date,int flag_lr);

#endif

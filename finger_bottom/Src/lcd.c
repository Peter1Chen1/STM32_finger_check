#include <stdint.h>
#include <stdio.h>
#include "logo.h"
#include "font.h"
#include "lcd.h"
#include "spi.h"
extern int flag_ud;
extern int flag_lr;
extern int flag_center;
extern int flag_ud0;
extern int flag_ud1;
extern int flag_ud2;
extern int flag_ud3;
extern int flag_ud4;
extern int flag_ud5;
extern int flag_ud6;
//RTC_TimeTypeDef time0;
//RTC_DateTypeDef date0;
//extern RTC_TimeTypeDef time;
//extern RTC_DateTypeDef date;
//Ƭѡ�͵�ƽ��Ч
void LCD_Chip_Select_On(void)
{
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}
//Ƭѡ�ߵ�ƽʧЧ
void LCD_Chip_Select_Off(void)
{
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}
//�����Ƹߵ�ƽ��Ч���ڱ���·�����޷��ı��ƽֻ�ܸߵ�ƽ
void LCD_Backlight_On(void)
{
	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1, GPIO_PIN_SET);
}
//����ƹر�
void LCD_Backlight_Off(void)
{
	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1, GPIO_PIN_RESET);
}
//�͵�ƽ������
void Set_LCD_Command_Mode(void)
{
	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6, GPIO_PIN_RESET);
}
//�ߵ�ƽ������
void Set_LCD_Data_Mode(void)
{
	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6, GPIO_PIN_SET); 
}
//����Ļic��������
void LCD_Write_Command(uint8_t cmd)
{
	 LCD_Chip_Select_On();
	 Set_LCD_Command_Mode();
	 HAL_SPI_Transmit(&hspi1,&cmd,sizeof(cmd),HAL_MAX_DELAY);
	 LCD_Chip_Select_Off();
	
	 return; 
}
//��Ļ�Դ������λ����
void LCD_Software_Reset_Start(void)
{
	 LCD_Write_Command(LCD_Software_Reset);
	 HAL_Delay(500);
}
//��Ļ�Դ���������
void LCD_Wake_Up(void)
{
	 LCD_Write_Command(LCD_SLEEP_OUT);
	 HAL_Delay(120);
}
//����8λ����
void LCD_Write_Data_8bit(uint8_t data)
{
	 LCD_Chip_Select_On();
	 Set_LCD_Data_Mode();
	 HAL_SPI_Transmit(&hspi1,&data,sizeof(data),HAL_MAX_DELAY); 
	 LCD_Chip_Select_Off();
	 return;
}
//ѡ��RGB565��ɫģʽ
void LCD_Pixel_Format_Init(void)
{
	 LCD_Write_Command(LCD_Pixel_Format);
	 LCD_Write_Data_8bit(0x05);
}
//ѡ���ڴ����ݶ�ȡģʽΪ���е�ַ ���ߵ����� ���ϵ��� ������ ��ȡ����
void LCD_Memory_Data_Access_CTL_Init(void)
{
	LCD_Write_Command(LCD_Memory_Data_Access_Control);
	LCD_Write_Data_8bit(0xc8);
	return;
}
//��Ļ�Դ���������
void LCD_On()
{
	 LCD_Write_Command(LCD_Display_On);
}
//��ʼ����Ļ
void LCD_Init(void)
{
	 LCD_Software_Reset_Start();
	 LCD_Wake_Up();
	 LCD_Pixel_Format_Init();
	 LCD_Memory_Data_Access_CTL_Init();
	 LCD_Backlight_On();
	 LCD_On();
}
//�ȸ�λ���λ�ķ�ʽ����16λ����
void LCD_Write_Data_16bit(uint16_t data)
{
	 uint8_t dataH = data >> 8;
	 uint8_t dataL = data & 0xff;
	
	 LCD_Chip_Select_On();
	 Set_LCD_Data_Mode();
	 HAL_SPI_Transmit(&hspi1,&dataH,sizeof(dataH),HAL_MAX_DELAY); 
	 HAL_SPI_Transmit(&hspi1,&dataL,sizeof(dataL),HAL_MAX_DELAY);
	 LCD_Chip_Select_Off();
}
//ѡ����Ļ����Ҫˢ�����ݵķ�Χ
void LCD_Display_Region_Set(uint16_t Start_X,uint16_t Start_Y,uint16_t End_X,uint16_t End_Y)
{
		//������Ӳ�����������������Ļƫ��
	  uint16_t x_adjust = 2;
	  uint16_t y_adjust = 3;
	  
		Start_X = Start_X + x_adjust;
	  Start_Y = Start_Y + y_adjust;
	  End_X   = End_X   + x_adjust;
	  End_Y   = End_Y   + y_adjust;
		//Ҳ����ֱ���� ����16λ���ݺ���
	  LCD_Write_Command(LCD_Column_Address_Set);
	  LCD_Write_Data_8bit(Start_X >> 8);
		LCD_Write_Data_8bit(Start_X & 0xff);
		LCD_Write_Data_8bit(End_X >> 8);
		LCD_Write_Data_8bit(End_X & 0xff);
	 
	  LCD_Write_Command(LCD_Row_Address_Set);
	  LCD_Write_Data_8bit(Start_Y >> 8);
		LCD_Write_Data_8bit(Start_Y & 0xff);
		LCD_Write_Data_8bit(End_Y >> 8);
		LCD_Write_Data_8bit(End_Y & 0xff);
}
//����ͼƬ ��ʼ���� ͼƬ���ص����� ���ݴ�С ͼƬ����ߵ����ظ���
//������ص������ص��С�����ݴ���
//ͼƬ��ֱ�Ӱ�ѡ�еķ�Χд����ͼƬ������������ɫ,���ַ���ͬ���ַ���������Ҫд�����ص�λ��
void LCD_Draw_Logo(uint16_t x,uint16_t y,uint8_t *buf,uint16_t len,int width,int height)
{
	  int i;
	
	  LCD_Display_Region_Set(x,y,x + width - 1,y + height - 1);
	  LCD_Write_Command(LCD_Memory_Write);
    for(i = 0;i < len;i ++){
			  LCD_Write_Data_8bit(buf[i]);
		}  	
}
//ˢ��������Ļ
void LCD_Clear(uint16_t Color)               
{	
   unsigned int i,m;
   LCD_Display_Region_Set(0,0,128,128);
	 LCD_Write_Command(LCD_Memory_Write);
	
   for(i=0;i<128;i++){
		 for(m=0;m<128;m++){	
			 LCD_Write_Data_16bit(Color);
    }   
	}
	
	LCD_Draw_Logo(14,14,(uint8_t *)gImage_logo,sizeof(gImage_logo),100,26);
}
//ȷ��һ�����ص����ɫ��Ҳ���Ǹ��õ���ɫ
void LCD_Draw_Color_Pix(uint16_t x,uint16_t y,uint16_t color)
{
	 LCD_Display_Region_Set(x,y,x + 1,y + 1);
	 LCD_Write_Command(LCD_Memory_Write);
	 LCD_Write_Data_16bit(color);
}
//дһ������ ��ʼ���� �������ص����� ����ˮƽ���ظ��� ���Ŵ�ֱ���ظ��� ������ɫ
void LCD_Write_Symbol(uint16_t x,uint16_t y,uint8_t *buf,uint16_t hsize,uint16_t vsize,uint16_t color)
{
	 int i,j;
	 int pos = 0;
	 uint8_t pix = 0;
	 
	 for(i = 0;i < vsize;i ++)
	 {
			for(j = 0;j < hsize;j ++)
		  {
				//��ͼƬ��ͬ��8�����ص�Ϊһ�飬�ж�һ�����ļ�������Ҫд��
				//ͼƬ��ֱ�Ӱ�ѡ�еķ�Χд����ͼƬ������������ɫ���ַ���������Ҫд�����ص�λ��
				if(j % 8 == 0)
				{ 
					 pix = buf[pos ++];
				}	
				//��Ҫд�ĵ��ȸ�ԭ�ɱ���ɫ��������Ӱ
				LCD_Draw_Color_Pix(x + j,y + i,COLOR_NAVY);
				//����⵽�����ص���Ҫд����õ���ɫ
				if(pix & 0x80)
				{
					 LCD_Draw_Color_Pix(x + j,y + i,color);
				}
				//��һ����ÿ�����ص㶼Ҫ��⵽
				pix = pix << 1;
			}
	 }
}
//д��λ����
void LCD_Draw_Two_Digital_Symbol(uint16_t *px,uint16_t *py,uint16_t number,uint16_t color)
{
	 uint8_t a;
	 uint8_t b;
	
	 a = number / 10;
	 b = number % 10;
	
	 LCD_Write_Symbol(*px,*py,digital[a],ENGLISH_H_SIZE,ENGLISH_V_SIZE,color);
	 *px += ENGLISH_H_SIZE; 
	
	 LCD_Write_Symbol(*px,*py,digital[b],ENGLISH_H_SIZE,ENGLISH_V_SIZE,color);
	 *px += ENGLISH_H_SIZE; 
}
//дһ������
void LCD_Draw_Chinese_Symbol(uint16_t *px,uint16_t *py,uint16_t number,uint16_t color)
{
	 LCD_Write_Symbol(*px,*py,chinese[number],CHINESE_H_SIZE,CHINESE_V_SIZE,color);
	 *px += CHINESE_H_SIZE; 
}
//дһ�����ð��
void LCD_Draw_Symbol(uint16_t *px,uint16_t *py,uint8_t number,uint16_t color)
{
	 LCD_Write_Symbol(*px,*py,sysmbol[number],ENGLISH_H_SIZE,ENGLISH_V_SIZE,color);
   *px += ENGLISH_H_SIZE;	 
	 return;
}
//д��ʱ��
void LCD_Draw_Time(uint16_t x,uint16_t y,uint16_t hour,uint16_t minute,uint16_t second)
{
	 LCD_Draw_Two_Digital_Symbol(&x,&y,hour,COLOR_WHITE);
	 LCD_Draw_Symbol(&x,&y,SYMBOL_CONOL,COLOR_WHITE);
	 LCD_Draw_Two_Digital_Symbol(&x,&y,minute,COLOR_WHITE);
	 LCD_Draw_Symbol(&x,&y,SYMBOL_CONOL,COLOR_WHITE);
	 LCD_Draw_Two_Digital_Symbol(&x,&y,second,COLOR_WHITE);
}
//��˸Сʱ
void LCD_Draw_Time_Hour(uint16_t x,uint16_t y,uint16_t hour,uint16_t minute,uint16_t second)
{
	HAL_Delay(200);
	 LCD_Draw_Two_Digital_Symbol(&x,&y,hour,COLOR_NAVY);
	 LCD_Draw_Symbol(&x,&y,SYMBOL_CONOL,COLOR_WHITE);
	 LCD_Draw_Two_Digital_Symbol(&x,&y,minute,COLOR_WHITE);
	 LCD_Draw_Symbol(&x,&y,SYMBOL_CONOL,COLOR_WHITE);
	 LCD_Draw_Two_Digital_Symbol(&x,&y,second,COLOR_WHITE);
}
//��˸����
void LCD_Draw_Time_Minute(uint16_t x,uint16_t y,uint16_t hour,uint16_t minute,uint16_t second)
{
	HAL_Delay(200);
	 LCD_Draw_Two_Digital_Symbol(&x,&y,hour,COLOR_WHITE);
	 LCD_Draw_Symbol(&x,&y,SYMBOL_CONOL,COLOR_WHITE);
	 LCD_Draw_Two_Digital_Symbol(&x,&y,minute,COLOR_NAVY);
	 LCD_Draw_Symbol(&x,&y,SYMBOL_CONOL,COLOR_WHITE);
	 LCD_Draw_Two_Digital_Symbol(&x,&y,second,COLOR_WHITE);
}
//��˸����
void LCD_Draw_Time_Second(uint16_t x,uint16_t y,uint16_t hour,uint16_t minute,uint16_t second)
{
	HAL_Delay(200);
	 LCD_Draw_Two_Digital_Symbol(&x,&y,hour,COLOR_WHITE);
	 LCD_Draw_Symbol(&x,&y,SYMBOL_CONOL,COLOR_WHITE);
	 LCD_Draw_Two_Digital_Symbol(&x,&y,minute,COLOR_WHITE);
	 LCD_Draw_Symbol(&x,&y,SYMBOL_CONOL,COLOR_WHITE);
	 LCD_Draw_Two_Digital_Symbol(&x,&y,second,COLOR_NAVY);
}
//д������
void LCD_Draw_Week(uint16_t x,uint16_t y,uint16_t week)
{
	 LCD_Draw_Chinese_Symbol(&x,&y,CHINESE_WEEK_1,COLOR_WHITE);
	 LCD_Draw_Chinese_Symbol(&x,&y,CHINESE_WEEK_2,COLOR_WHITE);
	 if(week == 6){
	   LCD_Draw_Chinese_Symbol(&x,&y,CHINESE_DAY,COLOR_WHITE);
	 }else{
	   LCD_Draw_Chinese_Symbol(&x,&y,week,COLOR_WHITE);
	 }
}
//��˸����
void LCD_Draw_Week_blink(uint16_t x,uint16_t y,uint16_t week)
{
	HAL_Delay(100);
	 LCD_Draw_Chinese_Symbol(&x,&y,CHINESE_WEEK_1,COLOR_NAVY);
	 LCD_Draw_Chinese_Symbol(&x,&y,CHINESE_WEEK_2,COLOR_NAVY);
	 if(week == 6){
	   LCD_Draw_Chinese_Symbol(&x,&y,CHINESE_DAY,COLOR_NAVY);
	 }else{
	   LCD_Draw_Chinese_Symbol(&x,&y,week,COLOR_NAVY);
	 }
}
//д������
void LCD_Draw_Date(uint16_t x,uint16_t y,uint16_t year,uint16_t month,uint16_t day)
{
		LCD_Draw_Two_Digital_Symbol(&x,&y,year/100,COLOR_WHITE);
		LCD_Draw_Two_Digital_Symbol(&x,&y,year%100,COLOR_WHITE);
		LCD_Draw_Symbol(&x,&y,SYMBOL_LINE,COLOR_WHITE);
		LCD_Draw_Two_Digital_Symbol(&x,&y,month,COLOR_WHITE);
		LCD_Draw_Symbol(&x,&y,SYMBOL_LINE,COLOR_WHITE);
		LCD_Draw_Two_Digital_Symbol(&x,&y,day,COLOR_WHITE);
}
//��˸���
void LCD_Draw_Date_Year(uint16_t x,uint16_t y,uint16_t year,uint16_t month,uint16_t day)
{
	HAL_Delay(200);
		LCD_Draw_Two_Digital_Symbol(&x,&y,year/100,COLOR_NAVY);
		LCD_Draw_Two_Digital_Symbol(&x,&y,year%100,COLOR_NAVY);
		LCD_Draw_Symbol(&x,&y,SYMBOL_LINE,COLOR_WHITE);
		LCD_Draw_Two_Digital_Symbol(&x,&y,month,COLOR_WHITE);
		LCD_Draw_Symbol(&x,&y,SYMBOL_LINE,COLOR_WHITE);
		LCD_Draw_Two_Digital_Symbol(&x,&y,day,COLOR_WHITE);
}
//��˸�·�
void LCD_Draw_Date_Mon(uint16_t x,uint16_t y,uint16_t year,uint16_t month,uint16_t day)
{
	HAL_Delay(200);
		LCD_Draw_Two_Digital_Symbol(&x,&y,year/100,COLOR_WHITE);
		LCD_Draw_Two_Digital_Symbol(&x,&y,year%100,COLOR_WHITE);
		LCD_Draw_Symbol(&x,&y,SYMBOL_LINE,COLOR_WHITE);
		LCD_Draw_Two_Digital_Symbol(&x,&y,month,COLOR_NAVY);
		LCD_Draw_Symbol(&x,&y,SYMBOL_LINE,COLOR_WHITE);
		LCD_Draw_Two_Digital_Symbol(&x,&y,day,COLOR_WHITE);
}
//��˸����
void LCD_Draw_Date_Day(uint16_t x,uint16_t y,uint16_t year,uint16_t month,uint16_t day)
{
	HAL_Delay(200);
		LCD_Draw_Two_Digital_Symbol(&x,&y,year/100,COLOR_WHITE);
		LCD_Draw_Two_Digital_Symbol(&x,&y,year%100,COLOR_WHITE);
		LCD_Draw_Symbol(&x,&y,SYMBOL_LINE,COLOR_WHITE);
		LCD_Draw_Two_Digital_Symbol(&x,&y,month,COLOR_WHITE);
		LCD_Draw_Symbol(&x,&y,SYMBOL_LINE,COLOR_WHITE);
		LCD_Draw_Two_Digital_Symbol(&x,&y,day,COLOR_NAVY);
}

void LCD_Test(void)
{
#if 1
	 //int i;	
	 /*A : 8 x 16*/
	 uint8_t a_symbol[] = {0x00,0x00,0x00,0x10,0x10,0x18,0x28,0x28,0x24,0x3C,0x44,0x42,0x42,0xE7,0x00,0x00};
	 
	 /*?: 16 x 16*/
	 uint8_t zhong_symbol[] = {0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,
                             0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00};
#endif	
											 
	LCD_Init();
	//LCD_Clear(COLOR_NAVY);
	LCD_Clear(Green);												 
	
	LCD_Write_Symbol(10,20,a_symbol,8,16,COLOR_WHITE);
	LCD_Write_Symbol(20,30,zhong_symbol,16,16,COLOR_WHITE);

	 													 
														 
	//LCD_Draw_Logo(14,14,(uint8_t *)gImage_logo,sizeof(gImage_logo),100,26);
}
//RTC_TimeTypeDef time;
//RTC_DateTypeDef data;
//void LCD_Task(RTC_TimeTypeDef time,RTC_DateTypeDef date)
//{
//	LCD_Draw_Time(32,56,time.Hours,time.Minutes,time.Seconds);	
//  LCD_Draw_Week(40,72,date.WeekDay-1);
//  LCD_Draw_Date(24,88,2000+date.Year,date.Month,date.Date);
//}

//void LCD_Task1(RTC_TimeTypeDef time,RTC_DateTypeDef date,int flag_lr)
//{
//	//if(flag_center==0)time0=time;
//	if(flag_lr==0)//Сʱ
//		{
//			//RTC_TimeTypeDef time0=time;
//			time0.Hours=time.Hours+flag_ud0;
//			//HAL_RTC_SetTime(&hrtc,&time,RTC_FORMAT_BIN);
//			//LCD_Draw_Time(32,56,time.Hours,time.Minutes,time.Seconds);
//			LCD_Task(time0,date0);
//			HAL_Delay(200);
//			LCD_Draw_Time_Hour(32,56,time0.Hours,time0.Minutes,time0.Seconds);
//		}
//		else if(flag_lr==1)//����
//		{
//			//RTC_TimeTypeDef time0=time;
//			time0.Minutes=time.Minutes+flag_ud1;
//			//HAL_RTC_SetTime(&hrtc,&time,RTC_FORMAT_BIN);
//			//LCD_Draw_Time(32,56,time.Hours,time.Minutes,time.Seconds);
//			LCD_Task(time0,date0);
//			HAL_Delay(200);
//			LCD_Draw_Time_Minute(32,56,time0.Hours,time0.Minutes,time0.Seconds);
//		}
//		else if(flag_lr==2)//����
//		{
//			//RTC_TimeTypeDef time0=time;
//			time0.Seconds=time.Seconds+flag_ud2;
//			//HAL_RTC_SetTime(&hrtc,&time,RTC_FORMAT_BIN);
//			//LCD_Draw_Time(32,56,time.Hours,time.Minutes,time.Seconds);
//			LCD_Task(time0,date0);
//			HAL_Delay(200);
//			LCD_Draw_Time_Second(32,56,time0.Hours,time0.Minutes,time0.Seconds);
//		}
//		else if(flag_lr==3)//����
//		{
//			//LCD_Draw_Time(32,56,time.Hours,time.Minutes,time.Seconds);
//			//RTC_DateTypeDef date0=date;
//			date0.WeekDay=date.WeekDay+flag_ud3;
//			//HAL_RTC_SetDate(&hrtc,&date,RTC_FORMAT_BIN);
//			//LCD_Draw_Week(40,72,date.WeekDay-1);
//			LCD_Task(time0,date0);
//			HAL_Delay(100);
//			LCD_Draw_Week_blink(40,72,date0.WeekDay-1);
//		}
//		else if(flag_lr==4)//���
//		{
//			//LCD_Draw_Time(32,56,time.Hours,time.Minutes,time.Seconds);
//			//LCD_Draw_Week(40,72,date.WeekDay-1);
//			//RTC_DateTypeDef date0=date;
//			date0.Year=date.Year+flag_ud4;
//			//HAL_RTC_SetDate(&hrtc,&date,RTC_FORMAT_BIN);
//			//LCD_Draw_Date(24,88,2000+date.Year,date.Month,date.Date);
//			LCD_Task(time0,date0);
//			HAL_Delay(100);
//			LCD_Draw_Date_Year(24,88,2000+date0.Year,date0.Month,date0.Date);
//		}
//		else if(flag_lr==5)//�·�
//		{
//			//RTC_DateTypeDef date0=date;
//			date0.Month=date.Month+flag_ud5;
//			//HAL_RTC_SetDate(&hrtc,&date,RTC_FORMAT_BIN);
//			//LCD_Draw_Date(24,88,2000+date.Year,date.Month,date.Date);
//			LCD_Task(time0,date0);
//			HAL_Delay(200);
//			LCD_Draw_Date_Mon(24,88,2000+date0.Year,date0.Month,date0.Date);
//		}
//		else if(flag_lr==6)//����
//		{
//			//RTC_DateTypeDef date0=date;
//			date0.Date=date.Date+flag_ud6;
//			//HAL_RTC_SetDate(&hrtc,&date,RTC_FORMAT_BIN);
//			//LCD_Draw_Date(24,88,2000+date.Year,date.Month,date.Date);
//			LCD_Task(time0,date0);
//			HAL_Delay(200);
//			LCD_Draw_Date_Day(24,88,2000+date0.Year,date0.Month,date0.Date);
//		}
//}






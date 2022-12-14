#include "FPM_Finger.h"
#include "usart.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdarg.h"


volatile uint16_t FingerCount = 0;
uint8_t uart2_recv_buf[BUFFER_SIZE];
uint8_t dma_state = 1;
uint8_t UART_SEND_FLAG = 0;


_SYS_CMD_PACK FPM_CMD;       //系统指令实例
uint8_t FPM_Data[128] = {0}; //用于存放指令数据域的值
uint8_t UART_FPM_CMD[256];   //用于存放指令，方面串口发送
uint8_t fcmd_length;
uint16_t Person_num = 0;     //用于标记指纹

/*
*brif:蜂鸣器状态提示
*
*/
void TIP_SUCCESS(void) //成功识别到指纹  短声1次
{
	
}

void TIP_FAILED(void) //指纹识别失败  长声1次
{
	
}

void TIP_WRITE_SUCCESS(void) //指纹录入成功 短声 2次
{
	
}

void TIP_WRITE_FAILED(void) //指纹录入失败   短声1次 长声1次
{
	
}

void TIP_DELATE_ALL(void)  //删除所有指纹模板 长声1次  短声1次
{
	
}

#if 1
/***************************
*brif:串口2发送命令函数
*para:*command  命令地址
*     num       命令长度
*return : 0     成功
*         1     失败
****************************/
uint8_t Commands_Send(uint8_t *command, uint8_t num)
{
	HAL_UART_Transmit_IT(&huart2,command,num);
	HAL_Delay(20);
	if(UART_SEND_FLAG == 1)
	{
		UART_SEND_FLAG = 0;
		return 0;
	}
	else
	{
		return 1;
	}
}
/********************************
*brief:获取系统指令
*para:pid 命令标识符
*     *data 命令数据域指针
*     data_length 命令数据域长度
*return: 返回该指令的总长度
*********************************/
uint8_t Get_FPM_CMD(uint8_t pid, uint8_t *data, uint8_t data_length)
{
	uint8_t i = 0, temp = 0;
	FPM_CMD.Head[0] = 0xEF;
	FPM_CMD.Head[1] = 0x01;
	UART_FPM_CMD[0] = FPM_CMD.Head[0];
	UART_FPM_CMD[1] = FPM_CMD.Head[1];
		
	FPM_CMD.Addr[0] = 0xFF;
	FPM_CMD.Addr[1] = 0xFF;
	FPM_CMD.Addr[2] = 0xFF;
	FPM_CMD.Addr[3] = 0xFF;
	UART_FPM_CMD[2] = FPM_CMD.Addr[0];
	UART_FPM_CMD[3] = FPM_CMD.Addr[1];
	UART_FPM_CMD[4] = FPM_CMD.Addr[2];
	UART_FPM_CMD[5] = FPM_CMD.Addr[3];
	
	FPM_CMD.PID = pid;
	UART_FPM_CMD[6] = FPM_CMD.PID;
	
	FPM_CMD.Length[0] = (data_length + 2) >> 8;
	FPM_CMD.Length[1] = data_length + 2;
	UART_FPM_CMD[7] = FPM_CMD.Length[0];
	UART_FPM_CMD[8] = FPM_CMD.Length[1];
	
	FPM_CMD.Data = data;
	for(i=0; i<data_length; i++)
	{
		temp += FPM_CMD.Data[i];
		UART_FPM_CMD[9+i] = FPM_CMD.Data[i];
	}
	
	FPM_CMD.SUM[0] = (pid + temp + data_length + 2) >> 8;
	FPM_CMD.SUM[1] = (pid + temp + data_length + 2);
	UART_FPM_CMD[9+data_length] = FPM_CMD.SUM[0];
	UART_FPM_CMD[10+data_length] = FPM_CMD.SUM[1];
	
	return 11+data_length;
}

/***********************************
*brief：系统指令数据域值获取
*para：para_num 该函数传入参数的个数
*      ...  随便传入需要的参数
*return: 返回数据域的长度
************************************/
uint8_t Get_FPM_CMD_Data_area(uint8_t para_num, ...)
{
	uint8_t num = 0;
	va_list valist; //用于存放参数
	va_start(valist, para_num);
	for(num=0; num < para_num; num++){
		FPM_Data[num] = va_arg(valist,int); //将第二个参数存入全局
	}
	va_end(valist);
	return para_num;
}

/********************
*brief:串口打印数据
*********************/
void SHOW_CMD(uint8_t *ch, uint8_t size)
{
	uint8_t i;
	for(i=0; i<size; i++)
	{
		printf("%02x ",ch[i]);
	}
	printf("\n");
}

/*******************************************************
*brif:探测指纹，如果探测到将指纹图像存于ImageBuffer
*para:no
*return: 0 探测成功
*        1 2 3 4探测失败
********************************************************/
uint8_t Find_Finger_And_Save_ImageBuffer(void)
{
	memset(uart2_recv_buf,0,sizeof(uart2_recv_buf));
	fcmd_length = Get_FPM_CMD(0x01,FPM_Data,Get_FPM_CMD_Data_area(1,GENIMG)); //获取检测指纹图像命令
#if DEBUG
	SHOW_CMD(UART_FPM_CMD,fcmd_length);
#endif
	while(Commands_Send(UART_FPM_CMD,fcmd_length) != 0);
	//printf("161\r\n");
	HAL_Delay(600);//延时不能太少
	if((uart2_recv_buf[9] == 0x00) && (uart2_recv_buf[6] == 0x07)) //表示指纹录入成功
	{
#if DEBUG
		printf("指纹探测成功\n");
#endif
		return 0;
	}
	else if(uart2_recv_buf[9] == 0x01)
	{
#if DEBUG
		printf("收包有错\n");
#endif		
		return 1;
	}
	else if(uart2_recv_buf[9] == 0x02)
	{
#if DEBUG
		printf("没有检测到手指\n");
#endif		
		return 2;
	}
	else if(uart2_recv_buf[9] == 0x03)
	{
#if DEBUG
		printf("手指录入不成功\n");
#endif
		return 3;
	}
	else
	{
		printf("193:error:%#x\r\n",uart2_recv_buf[9]);
		printf("194:error:%#x\r\n",uart2_recv_buf[6]);
		return 4;
	}
}

/************************************************************
*brif:获取指纹图像特征码，存放到CharBuffer1或者CharBuffer2
*para: area_num 区号
*return : 0         success
*         1 2 3 4 5 failed
*************************************************************/
uint8_t Get_Finger_Feature_Save_To_CharBuffer1or2(uint8_t area_num)
{
  memset(uart2_recv_buf,0,sizeof(uart2_recv_buf));
	fcmd_length = Get_FPM_CMD(0x01,FPM_Data,Get_FPM_CMD_Data_area(2,IMG2TZ,area_num)); 
#if DEBUG
	SHOW_CMD(UART_FPM_CMD,fcmd_length);
#endif
	while(Commands_Send(UART_FPM_CMD,fcmd_length) != 0);
	HAL_Delay(600);//延时不能太少	
	if((uart2_recv_buf[9] == 0x00) && (uart2_recv_buf[6] == 0x07))//表示生成特征成功
	{
#if DEBUG
		printf("生成特征成功\n");
#endif
		return 0;		
	}
	else if(uart2_recv_buf[9] == 0x01)
	{
#if DEBUG
		printf("收包出错\n");
#endif
		return 1;
	}
	else if(uart2_recv_buf[9] == 0x06)
	{
#if DEBUG
		printf("指纹图像太乱而生不成特征\n");
#endif
		return 2;
	}
	else if(uart2_recv_buf[9] == 0x07)
	{
#if DEBUG
		printf("指纹图像正常，但特征点太少而生不成特征\n");
#endif
		return 3;		
	}
	else if(uart2_recv_buf[9] == 0x15)
	{
#if DEBUG
		printf("图像缓冲区内没有有效原始图而生不成图像\n");
#endif
		return 4;		
	}
	else
	{
		return 5;
	}
}

/*******************************************************
*brif:合并CharBuffer1和CharBuffer2中的特征码成指纹模板
*para:no
*return:  0     success
*         1 2 3 failed
********************************************************/
uint8_t Combine_Finger_Feature(void)
{
  memset(uart2_recv_buf,0,sizeof(uart2_recv_buf));
	fcmd_length = Get_FPM_CMD(0x01,FPM_Data,Get_FPM_CMD_Data_area(1,REGMODEL)); 
#if DEBUG
	SHOW_CMD(UART_FPM_CMD,fcmd_length);
#endif
	while(Commands_Send(UART_FPM_CMD,fcmd_length) != 0);
	HAL_Delay(600);//延时不能太少	
	if((uart2_recv_buf[9] == 0x00) && (uart2_recv_buf[6] == 0x07))//表示特征合并成功
	{
#if DEBUG
		printf("特征模板合并成功\n");
#endif
		return 0;				
	}
	else if(uart2_recv_buf[9] == 0x01)
	{
#if DEBUG
			printf("收包有错\n");
#endif
		return 1;
	}
	else if(uart2_recv_buf[9] == 0x0a)
	{
#if DEBUG
		printf("合并失败，两枚指纹不属于同一手指\n");
#endif
		return 2;
	}
	else
	{
		return 3;
	}
}

/*************************************************************************
*brif:将指纹模板存放到Flash指定位置
*para:BufferID  缓冲区CharBuffer1、和CharBuffer2的BufferID分别为0x01 0x02
*return:0       success
*       1 2 3 4 failed
**************************************************************************/
uint8_t Save_Finger_Form_To_Flash_Position(uint8_t BufferID, uint16_t PageID)
{
  memset(uart2_recv_buf,0,sizeof(uart2_recv_buf));
	fcmd_length = Get_FPM_CMD(0x01,FPM_Data,Get_FPM_CMD_Data_area(4,STORE,BufferID,(PageID>>8),PageID)); 
#if DEBUG
	SHOW_CMD(UART_FPM_CMD,fcmd_length);
#endif
	while(Commands_Send(UART_FPM_CMD,fcmd_length) != 0);
	HAL_Delay(600);//延时不能太少	
	if((uart2_recv_buf[9] == 0x00) && (uart2_recv_buf[6] == 0x07))//表示特征合并成功
	{
#if DEBUG
		printf("指纹模板存放成功\n");
#endif
		return 0;
	}		
	else if(uart2_recv_buf[9] == 0x01)
	{
#if DEBUG
		printf("收包有错\n");
#endif
		return 1;
	}
	else if(uart2_recv_buf[9] == 0x0B)
	{
#if DEBUG
		printf("PageID超出指纹库范围\n");
#endif
		return 2;
	}
	else if(uart2_recv_buf[9] == 0x18)
	{
#if DEBUG
		printf("写FLASH出错\n");
#endif
		return 3;
	}
	else
	{
		return 4;
	}
}
/**************************************************************************
*brif:搜索指纹库
*para:BufferID  缓冲区CharBuffer1、CharBuffer2的BufferID分别为0x01 和 0x02
*     Page_start  搜索指纹库的起始页
*     Page_num    需要搜索的页数
*return:0     success
*       1 2 3 failed
***************************************************************************/
uint16_t Search_Finger_In_Finlib(uint8_t BufferID, uint16_t Page_start, uint16_t Page_num)
{
	uint16_t page = 0;
	uint16_t score = 0;
  memset(uart2_recv_buf,0,sizeof(uart2_recv_buf));
	fcmd_length = Get_FPM_CMD(0x01,FPM_Data,Get_FPM_CMD_Data_area(6,SEARCH,BufferID,(Page_start>>8),Page_start,(Page_num>>8),Page_num)); 
#if DEBUG
	SHOW_CMD(UART_FPM_CMD,fcmd_length);
#endif
	while(Commands_Send(UART_FPM_CMD,fcmd_length) != 0);
	HAL_Delay(600);//延时不能太少	
	if((uart2_recv_buf[9] == 0x00) && (uart2_recv_buf[6] == 0x07))//表示指纹搜索到
	{
		page = ((uart2_recv_buf[10] & 0x00FF) << 8) + (uart2_recv_buf[11]);
		score = ((uart2_recv_buf[12] & 0x00FF) << 8) + (uart2_recv_buf[13]);
		Person_num = page;
#if DEBUG
		printf("搜索到指纹，存放于: %d 页，得分: %d\n",page,score);
#endif
		return 0;
	}
	else if(uart2_recv_buf[9] == 0x01)
	{
#if DEBUG
		printf("收包有错\n");
#endif
		return 1;
	}
	else if(uart2_recv_buf[9] == 0x09)
	{
#if DEBUG
		printf("没有搜索到该指纹\n");
#endif
		return 2;
	}
	else
	{
		return 3;
	}
}

/*****************************
*brif:清空指纹库
*para:no
*return: 0     success
*        1 2 3 failed
******************************/
uint8_t Empty_The_FinLib(void)
{
  memset(uart2_recv_buf,0,sizeof(uart2_recv_buf));
	fcmd_length = Get_FPM_CMD(0x01,FPM_Data,Get_FPM_CMD_Data_area(1,EMPTY)); 
#if DEBUG
	SHOW_CMD(UART_FPM_CMD,fcmd_length);
#endif
	while(Commands_Send(UART_FPM_CMD,fcmd_length) != 0);
	HAL_Delay(600);//延时不能太少	
	if((uart2_recv_buf[9] == 0x00) && (uart2_recv_buf[6] == 0x07))//表示清空成功
	{
#if DEBUG
		printf("清空指纹库成功\n");
#endif
		return 0;
	}
	else if(uart2_recv_buf[9] == 0x01)
	{
#if DEBUF
		pirntf("收包出错\n");
#endif
		return 1;
	}
	else if(uart2_recv_buf[9] == 0x11)
	{
#if DEBUG
		printf("清空指纹库失败\n");
#endif
		return 2;
	}
	else
	{
		return 3;
	}
}

/*******************************************************************************
*brif:将flash数据库中指定ID号的指纹模板读入到模板缓冲区CharBuffer1或CharBuffer2
*para:BufferID  缓冲区CharBuffer1、CharBuffer2的BufferID分别为0x01 和 0x02
*     PageID    指纹页ID
*return:0   success   else  failed
********************************************************************************/
uint8_t Read_Finger_Form_From_Flash(uint8_t BufferID,uint16_t PageID)
{
  memset(uart2_recv_buf,0,sizeof(uart2_recv_buf));
	fcmd_length = Get_FPM_CMD(0x01,FPM_Data,Get_FPM_CMD_Data_area(1,LOADCHAR,BufferID,(PageID>>8),PageID)); 
#if DEBUG
	SHOW_CMD(UART_FPM_CMD,fcmd_length);
#endif
	while(Commands_Send(UART_FPM_CMD,fcmd_length) != 0);
	HAL_Delay(600);//延时不能太少	
	if((uart2_recv_buf[9] == 0x00) && (uart2_recv_buf[6] == 0x07))
	{
#if DEBUG
		printf("读指纹模板成功\n");
#endif
		return 0;
	}
	else if(uart2_recv_buf[9] == 0x01)
	{
#if DEBUG
		printf("收包有错\n");
#endif
		return 1;
	}
	else if(uart2_recv_buf[9] == 0x0c)
	{
#if DEBUG
		printf("读出有错或模板无效\n");
#endif
		return 2;
	}
	else if(uart2_recv_buf[9] == 0x0B)
	{
#if DEBUG
		printf("PageID超出指纹库范围\n");
#endif
		return 3;
	}
	else 
	{
		return 4;
	}
}
#endif

uint8_t Delete_The_Finger(uint16_t PageID,uint16_t Page_num)
{
  memset(uart2_recv_buf,0,sizeof(uart2_recv_buf));
	fcmd_length = Get_FPM_CMD(0x01,FPM_Data,Get_FPM_CMD_Data_area(5,DELETCHAR ,(PageID>>8),PageID,(Page_num>>8),Page_num)); 
#if DEBUG
	SHOW_CMD(UART_FPM_CMD,fcmd_length);
#endif
	while(Commands_Send(UART_FPM_CMD,fcmd_length) != 0);
	HAL_Delay(600);//延时不能太少	
	if((uart2_recv_buf[9] == 0x00) && (uart2_recv_buf[6] == 0x07))//表示清空成功
	{
#if DEBUG
		printf("删除指纹模板成功\n");
#endif
		return 0;
	}
	else if(uart2_recv_buf[9] == 0x01)
	{
#if 1
		printf("收包出错\n");
#endif
		return 1;
	}
	else if(uart2_recv_buf[9] == 0x10)
	{
#if 1
		printf("删除模板失败！\n");
#endif
		return 2;
	}
	else
	{
		return 3;
	}
}


#ifndef __FPM_FINGER_H
#define __FPM_FINGER_H

#include "stdint.h"



/* ȷ���붨��� */
#define COMMAND_OK 	        			0x00 //��ʾָ��ִ����ϻ�OK
#define RECV_PACKAGE_ERR  				0x01 //��ʾ���ݰ����մ���
#define NO_FINGER           			0x02 //��ʾ��������û����ָ
#define INPUT_FINGER_IMAGE_ERR		0x03 //��ʾ¼��ָ��ͼ��ʧ��
#define FINGER_IMAGE_CHAOS      	0x06 //��ʾָ��ͼ��̫�Ҷ�����������
#define FEATURE_POINT_LESS				0x07 //��ʾָ��ͼ����������������̫�٣������̫С��������������
#define FINGER_NOT_MATCH					0x08 //��ʾָ�Ʋ�ƥ��
#define REACH_NO_FINGER						0x09 //��ʾû������ָ��
#define FEATURE_COMBINE_FAIL			0x0A //��ʾ�����ϲ�ʧ��
#define ADDR_NUM_OVERSTEP       	0x0B //��ʾ����ָ�ƿ�ʱ��ַ��ų���ָ�ƿⷶΧ
#define READ_TEMPLATE_FAIL      	0x0C //��ʾ��ָ�ƿ��ģ��������Ч
#define UPLOAD_FEATURE_FAIL     	0x0D //��ʾ�ϴ�����ʧ��
#define MODER_CANOT_RECV_PACKAGE	0x0E //��ʾģ�鲻�ܽ��ܺ������ݰ�
#define UPLOAD_IMAGE_FAIL         0x0F //��ʾ�ϴ�ͼ��ʧ��
#define DELATE_TEMPLATE_FAIL      0x10 //��ʾɾ��ģ��ʧ��
#define CLEAN_FINGERLIB_EMPTY     0x11 //��ʾ���ָ�ƿ�ʧ��
#define COMMAND_ISNOT_CURRENT     0x13 //��ʾ�����ȷ
#define NO_EFFACT_IMAGE_IN_BUFF   0x15 //��ʾ��������û����Чԭʼͼ��������ͼ��
#define READ_WRITE_FLASH_ERROR    0x18 //��ʾ��дFLASH����
#define UNDEFINED_ERROR           0x19 //��ʾδ����Ĵ���
#define INVALID_REGISTER          0x1A //��ʾ��Ч�Ĵ�����
#define REGISTER_SET_CONTENT_ERR  0x1B //��ʾ�Ĵ����趨���ݴ���
#define TEXT_PAGE_ERROR           0x1C //��ʾ���±�ҳ��ָ������
#define PORT_OPERATION_ERROR      0x1D //�˿ڲ���ʧ��
#define CONFIRMATION_CODE_LENGTH  24


//ϵͳ��ָ��
#define VFYPWD   							0x13  //��֤ģ�����ֿ���
#define SETPWD                0x12  //����ģ�����ֿ���
#define SETADDER              0x15  //����ģ���ַ
#define SETSYSPARA            0x0E  //������������                 
#define CONTROL               0x17  //UART����USBͨѶ�˿ڽ��п��ؿ��ƣ�USB����UART�˿ڽ��п��ؿ���
#define READSYSPARA           0x0F  //��ȡģ���״̬�Ĵ�����ϵͳ�������ò���
#define TEMPLETENUM           0x1D  //��ģ�����Դ洢��ָ��ģ�����
//ָ�ƴ�����ָ��
#define GENIMG                0x01  //̽����ָ��̽�⵽��¼��ָ��ͼ�����ImageBuffer��������¼��ɹ�ȷ���룬��̽�ⲻ����ָ��ֱ�� ��������ָȷ����
#define UPIMAGE               0x0A  //��ģ��ͼ�񻺳���Img_Buffer�е������ϴ�����λ��
#define DOWMIMAGE             0x0B  //��λ������ͼ�����ݵ�ģ��ͼ�񻺳���Img_Buffer��
#define IMG2TZ                0x02  //��ImageBuffer�е�ԭʼͼ������ָ���������ļ�����CharBuffer��CharBuffer2
#define REGMODEL              0x05  //��CharBuffer1��CharBuffer2�е������ļ��ϲ�����ģ�壬�������CharBuffer1��CharBuffer2������������ͬ��
#define UPCHAR                0x08  //������������CharBuffer1��CharBuffer2�е������ļ��ϴ�����λ��
#define DOWNCHAR              0x09  //��λ�����������ļ���ģ���һ��������������
#define STORE                 0x06  //��ָ��������������(buffer1 �� Buffer2)�е�ģ�����ݴ洢��Flashָ�ƿ���ָ��λ��
#define LOADCHAR              0x07  //��flash���ݿ���ָ��ID�ŵ�ָ��ģ����뵽ģ�建����CharBuffer1 �� CharBuffer2
#define DELETCHAR             0x0C  //ɾ��ģ��ָ�ƿ���ָ����һ��(ָ��ID�ſ�ʼ��N��ָ��ģ��)ģ��
#define EMPTY                 0x0D  //ɾ��ģ����ָ�ƿ�������ָ��ģ��
#define Match                 0x03  //ģ�龫ȷ�ȶԣ�1��1��CharBuffer1 �� CharBuffer2�е������ļ��������ȶԽ����
#define SEARCH                0x04  //��CharBuffer1��CharBuffer2�е������ļ����������򲿷�ָ�ƿ⡣�����������򷵻�ҳ�롣
//����ָ��
#define GETRANDOMCODE         0x14  //��ģ��оƬ����һ������������ظ���λ��
#define WRITENOTEPAD          0x18  //��λ��������д����±�ָ��Flashҳ����ָ����READNOTEPAD��Ӧ
#define READNOTEPAD           0x19  //��ȡ���±�ָ��ҳ���ݡ���ָ����Writenotepad��Ӧ

#define COMMAND_CODE_LENGTH   23

#define DEBUG 1

/*                           ָ�����ʽ                          
---------------------------------------------------------------------|
    ��ͷ    ģ���ַ    ����ʶ    ������   ָ����    ����    У���  |
	 0xEF01    xxxx        01H       0x7H     13H    PassWord    sum   |   
	 2bytes   4bytes      1byte     2bytes   1byte     4byte    2byte  |
---------------------------------------------------------------------|

                             Ӧ�����ʽ
----------------------------------------------------------------------|   
     ��ͷ     ģ���ַ      ����ʶ      ������      ȷ����     У��� |
    0xEF01     xxxx          07H          03H         xxH        sum  |
    2bytes    4bytes        1bytes       2bytes      1byte      2bytes|
----------------------------------------------------------------------|
*/



#define DATA_LENGTH 128
#define BUFFER_SIZE 128
/* ��������� */
typedef struct System_Command_Package{
	uint8_t Head[2];						//�����ͷ 0xEF,0x01
	uint8_t Addr[4];						//��ַ��   0xFF,0xFF,0xFF,0xFF
	uint8_t PID;								//����ʶ   0x01(cmd_package),0x02(data_package),0x07(ack_package),0x08(end_package)
	uint8_t Length[2];					//������ = DATA_LENGTH + 2
	uint8_t *Data;              //������
	uint8_t SUM[2];             //У��� = PID + Length + Data
}_SYS_CMD_PACK;

extern volatile uint16_t FingerCount;
extern uint8_t uart2_recv_buf[BUFFER_SIZE];
extern uint8_t dma_state;
extern uint8_t UART_SEND_FLAG;


extern _SYS_CMD_PACK FPM_CMD;       //ϵͳָ��ʵ��
extern uint8_t FPM_Data[128]; //���ڴ��ָ���������ֵ
extern uint8_t UART_FPM_CMD[256];   //���ڴ��ָ����洮�ڷ���
extern uint8_t fcmd_length;
extern uint16_t Person_num;     //���ڱ��ָ��



uint8_t Commands_Send(uint8_t *command, uint8_t num);
uint8_t Get_FPM_CMD(uint8_t pid, uint8_t *data, uint8_t data_length);
uint8_t Get_FPM_CMD_Data_area(uint8_t para_num, ...);
void SHOW_CMD(uint8_t *ch, uint8_t size);
uint8_t Find_Finger_And_Save_ImageBuffer(void);
uint8_t Get_Finger_Feature_Save_To_CharBuffer1or2(uint8_t area_num);
uint8_t Combine_Finger_Feature(void);
uint8_t Save_Finger_Form_To_Flash_Position(uint8_t BufferID, uint16_t PageID);
uint16_t Search_Finger_In_Finlib(uint8_t BufferID, uint16_t Page_start, uint16_t Page_num);
uint8_t Empty_The_FinLib(void);
uint8_t Read_Finger_Form_From_Flash(uint8_t BufferID,uint16_t PageID);
uint8_t Delete_The_Finger(uint16_t PageID,uint16_t Page_num);
void TIP_SUCCESS(void);
void TIP_FAILED(void);
void TIP_WRITE_SUCCESS(void);
void TIP_WRITE_FAILED(void);
void TIP_DELATE_ALL(void);

#endif

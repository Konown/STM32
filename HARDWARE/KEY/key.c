#include "key.h"
#include "delay.h"
#include "oled.h"
#include "timer.h"

 	    
//������ʼ������ 
//PA0.15��PC5 ���ó�����
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTCʱ��

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;//PB14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PB15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;//PC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC5
 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;//PC6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������  
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
//KEY0_PRES��KEY0����
//KEY1_PRES��KEY1����
//WKUP_PRES��WK_UP���� 
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	
	if(key_up&&(KEY5==0||KEY4==0||KEY3==1||KEY2==1))
	{
		key_up=0;
		if(KEY5==0)
		{
		}
		else if(KEY4==0)
		{
		}
		else if(KEY3==1)
		{
		}
		else if(KEY2==1)
		{
		}
	}else if(KEY5==1&&KEY4==1&&KEY3==0&&KEY2==0)key_up=1;
	return 0;// �ް�������
}

#include "dma_adc.h"

volatile uint16_t ADC_ConvertedValue[10][8];//�������ADCת�������Ҳ��DMA��Ŀ���ַ,8ͨ����ÿͨ���ɼ�10�κ���ȡƽ����
         
void adc_dma_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);	
 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;		 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;//ADC��ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue; //�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //����(�����赽�ڴ�)
	DMA_InitStructure.DMA_BufferSize = 8*10; //�������ݵĴ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�̶�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord ; //�������ݵ�λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord ;    //�ڴ����ݵ�λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular  ; //DMAģʽ��ѭ������
	DMA_InitStructure.DMA_Priority = DMA_Priority_High ; //���ȼ�����
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;   //��ֹ�ڴ浽�ڴ�Ĵ���
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //����DMA1��1ͨ��
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
 
	ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //����ADCģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;  //��ֹɨ�跽ʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//��������ת��ģʽ 
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //��ʹ���ⲿ����ת��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //�ɼ������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 8; //Ҫת����ͨ����Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);//����ADCʱ�ӣ�ΪPCLK2��8��Ƶ����9Hz
	
  ADC_TempSensorVrefintCmd(ENABLE); //�����ڲ��¶ȴ�����
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5 );
  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5 );
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_239Cycles5 );
  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_239Cycles5 );
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_239Cycles5 );
  ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_239Cycles5 );
	
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
 
	ADC_ResetCalibration(ADC1);//��λУ׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�У׼�Ĵ�����λ���
 
	ADC_StartCalibration(ADC1);//ADCУ׼
	while(ADC_GetCalibrationStatus(ADC1));//�ȴ�У׼���
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//����û�в����ⲿ����������ʹ���������ADCת��
}

float ADC_Value[8];//�������澭��ת���õ��ĵ�ѹֵ
void ADC1_Average(void)
{
	u8 i,j;
	int sum;
		for(i=0;i<8;i++)
		{
			sum=0;
			for(j=0;j<10;j++)
			{
				sum+=ADC_ConvertedValue[j][i];
			}
			ADC_Value[i]=(float)sum/(10*4096)*3.3;//��ƽ��ֵ��ת���ɵ�ѹֵ
			//��ӡʡ��	
		}
}


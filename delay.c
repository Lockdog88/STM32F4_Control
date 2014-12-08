#include "delay.h"
/*
void delay_ms(unsigned int delay)
{
     TIM7->PSC = F_APB1/1000+1;	//������������� ������������
     TIM7->ARR = delay;	 //������������� �������� ������������ �������, � ������ � �������� ��� ������� ������������ ������� ����������
     TIM7->EGR |= TIM_EGR_UG;	//���������� ������� ���������� ��� ������ ������ � �������� PSC � ARR
     TIM7->CR1 |= TIM_CR1_CEN|TIM_CR1_OPM;	//��������� ������ ������� ���� CEN � ������������� ����� ������ ������� ���������� ���� OPM
     while ((TIM7->CR1&TIM_CR1_CEN)!=0);
}*/

void delay_us(unsigned int delay)
{
     TIM7->PSC = F_APB1/1000000+1;	//������������� ������������
     TIM7->ARR = delay;	 //������������� �������� ������������ �������, � ������ � �������� ��� ������� ������������ ������� ����������
     TIM7->EGR |= TIM_EGR_UG;	//���������� ������� ���������� ��� ������ ������ � �������� PSC � ARR
     TIM7->CR1 |= TIM_CR1_CEN|TIM_CR1_OPM;	//��������� ������ ������� ���� CEN � ������������� ����� ������ ������� ���������� ���� OPM
     while ((TIM7->CR1&TIM_CR1_CEN)!=0);
}

void Delay (unsigned int volatile nCount)
{
	int i;
   for (i=nCount; i!= 0; i--){}
}

void delay_ms(uint32_t ms)
{
volatile uint32_t nCount; //���������� ��� �����
RCC_ClocksTypeDef RCC_Clocks; //���������� ��� ���������� ������� �������
RCC_GetClocksFreq (&RCC_Clocks); //��������� ������� �������� �������

nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms; //������������� �� � �����
for (; nCount!=0; nCount--); //������ ������ �����
}

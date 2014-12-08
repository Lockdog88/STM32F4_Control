#include "delay.h"
/*
void delay_ms(unsigned int delay)
{
     TIM7->PSC = F_APB1/1000+1;	//устанавливаем предделитель
     TIM7->ARR = delay;	 //устанавливаем значение переполнени€ таймера, а значит и значение при котором генерируетс€ —обытие обновлени€
     TIM7->EGR |= TIM_EGR_UG;	//√енерируем —обытие обновлени€ дл€ записи данных в регистры PSC и ARR
     TIM7->CR1 |= TIM_CR1_CEN|TIM_CR1_OPM;	//«апускаем таймер записью бита CEN и устанавливаем режим ќдного прохода установкой бита OPM
     while ((TIM7->CR1&TIM_CR1_CEN)!=0);
}*/

void delay_us(unsigned int delay)
{
     TIM7->PSC = F_APB1/1000000+1;	//устанавливаем предделитель
     TIM7->ARR = delay;	 //устанавливаем значение переполнени€ таймера, а значит и значение при котором генерируетс€ —обытие обновлени€
     TIM7->EGR |= TIM_EGR_UG;	//√енерируем —обытие обновлени€ дл€ записи данных в регистры PSC и ARR
     TIM7->CR1 |= TIM_CR1_CEN|TIM_CR1_OPM;	//«апускаем таймер записью бита CEN и устанавливаем режим ќдного прохода установкой бита OPM
     while ((TIM7->CR1&TIM_CR1_CEN)!=0);
}

void Delay (unsigned int volatile nCount)
{
	int i;
   for (i=nCount; i!= 0; i--){}
}

void delay_ms(uint32_t ms)
{
volatile uint32_t nCount; //переменна€ дл€ счета
RCC_ClocksTypeDef RCC_Clocks; //переменна€ дл€ считывани€ текущей частоты
RCC_GetClocksFreq (&RCC_Clocks); //считываем текущую тактовую частоту

nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms; //пересчитываем мс в циклы
for (; nCount!=0; nCount--); //гон€ем пустые циклы
}

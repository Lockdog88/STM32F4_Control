#include "copterctrl.h"
#include "delay.h"

void PWM_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	GPIO_InitTypeDef PORT;
	PORT.GPIO_Mode = GPIO_Mode_AF;
	PORT.GPIO_Speed = GPIO_Speed_2MHz;
	PORT.GPIO_OType = GPIO_OType_PP;
	PORT.GPIO_PuPd = GPIO_PuPd_UP;
	PORT.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &PORT);
	PORT.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &PORT);
	PORT.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA, &PORT);
	PORT.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &PORT);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2);
	//Разрешаем таймеру использовать ногу PA1, PA2, PA3 для ШИМа
	TIM2->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E);
	TIM2->CCMR1|= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
	TIM2->CCMR2|= (TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2);
	//Настраиваем предделитель чтоб частота ШИМа была в районе 50 Гц
	TIM2->PSC = 6;
	//Запускаем таймер
	TIM2->CR1 |= TIM_CR1_CEN;
}

// Функция устанавливает позицию газа (в процентах)
void set_throttle(uint8_t pos) {
uint32_t tmp=(SERVO_180 - SERVO_0) /100 ;
TIM2->CCR1 = SERVO_0 + tmp * pos;
}
// Функция устанавливает позицию рысканья (в процентах)
void set_rudder(uint8_t pos) {
uint32_t tmp=(SERVO_180 - SERVO_0) /100 ;
TIM2->CCR2 = SERVO_0 + tmp * pos;
}
// Функция устанавливает позицию вперёд/назад(в процентах)
void set_elevator(uint8_t pos) {
uint32_t tmp=(SERVO_180 - SERVO_0) /100 ;
TIM2->CCR3 = SERVO_0 + tmp * pos;
}
// Функция устанавливает позицию влева/вправо (в процентах)
void set_aileron(uint8_t pos) {
uint32_t tmp=(SERVO_180 - SERVO_0) /100 ;
TIM2->CCR4 = SERVO_0 + tmp * pos;
}

void copter_start(void)
{
	set_throttle(25);
	set_rudder(25);
	set_aileron(25);
	set_elevator(25);
	//delay_ms(1500);
	//set_throttle(25);
	//set_rudder(50);
	//set_aileron(50);
	//set_elevator(50);
}

void copter_stop(void)
{
	set_throttle(25);
	set_rudder(50);
	set_aileron(50);
	set_elevator(50);
}

void copter_thr_up_down(void)
{
	int i;
	for (i=25;i<60;i++)
	{
		set_throttle(i);
		Delay(100000);
	}
	for (i=60;i>25;i--)
	{
		set_throttle(i);
		Delay(100000);
	}
}

void stick_center(void)
{
	set_rudder(50);
	set_aileron(50);
	set_elevator(50);
}

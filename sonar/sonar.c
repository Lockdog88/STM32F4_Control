#include "config.h"
#include "sonar/sonar.h"

void TIM2_Init(void) {
  uint16_t PrescalerValue = 0;

  TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
  TIM_OCInitTypeDef         TIM_OCInitStructure;

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_OCStructInit(&TIM_OCInitStructure);

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 65535 - 1;      //in uSecs
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_Cmd(TIM3, ENABLE);
}

float SR04read(void) {
  TIM_SetCounter(TIM3, 0);
  GPIO_SetBits(GPIOC, SR04_TRIG);
  while(TIM_GetCounter(TIM3) < 15);
  GPIO_ResetBits(GPIOC, SR04_TRIG);
  //TIM_SetCounter(TIM2, 0);
  while(!GPIO_ReadInputDataBit(GPIOC, SR04_ECHO));// & (TIM_GetCounter(TIM2) < 50000));
  TIM_SetCounter(TIM3, 0);
  while(GPIO_ReadInputDataBit(GPIOC, SR04_ECHO));// & (TIM_GetCounter(TIM2) < 50000));
  return ((float)TIM_GetCounter(TIM3) * 0.01715 + SR04_OFFSET);
}

void SR04_Init(void) {
  GPIO_InitTypeDef GPIO_InitStructure;

  // configuring clock sources for GPIOC
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  /* Configure SR04 pins: PC6 - TRIGGER */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Configure SR04 pins: PC7 - ECHO */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // hold TRIG pin low
  GPIO_ResetBits(GPIOC, SR04_TRIG);
}

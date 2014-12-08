#include "config.h"
#include "delay.h"
#include "cli/parser.h"
#include "CopterControl/copterctrl.h"

uint16_t data;
microrl_t rl;
microrl_t * prl = &rl;
char* fp;

void USARTs_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	USART_InitTypeDef USART1_params;
	GPIO_InitTypeDef GPIO_port;


	GPIO_port.GPIO_Pin = GPIO_Pin_10;
	GPIO_port.GPIO_Mode = GPIO_Mode_AF;
	GPIO_port.GPIO_OType = GPIO_OType_PP;
	GPIO_port.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_port.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_port);

	//GPIO_port.GPIO_Pin = GPIO_Pin_3;
	//GPIO_port.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//GPIO_Init(GPIOA, &GPIO_port);

	GPIO_port.GPIO_Pin = GPIO_Pin_9;
	GPIO_port.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_port.GPIO_Mode = GPIO_Mode_AF;
	GPIO_port.GPIO_OType = GPIO_OType_PP;
	GPIO_port.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_port);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);

	//GPIO_port.GPIO_Pin = GPIO_Pin_2;
	//GPIO_port.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_port.GPIO_Mode = GPIO_Mode_AF_PP;
	//GPIO_Init(GPIOA, &GPIO_port);

	USART1_params.USART_BaudRate = 115200;
	USART1_params.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_params.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART1_params.USART_Parity = USART_Parity_No;
	USART1_params.USART_StopBits = USART_StopBits_1;
	USART1_params.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART1, &USART1_params);
	//USART_Init(USART2, &USART1_params);
	USART_Cmd(USART1, ENABLE);
	//USART_Cmd(USART2, ENABLE);
}

void CLI_Init(void)
{
	microrl_init (prl, print);
	microrl_set_execute_callback (prl, execute);

	#ifdef _USE_COMPLETE
	// set callback for completion
		microrl_set_complete_callback (prl, complet);
	#endif
	// set callback for Ctrl+C
		microrl_set_sigint_callback (prl, sigint);
}

int main(void)
{
	CLI_Init();
	USARTs_Init();
	PWM_Init();
	set_throttle(25);
	set_rudder(50);
	set_aileron(50);
	set_elevator(50);

    while(1)
    {
    	//print("Started");
    	if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE)!=0)
    			{
    				data = USART_ReceiveData(USART2);
    				//readLidar();
    			}
    	microrl_insert_char (prl, get_char());

  /*  if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE)!=0)
    	    			{
    						data = USART_ReceiveData(USART1);
    					USART_SendData(USART1, data);
    	    			}*/
    }
}

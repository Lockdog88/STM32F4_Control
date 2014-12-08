#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "cli/cli_config.h"
#include "cli/cli_microrl.h"

#define	F_APB1	24000000

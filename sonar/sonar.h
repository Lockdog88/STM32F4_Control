/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SR04_TRIG   (1<<6)
#define SR04_ECHO   (1<<7)
#define SR04_OFFSET 0.8

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint32_t msTicks;

/* Private function prototypes -----------------------------------------------*/
float SR04read(void);
void SR04_Init(void);
void TIM2_Init(void);

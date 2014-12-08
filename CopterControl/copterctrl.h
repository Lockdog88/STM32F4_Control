#include "config.h"


//--------------------------------------------------------
//-Каналы:
//--PA0 - Газ (Throttle)
//--PA1 - Рысканье (Rudder)
//--PA2 - Вперёд/назад (Elevator)
//--PA3 - Влево/вправо (Aileron)
//--------------------------------------------------------

#define SERVO_180 8200
#define SERVO_0 1800

void PWM_Init(void);

void set_throttle(uint8_t pos);
void set_rudder(uint8_t pos);
void set_elevator(uint8_t pos);
void set_aileron(uint8_t pos);
void copter_start(void);
void copter_stop(void);
void copter_thr_up_down(void);
void stick_center(void);

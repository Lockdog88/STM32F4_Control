#include "parser.h"
#include "CopterControl/copterctrl.h"
#include "delay.h"
#include "sonar/sonar.h"

//available  commands
char * keyworld [] = {_CMD_HELP, _CMD_CLEAR, _CMD_INFO, _CMD_SET_THR, _CMD_SET_RUD, _CMD_SET_AIL, _CMD_SET_ELE, _CMD_START, _CMD_STOP};
// 'set/clear' command argements
//char * set_clear_key [] = {_SCMD_PB, _SCMD_PD};
// array for comletion
char * compl_world [_NUM_OF_CMD + 1];

void print(const char* str)
{
	unsigned int i;
	for(i = 0; str[i]; i++)
	{
		while(!USART_GetFlagStatus(USART1,USART_FLAG_TC));
		USART_SendData(USART1,str[i]);
	}
}

char get_char (void)
{
	uint16_t data;
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==0){}
	//data = USART_ReceiveData(USART1);
	data = USART1->DR;
	return data;
}

int execute (int argc, const char * const * argv)
{
	int i = 0;
	// just iterate through argv word and compare it with your commands
	while (i < argc) {
		if (strcmp (argv[i], _CMD_INFO) == 0) {
			print ("STM32 hexacopter control");
			print (MICRORL_LIB_VER);
			print (" Version");
			print (VER);
			print("\n\r");
		} else if (strcmp (argv[i], _CMD_START) == 0) {
			print("\n\r");
			print ("Starting...\n\r");
			copter_start();
		} else if (strcmp (argv[i], _CMD_STOP) == 0) {
			print("\n\r");
			print ("Stop!\n\r");
			copter_stop();
		} else if (strcmp (argv[i], _CMD_THR_UPDN) == 0) {
			print("\n\r");
			print ("Up and Down!\n\r");
			stick_center();
			copter_thr_up_down();
			print ("End!\n\r");
		} else if (strcmp (argv[i], _CMD_GET_SONAR) == 0) {
			char buffer[10];
			print("\n\r");
			sprintf(buffer, "%.0f", SR04read());
			print("Lenght: ");
			print(buffer);
			print("\n\r");
		} else if (strcmp(argv[i], _CMD_SET_THR) == 0){
			if (++i < argc) {
				if ((atoi(argv[i]) < 0) || (atoi(argv[i]) > 100)){
					print ("Wrong value! Only 0..100% range!\n\r");
					print(argv[i]);
					print("\n\r");
					return 1;
				} else {
					set_throttle(atoi(argv[i]));
					print ("New value of Throttle: ");
					print (argv[i]);
					print ("%\n\r");
					return 0;
				}
			}
		} else if (strcmp(argv[i], _CMD_SET_RUD) == 0){
					if (++i < argc) {
						print("\n\r");
						if ((atoi(argv[i]) < 0) || (atoi(argv[i]) > 100)){
							print ("Wrong value! Only 0..100% range!\n\r");
							print(argv[i]);
							print("\n\r");
							return 1;
						} else {
							set_rudder(atoi(argv[i]));
							print ("New value of Rudder: ");
							print (argv[i]);
							print ("%\n\r");
							return 0;
						}
					}
		} else if (strcmp(argv[i], _CMD_SET_AIL) == 0){
			if (++i < argc) {
				print("\n\r");
				if ((atoi(argv[i]) < 0) || (atoi(argv[i]) > 100)){
					print ("Wrong value! Only 0..100% range!\n\r");
					print(argv[i]);
					print("\n\r");
					return 1;
				} else {
					set_aileron(atoi(argv[i]));
					print ("New value of Aileron: ");
					print (argv[i]);
					print ("%\n\r");
					return 0;
				}
			}
		} else if (strcmp(argv[i], _CMD_SET_ELE) == 0){
			if (++i < argc) {
				print("\n\r");
				if ((atoi(argv[i]) < 0) || (atoi(argv[i]) > 100)){
					print ("Wrong value! Only 0..100% range!\n\r");
					print(argv[i]);
					print("\n\r");
					return 1;
				} else {
					set_elevator(atoi(argv[i]));
					print ("New value of Elevator: ");
					print (argv[i]);
					print ("%\n\r");
					return 0;
				}
			}
		} else {
			print ("command: '");
			print ((char*)argv[i]);
			print ("' Not found.\n\r");
		}
		i++;
	}
	return 0;
}

char ** complet (int argc, const char * const * argv)
{
	int j = 0;

	compl_world [0] = NULL;

	// if there is token in cmdline
	if (argc == 1) {
		// get last entered token
		char * bit = (char*)argv [argc-1];
		// iterate through our available token and match it
		int i;
		for (i = 0; i < _NUM_OF_CMD; i++) {
			// if token is matched (text is part of our token starting from 0 char)
			if (strstr(keyworld [i], bit) == keyworld [i]) {
				// add it to completion set
				compl_world [j++] = keyworld [i];
			}
		}
	}

	// note! last ptr in array always must be NULL!!!
	compl_world [j] = NULL;
	// return set of variants
	return compl_world;
}

void sigint (void)
{
	print ("^C catched!\n\r");
}

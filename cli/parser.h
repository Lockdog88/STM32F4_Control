#include "config.h"

#define VER "1.0"
// definition commands word
#define _CMD_HELP   "help"
#define _CMD_INFO   "info"
#define _CMD_CLEAR  "clear"
#define _CMD_SET_THR "set_thr"
#define _CMD_SET_RUD "set_rud"
#define _CMD_SET_AIL "set_ail"
#define _CMD_SET_ELE "set_ele"
#define _CMD_START "c_start"
#define _CMD_STOP "c_stop"
#define _CMD_THR_UPDN "thud"
#define _CMD_GET_SONAR "get_sonar"

#define _NUM_OF_CMD 11
#define _NUM_OF_SETCLEAR_SCMD 2



void print(const char* str);
char get_char (void);
int execute (int argc, const char * const * argv);
char ** complet (int argc, const char * const * argv);
void sigint (void);

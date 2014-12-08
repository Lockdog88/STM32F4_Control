#include "config.h"


unsigned char init_level = 0;
unsigned char b_speed[2];
unsigned char b_data0[4];
unsigned char b_data1[4];
unsigned char b_data2[4];
unsigned char b_data3[4];
unsigned char b =0;
double speed_rpm = 0;
int indexV = 0;
int dist_mm[360] ;
int quality[360] ;

void readLidar();

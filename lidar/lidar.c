#include "lidar.h"
#include "delay.h"
#include "cli/parser.h"

void readLidar()
{
	int i;
    if (init_level ==0)
    {
      b = USART_ReceiveData(USART2);
      if (b == 250) //Start Byte
      {
        init_level = 1;
      }
      else
      {
        init_level = 0;
      }
    }
    else if (init_level == 1)
    { // position index
      b = USART_ReceiveData(USART2);
      if (b >= 160 && b <= 249)
      {
        indexV = b - 160;
        init_level = 2;
      }

      else if (b != 250)
      {
        init_level = 0;
      }
    }
    else if (init_level == 2)
    {// speed
      b_speed[0] = USART_ReceiveData(USART2);
      while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE)==0)
      {
        delay_us(1);
      }
      b_speed[1] = USART_ReceiveData(USART2);
      for (i=0;i<4;i++)
      {
        while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE)==0)
        {
          delay_us(1);
        }
        b_data0[i] = USART_ReceiveData(USART2);
      }
      //decode(b_data0);
      for (i=0;i<4;i++)
      {
        while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE)==0)
        {
          delay_us(1);
        }
        b_data1[i] = USART_ReceiveData(USART2);
      }
      for (i=0;i<4;i++)
      {
        while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE)==0)
        {
          delay_us(1);
        }
        b_data2[i] = USART_ReceiveData(USART2);
      }
      for (i=0;i<4;i++)
      {
        while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE)==0)
        {
          delay_us(1);
        }
        b_data3[i] = USART_ReceiveData(USART2);
      }
      speed_rpm =  ( b_speed[0] | (b_speed[1] << 8) ) / 64.0;
      dist_mm[4*indexV]   = b_data0[0] | ((b_data0[1] & 63) << 8); // distance is coded on 13 bits ? 14 bits ?
      quality[4*indexV]   = b_data0[2] | (b_data0[3] << 8); // quality is on 16 bits
      dist_mm[4*indexV+1] = b_data1[0] | ((b_data1[1] & 63) << 8); // distance is coded on 13 bits ? 14 bits ?
      quality[4*indexV+1] = b_data1[2] | (b_data1[3] << 8); // quality is on 16 bits
      dist_mm[4*indexV+2] = b_data2[0] | ((b_data2[1] & 63) << 8); // distance is coded on 13 bits ? 14 bits ?
      quality[4*indexV+2] = b_data2[2] | (b_data2[3] << 8); // quality is on 16 bits
      dist_mm[4*indexV+3] = b_data3[0] | ((b_data3[1] & 63) << 8); // distance is coded on 13 bits ? 14 bits ?
      quality[4*indexV+3] = b_data3[2] | (b_data3[3] << 8); // quality is on 16 bits
      if (indexV == 89)
      {
    	  print("indexV = 89\n");
    	  for (i = 0; i < 360; i++)
    	        	{
    	        		//USART_SendData(USART1, (dist_mm[i]));
    	        		//USART_SendData(USART1, fp);
    	        		//sprintf(fp, "Dist: %i \n", dist_mm[j]);
    	        		//printf("Dist: %i, Quality: %i, Position: %i \n", dist_mm[i],quality[i],i);
    	        		//print("Hello\n");
    	        		//USART_SendData(USART1, ',');
    	        	}
      }
      delay_ms(10);

      init_level = 0; //reset and wait for next packet
    }
}

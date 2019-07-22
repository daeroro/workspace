/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 07-July-2017
*   @version 04.07.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

#include "HL_system.h"
#include "HL_etpwm.h"
#include "HL_sci.h"

#define UART    sciREG1
#define MAX     50

volatile int delay;
//etpwm4A = E19, etpwm1B = H3, etpwm6B = p2
unsigned int etpwm4A = 0, etpwm1B = 0, etpwm6B = 0;

uint32 receive_data = 0;
/* USER CODE END */

void catch_command(void)
{
    while((UART->FLR & 0x4) == 4)
        ;
        receive_data = sciReceiveByte(UART);
}
void wait(int delay)
{
    int i;

    for(i = 0; i < delay; i++)
        ;
}
int main(void)
{
/* USER CODE BEGIN (3) */
#if 0
    UART에 값을 입력 받아서 PWM을 제어하는 소스입니다.
    제대로 작동 여부는 확실치 않으니 필요한 소스만 긁어서 쓰시지 바랍니다.
#endif
        int flag = 0;
        int tmp = MAX;

        sciInit();
        etpwmInit();

        for(;;)
        {
           // etpwmStartTBCLK();

            if((UART->FLR & 0x200) == 0 && flag == 0)
            {
                wait(100000);

                if(etpwm4A >= (tmp + 50))
                    etpwm4A = 0;
                else
                    etpwm4A++;

                etpwmSetCmpA(etpwmREG4, etpwm4A);

                wait(100000);

                if(etpwm6B >= (tmp + 30))
                    etpwm6B = 0;
                else
                    etpwm6B++;

                etpwmSetCmpB(etpwmREG6, etpwm6B);

                wait(100000);

                if(etpwm1B >=(tmp + 60))
                    etpwm1B = 0;
                else
                    etpwm1B++;

                etpwmSetCmpB(etpwmREG1, etpwm1B);

            }
            else if((UART->FLR & 0x200) == 0 && flag == 1)
            {
                wait(100000);

                if(etpwm4A >= tmp)
                    etpwm4A = 0;
                else
                    etpwm4A++;

                etpwmSetCmpA(etpwmREG4, etpwm4A);

                wait(100000);

                if(etpwm6B >= tmp)
                    etpwm6B = 0;
                else
                    etpwm6B++;

                etpwmSetCmpB(etpwmREG6, etpwm6B);

                if(etpwm1B >= tmp)
                    etpwm1B = 0;
                else
                    etpwm1B++;

                etpwmSetCmpB(etpwmREG1, etpwm1B);

            }
            else
            {
                catch_command();

                if(receive_data == 53)
                {
                    flag = 1;
                    etpwm4A = tmp - 20;
                    etpwm6B = tmp - 20;
                    etpwm1B = tmp - 20;
                }
                else if(receive_data == 48)
                {
                    flag = 0;
                    etpwm4A = 0;
                    etpwm6B = 0;
                    etpwm1B = 0;

                }
            }

            etpwmStopTBCLK();
        }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* USER CODE END */

/*
 * ledMatrixDriver.c
 *
 *  Created on: 12. 5. 2019
 *      Author: lukelee36
 */

#include "Board.h"
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
#include "ledMatrixDriver.h"
#include "ledMatrixGraphic.h"

void lmd_init()
{
    /* Configure the LED pin */
      // GPIO_setConfig(Board_GPIO_LED0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
       GPIO_setConfig(CLKMatrix, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_LOW);
       GPIO_setConfig(AMatrix, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
       GPIO_setConfig(BMatrix, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
       GPIO_setConfig(CMatrix, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
       GPIO_setConfig(LATMatrix, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_LOW);
       GPIO_setConfig(OEMatrix, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_LOW);
       GPIO_setConfig(CLKMatrix, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_LOW);
       GPIO_setConfig(R1Matrix, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_LOW);
       GPIO_setConfig(R2Matrix, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_LOW);
}

void lmd_timer_init()
{
    Timer_Handle timer0;
    Timer_Params params;

    Timer_Params_init(&params);
    params.period = 1250;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback;

    timer0 = Timer_open(Board_TIMER0, &params);

    if (timer0 == NULL) {
       /* Failed to initialized timer */
//       while (1) {}
       // DebugP_log("Failed to initialized timer");
   }

   if (Timer_start(timer0) == Timer_STATUS_ERROR) {
       /* Failed to start timer */
  //     while (1) {}
       //DebugP_log("Failed to start timer");
   }
}

void timerCallback(Timer_Handle myHandle)
{
    static uint8_t addr = 0;
    uint8_t a,b,c = 0;
    //int j = 0, i = 0;

  //  GPIO_toggle(Board_GPIO_LED0);
//    GPIO_toggle(CLKMatrix);

    // zde se momentalne bude menit kazdou sekundu adresa
    if(addr < 7)
    {
        addr = addr + 1;
    }
    else
    {
        addr = 0;
    }

    lmg_loadMatrixData(addr);


    //part for change address
    GPIO_write(LATMatrix, GPIO_CFG_OUT_HIGH);
    GPIO_write(OEMatrix, GPIO_CFG_OUT_HIGH);
    // select address from number to port A, B, C
    a = addr & 0x01;
    b = addr & 0x02;
    c = addr & 0x04;

    if (a)
    {
        GPIO_write(AMatrix, GPIO_CFG_OUT_HIGH);
    }
    else
    {
        GPIO_write(AMatrix, GPIO_CFG_OUT_LOW);
    }

    if (b)
    {
        GPIO_write(BMatrix, GPIO_CFG_OUT_HIGH);
    }
    else
    {
        GPIO_write(BMatrix, GPIO_CFG_OUT_LOW);
    }

    if (c)
    {
        GPIO_write(CMatrix, GPIO_CFG_OUT_HIGH);
    }
    else
    {
        GPIO_write(CMatrix, GPIO_CFG_OUT_LOW);
    }
    //usleep(10);
    GPIO_write(LATMatrix, GPIO_CFG_OUT_LOW);
    GPIO_write(OEMatrix, GPIO_CFG_OUT_LOW);
}

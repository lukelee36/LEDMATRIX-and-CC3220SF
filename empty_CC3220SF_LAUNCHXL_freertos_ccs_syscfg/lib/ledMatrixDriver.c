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



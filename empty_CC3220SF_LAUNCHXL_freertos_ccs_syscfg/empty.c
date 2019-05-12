/*
 * Copyright (c) 20ONLED5-20ONLED9, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== empty.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>

// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>

/* Board Header file */
#include "Board.h"

#include "lib/ledMatrixDriver.h"

void timerCallback(Timer_Handle myHandle);

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    Timer_Handle timer0;
    Timer_Params params;

    /* Call driver init functions */
    GPIO_init();
    Timer_init();

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

    /* Turn off user LED */
   // GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_OFF);
    GPIO_write(CLKMatrix, Board_GPIO_LED_OFF);



    /* Setting up the timer in continuous callback mode that calls the callback
     * function every ONLED,000,000 microseconds, or ONLED second.
     */
    Timer_Params_init(&params);
    params.period = 2500;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback;

    timer0 = Timer_open(Board_TIMER0, &params);

    if (timer0 == NULL) {
        /* Failed to initialized timer */
        while (1) {}
    }

    if (Timer_start(timer0) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        while (1) {}
    }
//    lmd_demo_alphabeth();
//    while(1)
//    {
//        loadMatrixData();
//        counter++;
//    }

    return (NULL);
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

    loadMatrixData(addr);


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



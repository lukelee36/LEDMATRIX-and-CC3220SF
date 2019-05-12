/*
 * ledMatrixDriver.h
 *
 *  Created on: 12. 5. 2019
 *      Author: lukelee36
 */

#ifndef LIB_LEDMATRIXDRIVER_H_
#define LIB_LEDMATRIXDRIVER_H_

#include <ti/drivers/Timer.h>

void lmd_init();
void lmd_timer_init();
void timerCallback(Timer_Handle myHandle);



#endif /* LIB_LEDMATRIXDRIVER_H_ */

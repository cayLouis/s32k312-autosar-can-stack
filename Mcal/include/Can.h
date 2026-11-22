/*
 * Can.h
 *
 *  Created on: 2026年11月18日
 *      Author: 罗灿
 */

#ifndef INCLUDE_CAN_H_
#define INCLUDE_CAN_H_

#include "FlexCan_Ip.h"
#include "Can_Mb.h"
#include "Can_RingBuffer.h"





void Can_Init(void);

void Can_MainFunction(void);


#endif /* INCLUDE_CAN_H_ */

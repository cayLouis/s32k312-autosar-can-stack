/*
 * Can_Mb.h
 *
 *  Created on: 2026年11月20日
 *      Author: 罗灿
 */

#ifndef INCLUDE_CAN_MB_H_
#define INCLUDE_CAN_MB_H_
#include "Can_Mb_Types.h"



extern const Can_MbConfigType Can_MbConfigTable[];

#define MB_CONFIG_NUM (sizeof(Can_MbConfigTable) / sizeof(Can_MbConfigType))

#endif /* INCLUDE_CAN_MB_H_ */

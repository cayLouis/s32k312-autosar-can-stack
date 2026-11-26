/*
 * CanIf.h
 *
 *  Created on: 2026年11月25日
 *      Author: 罗灿
 */

#ifndef CANIF_INCLUDE_CANIF_H_
#define CANIF_INCLUDE_CANIF_H_
#include "ComStack_Types.h"


void CanIf_Init(void);
void CanIf_RxIndication(uint8_t HwChannel, const PduInfoType* pduInfo);


#endif /* CANIF_INCLUDE_CANIF_H_ */

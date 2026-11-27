/*
 * CanIf.h
 *
 *  Created on: 2026年11月25日
 *      Author: 罗灿
 */

#ifndef CANIF_INCLUDE_CANIF_H_
#define CANIF_INCLUDE_CANIF_H_
#include "ComStack_Types.h"

typedef void (*CanIf_RxCallback)(uint16_t PduId, const uint8_t* DataPtr, uint8_t Dlc)

typedef struct {
	uint16_t PduId; // 逻辑序号：PDU ID
	uint32_t CanId; // Can ID
	uint8_t HwChannel; // 物理通道
	uint8_t DefaultDlc; // 默认数据长度
	CanIf_RxCallback RxCallback; // 回调函数指针
} CanIf_PduConfigType;

extern const CanIf_PduConfigType CanIf_PduConfigTable[];
extern const uint8_t CanIf_PduConfigNum;


void CanIf_Init(void);
void CanIf_RxIndication(uint8_t HwChannel, const PduInfoType* pduInfo);
void CanIf_RegisterRxCallback(uint16_t PduId, CanIf_RxCallback callback); // 回调注册


#endif /* CANIF_INCLUDE_CANIF_H_ */

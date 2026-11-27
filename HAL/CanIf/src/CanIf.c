/*
 * CanIf.c
 *
 *  Created on: 2026年11月25日
 *      Author: 罗灿
 */


#include "CanIf.h"


void CanIf_Init(void){

}

void CanIf_RxIndication(uint8_t HwChannel, const PduInfoType* pduInfo) {

}


void CanIf_RegisterRxCallback(uint16_t PduId, CanIf_RxCallback callback) {
	// 根据PDU ID匹配配置表注册回调函数
	for (uint16_t i = 0; i < CanIf_PduConfigNum; i++)
	{
		if (PduId == CanIf_PduConfigTable[i].PduId){
			CanIf_PduConfigTable[i].RxCallback = callback;
		}
	}
}

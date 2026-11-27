/*
 * CanIf_Cfg.c
 *
 *  Created on: 2026年11月27日
 *      Author: 罗灿
 */

#include "CanIf.h"


const CanIf_PduConfigType CanIf_PduConfigTable[] = {
	{ 0, 0x2E3U, 0, 8, NULL},
	{ 1, 0x51U,  0, 8, NULL},
};

const uint8_t CanIf_PduConfigNum = sizeof(CanIf_PduConfigTable) / sizeof(CanIf_PduConfigType); // 配置表大小

/*
 * Can_MbConfig.c
 *
 *  Created on: 2026年11月20日
 *      Author: 罗灿
 */

#include "Can_Mb.h"


const Can_MbConfigType Can_MbConfigTable[] = {
		{
				.MbIndex = 0U,
				.MbType = CAN_MB_RX_FIFO,
				.CanId = 0x2E3U,
				.IdMask = 0x7FFU,
				.isExtended = false,
		}
};

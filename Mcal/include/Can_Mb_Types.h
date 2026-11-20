/*
 * Can_Mb_Types.h
 *
 *  Created on: 2026年11月20日
 *      Author: 罗灿
 */

#ifndef INCLUDE_CAN_MB_TYPES_H_
#define INCLUDE_CAN_MB_TYPES_H_

typedef enum {
	CAN_MB_RX_INDIVIDUAL = 0U, // 独立接收MB
	CAN_MB_TX_STATIC, // 静态发送MB
	CAN_MB_RX_FIFO // Rx_FIFO
} Can_MbType;

typedef struct {
	uint8_t MbIndex; // MB编号
	Can_MbType MbType; // MB类型
	uint32_t CanId; // 匹配目标ID
	uint32_t IdMask; // 接收掩码
	uint32_t dataLength; // 报文长度
	bool IsExtended; // 是否为扩展帧
	bool fdEnable; // 是否为CanFD报文
} Cam_MbConfigType;

#endif /* INCLUDE_CAN_MB_TYPES_H_ */

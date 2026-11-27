/*
 * ComStack_Types.h
 *
 *  Created on: 2026年11月26日
 *      Author: 罗灿
 *      Description：存放COM通信栈数据类型
 */

#ifndef COMSTACK_TYPES_H_
#define COMSTACK_TYPES_H_


typedef struct {
	uint32_t CanId; // CAN ID
	uint8_t Dlc; // 数据长度
	uint8_t* DataPtr; // 数据缓冲区指针
} PduInfoType;



#endif /* COMSTACK_TYPES_H_ */

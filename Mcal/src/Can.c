/*
 * Can.c
 *
 *  Created on: 2026年11月18日
 *      Author: 罗灿
 */


#include "Can.h"

static Can_RingBuffer_t s_RxRingBuf; // 接收Buffer，对外不可见
static Can_RingBuffer_t s_TxRingBuf; // 发送Buffer，对外不可见

static uint32_t s_TxErrorCnt = 0;
static uint32_t s_RxErrorCnt = 0;

void Can_Init(void) {
	// 初始化缓冲区
	Can_RingBuffer_Init(&s_RxRingBuf);
	Can_RingBuffer_Init(&s_TxRingBuf);

	FlexCAN_Ip_Init(INST_FLEXCAN_0, &FlexCAN_State0, &FlexCAN_Config0);
	FlexCAN_Ip_SetRxMaskType(INST_FLEXCAN_0, FLEXCAN_RX_MASK_INDIVIDUAL); // 配置为独立掩码模式

	// 遍历配置表
	for (uint8_t index = 0; index < MB_CONFIG_NUM; index++) {
		const Can_MbConfigType* cfg = &Can_MbConfigTable[index];
		Flexcan_Ip_MsgBuffIdType msg_id_type = cfg->IsExtended ? FLEXCAN_MSG_ID_EXT : FLEXCAN_MSG_ID_STD;

		// 栈局部变量如果不显式赋值，就会存在脏数据
		Flexcan_Ip_DataInfoType RxInfo = {
				.msg_id_type = msg_id_type,
				.data_length = cfg->dataLength,
				.fd_enable = cfg->fdEnable,
				.fd_padding = 0U,
				.enable_brs = TRUE,
				.is_remote = FALSE,
				.is_polling = FALSE
		};

		FlexCAN_Ip_SetRxIndividualMask(INST_FLEXCAN_0, cfg->MbIndex, cfg->IdMask);
		FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, cfg->MbIndex, &RxInfo, cfg->CanId);
	}

	FlexCAN_Ip_SetStartMode(INST_FLEXCAN_0); // 把FlexCAN 0实例从配置模式（冻结模式）切换到正常工作模式
}


void FlexCAN0_CallBack(uint8 instance, Flexcan_Ip_EventType eventType,
                       uint32 buffIdx, const Flexcan_Ip_StateType *driverState) {
    (void)instance;
    (void)driverState;
    // 缓存报文数据，缓冲区如何设计？
    switch (eventType)
    {
    	case FLEXCAN_EVENT_RX_COMPLETE:
    	{
    		Flexcan_Ip_MsgBuffType rxFrame;
    		Flexcan_Ip_StatusType status;

    		status = FlexCAN_Ip_Receive(INST_FLEXCAN_0, buffIdx, &rxFrame, FALSE);
    		if (status == FLEXCAN_STATUS_SUCCESS) {
    			Can_RingBuffer_Push(&s_RxRingBuf, &rxFrame);
    		} else {
    			s_RxErrorCnt++;
    		}
    		break;
    	}
	}
    
}

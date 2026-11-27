/*
 * Can.c
 *
 *  Created on: 2026年11月18日
 *      Author: 罗灿
 */


#include "Can.h"

#define CAN_IDE_MASK (1U << 21) // IDE位于第21位
#define CAN_STD_ID_MASK 0x7FFU // 标准ID 11位掩码
#define CAN_STD_ID_SHIFT 28U // 标准ID偏移量为28位
#define CAN_EXT_ID_MASK 0x3FFFFU // 扩展ID掩码
#define CAN_DLC_SHIFT 16U
#define CAN_DLC_MASK 0xFU // DLC掩码

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

// 获取标准帧ID
static inline uint32_t Can_GetStdId(uint32_t msgId)
{
	return (msgId >> CAN_STD_ID_SHIFT) & CAN_STD_ID_MASK;
}

// 获取扩展帧ID
static inline uint32_t Can_GetExtId(uint32_t msgId)
{
	return msgId & CAN_EXT_ID_MASK;
}

// 判断是否为扩展帧
static inline bool Can_IsExtendedFrame(uint32_t cs)
{
	// IDE == 1：扩展帧；IDE == 0：普通帧
	return (cs & CAN_IDE_MASK) != 0;
}

static uint32_t Can_GetRealCanId(uint32_t cs, uint32_t msgId)
{
	if (Can_IsExtendedFrame(cs)) {
		return Can_GetExtId(msgId);
	} else {
		return Can_GetStdId(msgId);
	}
}

void CAN_MainFunction_Read(void) {

	Flexcan_Ip_MsgBuffType rxFrame;
	PduInfoType pduInfo;

	// 当环形缓冲区非空的时候
	while (Can_RingBuffer_Pop(&s_RxRingBuf, &rxFrame) == E_OK) {
		pduInfo.CanId = Can_GetRealCanId(rxFrame.cs, rxFrame.msgId);
		pduInfo.DataPtr = rxFrame.data;
		pduInfo.Dlc = (rxFrame.cs >> CAN_DLC_SHIFT) & CAN_DLC_MASK;
		CanIf_RxIndication(0, &pduInfo);
	}
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
    			Std_ReturnType status = Can_RingBuffer_Push(&s_RxRingBuf, &rxFrame);
    			if (status != E_OK) {
    				s_RxErrorCnt++;
    			}
    		} else {
    			s_RxErrorCnt++;
    		}
    		break;
    	}
	}
    
}

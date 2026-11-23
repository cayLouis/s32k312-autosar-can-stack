#include "Can_RingBuffer.h"



// 初始化
void Can_RingBuffer_Init(Can_RingBuffer_t *ringBuffer) {
    ringBuffer->head = 0U;
    ringBuffer->tail = 0U;
    ringBuffer->overflowcnt = 0U;
    memset(ringBuffer->buffer, 0, sizeof(ringBuffer->buffer));
}

bool Can_RingBuffer_IsFull(const Can_RingBuffer_t *ringBuffer) {
    return ((ringBuffer->head + 1U) % CAN_RINGBUFFER_SIZE) == ringBuffer->tail;
}

bool Can_RingBuffer_IsEmpty(const Can_RingBuffer_t *ringBuffer) {
    return ringBuffer->head == ringBuffer->tail;
}

//写入
Std_ReturnType Can_RingBuffer_Push(Can_RingBuffer_t* rb, const Flexcan_Ip_MsgBuffType* frame) {
	if (Can_RinfBuffer_IsFull(rb)) {
		rb->overflowcnt++; // 记录丢帧
		return E_NOT_OK;
	}
	/* 拷贝数据到环形缓冲区 */
	rb->buffer[rb->head] = *frame;
	/* 偏移指针 */
	rb->head = (rb->head + 1U) % CAN_RINGBUFFER_SIZE;

	return E_OK;
}

// 读取
Std_ReturnType Can_RingBuffer_Pop(Can_RingBuffer_t* rb, const Flexcan_Ip_MsgBuffType* frame){
	if (Can_RingBuffer_IsEmpty(rb)) {
		return E_NOT_OK;
	}

	*frame = rb->buffer[rb->tail];
	rb->tail = (rb->tail + 1U) % CAN_RINGBUFFER_SIZE;
	return E_OK;
}

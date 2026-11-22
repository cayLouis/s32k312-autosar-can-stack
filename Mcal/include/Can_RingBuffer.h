#ifndef CAN_RINGBUFFER_H
#define CAN_RINGBUFFER_H
#include "Flexcan_Ip_Types.h"

#define CAN_RINGBUFFER_SIZE 64U

typedef struct {
    Flexcan_Ip_MsgBuffType buffer[CAN_RINGBUFFER_SIZE];
    uint8_t head; // 写指针
    uint8_t tail; // 读指针
    uint32_t overflowcnt; // 用于溢出丢帧计数
} Can_RingBuffer_t;

void Can_RingBuffer_Init(Can_RingBuffer_t *ringBuffer);
bool Can_RingBuffer_IsFull(const Can_RingBuffer_t *ringBuffer);
bool Can_RingBuffer_IsEmpty(const Can_RingBuffer_t *ringBuffer);


#endif /* CAN_RINGBUFFER_H */
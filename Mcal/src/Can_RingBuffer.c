#include "Can_RingBuffer.h"



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
/*********************************************************************************************************
 *  ------------------------------------------------------------------------------------------------------
 *  file description
 *  ------------------------------------------------------------------------------------------------------
 *         \file  queue.h
 *        \brief  This is a C language queue
 *       \author  Lamdonn
 *      \version  1.0.0
 ********************************************************************************************************/
/*********************************************************************************************************
  MIT License

  Copyright (C) 2023 Lamdonn.

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
 ********************************************************************************************************/
#ifndef __queue_H
#define __queue_H

/* queue type define */
typedef struct QUEUE
{
    void* base;                     /* base address of data */
    int dsize;                      /* size of queue data */
    int capacity;                   /* capacity of queue */
    int size;                       /* size of queue */
    int head;                       /* index of queue head */
    int tail;                       /* index of queue tail */
} *queue;

/**
 *  \brief define queue.
 *  \param[in] type: the data type of the queue
 *  \param[in] capacity: the capacity of queue
 *  \return queue
 */
#define queue(type, capacity)       (&(struct QUEUE){(type[capacity]){0},sizeof(type),capacity,0,0,0})

/**
 *  \brief queue define.
 *  \param[in] name: queue name
 *  \param[in] array: array name
 *  \return none
 */
#define queue_define(name, array) \
    struct QUEUE struct_QUEUE_##name = {array,sizeof(array[0]),sizeof(array)/sizeof(array[0]),0,0,0}; \
    queue name = &struct_QUEUE_##name; \

/**
 *  \brief push data into the queue from the front.
 *  \param[in] queue: queue
 *  \param[in] *data: the address of data, if it is 0, no value will be assigned
 *  \return 1 success or 0 fail
 */
int queue_push_front(queue queue, void* data);

/**
 *  \brief push data into the queue from the back.
 *  \param[in] queue: queue
 *  \param[in] *data: the address of data, if it is 0, no value will be assigned
 *  \return 1 success or 0 fail
 */
int queue_push_back(queue queue, void* data);

/**
 *  \brief pop data from the front of queue.
 *  \param[in] queue: queue
 *  \param[in] *data: the address of data, if it is 0, no value will be assigned
 *  \return 1 success or 0 fail
 */
int queue_pop_front(queue queue, void* data);

/**
 *  \brief pop data from the back of queue.
 *  \param[in] queue: queue
 *  \param[in] *data: the address of data, if it is 0, no value will be assigned
 *  \return 1 success or 0 fail
 */
int queue_pop_back(queue queue, void* data);

/**
 *  \brief clear queue.
 *  \param[in] queue: queue
 *  \return none
 */
void queue_clear(queue queue);

/**
 *  \brief get data address of queue.
 *  \param[in] queue: queue
 *  \param[in] index: index
 *  \return address of queue data or 0 fail
 */
void* queue_data(queue queue, int index);

/** 
 *  \brief macro definition method for get front item of queue
 *  \param[in] queue: queue
 *  \param[in] type: tpye of item
 *  \param[in] i: index
 *  \return reference to the specified item
 */
#define queue_at(queue, type, i)    (*(type *)queue_data((queue),(i)))

/**
 *  \brief check if empty.
 *  \param[in] queue: queue
 *  \return 0 not empty or others empty
 */
#define queue_empty(queue)          ((queue)->size == 0)

/**
 *  \brief check if full.
 *  \param[in] queue: queue
 *  \return 0 not full or others full
 */
#define queue_full(queue)           ((queue)->size == (queue)->capacity)

/** 
 *  \brief convert literals to addresses
 *  \param[in] type: type, such as int/char/float etc.
 *  \param[in] value: literal value
 *  \return address of literal
 */
#define literal(type, value)        ((type[1]){value})

#endif

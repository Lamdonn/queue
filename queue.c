/*********************************************************************************************************
 *  ------------------------------------------------------------------------------------------------------
 *  file description
 *  ------------------------------------------------------------------------------------------------------
 *         \file  queue.c
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
#include "queue.h"

#define at(i)                       (((char *)(queue->base))+(i)*(queue->dsize)) /* address of void array */

static void* queue_memcpy(void* dest, const void* src, int n)
{
    char* dst = dest;
    const char* s = src;
    while (n--) *dst++ = *s++;
    return dest;
}

int queue_push_front(queue queue, void* data)
{
    if (!queue) return 0;
    if (queue->size == queue->capacity) return 0;
    queue->head = (queue->head + queue->capacity - 1) % queue->capacity;
    if (data) queue_memcpy(at(queue->head), data, queue->dsize);
    queue->size++;
    return 1;
}

int queue_push_back(queue queue, void* data)
{
    if (!queue) return 0;
    if (queue->size == queue->capacity) return 0;
    if (data) queue_memcpy(at(queue->tail), data, queue->dsize);
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->size++;
    return 1;
}

int queue_pop_front(queue queue, void* data)
{
    if (!queue) return 0;
    if (queue->size == 0) return 0;
    if (data) queue_memcpy(data, at(queue->head), queue->dsize);
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;
    return 1;
}

int queue_pop_back(queue queue, void* data)
{
    if (!queue) return 0;
    if (queue->size == 0) return 0;
    queue->tail = (queue->tail + queue->capacity - 1) % queue->capacity;
    if (data) queue_memcpy(data, at(queue->tail), queue->dsize);
    queue->size--;
    return 1;
}

void queue_clear(queue queue)
{
    if (!queue) return;
    queue->tail = 0;
    queue->head = 0;
    queue->size = 0;
}

void* queue_data(queue queue, int index)
{
    if (!queue) return 0;
    if (index < 0 || index >= queue->size) return 0;
    return (void*)at((queue->head + index) % (queue->capacity));
}

# queue

[中文版](README_zh.md)

#### Description  

This is a general-purpose queue in C language, which is simple, compact, general-purpose, reliable and efficient.  
It supports any data type and is very simple to use. This queue is very reliable in standard usage.  
This queue has two entrances and exits at the front and back, and data can be pushed and popped at both ends, and the queue form of `FIFO` (first in first out) and the stack form of `FILO` (first in last out) can be realized.  

#### Software Architecture  

It does not depend on any third-party library, not even on the C language standard library, and has an independent single-file structure.  

#### Installation

Just download queue.c and queue.h directly to participate in the compilation.  

#### Instructions

* Define queue

```c
#define queue(type, capacity)
```
The queue does not involve the allocation of memory space, so it does not need to release space when it is used at the end.  
When defining, it is as simple as `int a = 5;`.  

| Parameters | Description |
|-----|------|
| type | data type, such as int, char, float, struct, etc. |
| capacity | Queue capacity, that is, how many queue data the queue can hold at most |

| return value | description |
|-----|------|
| queue | handle to the queue |

Example:
```c
queue c = queue(char, 1024); // Define a queue whose type is char and has a capacity of 1024
queue i = queue(int, 10); // Define a queue whose type is int and whose capacity is 10
queue s = queue(struct STUDENT, 10); // Define a queue whose type is a structure with a capacity of 10
```

* Push

```c
int queue_push_front(queue queue, void* data);
int queue_push_back(queue queue, void* data);
```
The use of these two methods is consistent, pushing data from the front and the end respectively.

| Parameters | Description |
|-----|------|
| queue | handle to the queue |
| data | The address of the queued data (the data type must be consistent with the type when it was defined), you can pass `0` (NULL) to push an empty data (the original address is whatever is saved) |

| return value | description |
|-----|------|
| 1 | Operation succeeded |
| 0 | Operation failed |

Example:
```c
queue q = queue(int, 6); // Define a queue whose type is int and whose capacity is 6
int i = 10;
queue_push_back(q, &i); // According to the address of i, push the data of i from the end
queue_push_back(q, literal(int, 3)); // push data 3 from the end
queue_push_front(q, literal(int, 4)); // push data 4 from the head
```
The `literal(type, value)` macro here is for the convenience of pushing literal data, which is similar to obtaining the address of the literal `3`, and passing this address to the `push` method.

* Pop

```c
int queue_pop_front(queue queue, void* data);
int queue_pop_back(queue queue, void* data);
```
These two methods are used in the same way, popping data from the front and back respectively.

| Parameters | Description |
|-----|------|
| queue | handle to the queue |
| data | The address to receive the dequeued data (the data type needs to be consistent with the type when defined), you can pass `0` (NULL) to not receive the dequeued data |

| return value | description |
|-----|------|
| 1 | Operation succeeded |
| 0 | Operation failed |

Example:
```c
queue q = queue(int, 6); // Define a queue whose type is int and whose capacity is 6
int i = 10;

queue_push_back(q, &i);
queue_push_back(q, literal(int, 3));
queue_push_front(q, literal(int, 4));

queue_pop_front(q, &i); // pop data from the front, save in i
queue_pop_front(q, 0); // Pop data from the front, do not save pop data
queue_pop_back(q, 0); // pop data from the end, do not save the pop data
```

* Clear

```c
void queue_clear(queue queue);
```
This function clears all the data in the queue and restores it to the initialized state.
In fact, it is to adjust the index pointed to by the head and tail without actually deleting the data.

| Parameters | Description |
|-----|------|
| queue | handle to the queue |

| return value | description |
|-----|------|
| void | |

Example:
```c
queue q = queue(int, 10);
int data = 100;
queue_push(q, &data);
queue_clear(q); // Clear the queue data
```

* Obtain  

```c
void* queue_data(queue queue, int index);
```
This function obtains the address of the element in the queue according to the index.

| Parameters | Description |
|-----|------|
| queue | handle to the queue |
| index | Queue index (starting from index 0, from head to tail) |

| return value | description |
|-----|------|
| !0 | address of queue entry |
| 0 | Fetching failed |

Apply this function to form `at` macro definition method:
```c
#define queue_at(queue, type, i)
```
The `at` method uses a reference similar to C++, and actually points to this address for operation.

| Parameters | Description |
|-----|------|
| queue | handle to the queue |
| type | The data type of the queue item, consistent with the defined queue |
| i | Queue index (starting from index 0, from head to tail) |

| return value | description |
|-----|------|
| A reference to a queue item | Before using it, the queue must be valid, the type is valid, and the index i is valid |

Example:
```c
queue q = queue(int, 10);
int data = 100;
void *p;

queue_push(q, &data);
queue_push(q, &data);

p = queue_data(q, 0); // Get the address of the queue item
if (p) printf("%d\r\n", *(int *)p); // determine whether the address is valid

queue_at(q, int, 1) = 100; // modify the element with index 1 to 100
printf("q[0] = %d\n", queue_at(q, int, 0)); // print the element with index 0
```

* empty and full

```c
#define queue_empty(queue)
#define queue_full(queue)
```
These two methods are to judge whether the queue is empty and whether it is full, respectively, and are consistent in usage.
In fact, it is to judge the size of the queue. If it is equal to 0, it is empty, and if it is equal to the capacity, it is full.

| Parameters | Description |
|-----|------|
| queue | handle to the queue |

| return value | description |
|-----|------|
| 0 | Inconsistent |
| !0 | Consistent |

* Initialization definition

```c
#define queue_define(name, array)
```
This method defines a new queue based on a pre-defined array.
**Some compilers use the old version of C language, which may not support the usage of queue(type, capacity) (supported by C99 or newer version), and queue_define is only used at this time**
In general, it is not recommended to use this method to define a queue, and the `queue(type, capacity)` method is preferred to directly define the queue.


| Parameters | Description |
|-----|------|
| name | the name of the queue |
| array | the name of the buffer array |

Example:
```c
int buffer[12];
queue_define(q, buffer);
```

* Queue structure member

```c
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
```
In the `queue` structure members, **please do not directly modify any members**.  
You can read the `size` member, which is the queue size (number of queue items).  
You can read the `dsize` member, which is the size of the queue data item, such as `sizeof(int)`.  
You can read the `capacity` member, which is the capacity of the queue, corresponding to `capacity` in the definition method of `queue(type, capacity)`.  

* example  

```c
int main(int argc, char *argv[])
{
     queue q = queue(int, 6); // define a queue with an int capacity of 6
     int i = 0;

     // According to the capacity, push from the back to fill the entire queue
     for (i = 0; i < q->capacity; i++)
     {
         queue_push_back(q, literal(int, 100 + i)); // Pass in parameters through literals
     }

     // traverse the queue
     for (i = 0; i < q->size; i++)
     {
         printf("q[%d] = %d\r\n", i, queue_at(q, int, i));
     }

     queue_pop_front(q, 0); // pop from the front
     queue_pop_back(q, 0); // pop from the end
     queue_push_front(q, literal(int, 1024)); // push 1024 at the front
     printf("------------- modify -------------\r\n");

     // traverse the queue
     for (i = 0; i < q->size; i++)
     {
         printf("q[%d] = %d\r\n", i, queue_at(q, int, i));
     }
    
     return 0;
}
```
result:   
```
q[0] = 100
q[1] = 101
q[2] = 102
q[3] = 103
q[4] = 104
q[5] = 105
------------- modify -------------
q[0] = 1024
q[1] = 101
q[2] = 102
q[3] = 103
q[4] = 104
```

#### Contact information 

Lamdonn@163.com  

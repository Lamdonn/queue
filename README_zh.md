# queue

[English version](README.md)

#### 介绍 

这是一个C语言通用队列，简单、小巧、通用、可靠、高效。  
支持任意数据类型，使用也非常的简单，在规范使用情况下这个队列非常可靠。  
这个队列开放了前部和尾部两个出入口，在两端都可以推入数据和弹出数据，可以实现`FIFO`（先进先出）的队列形式和`FILO`（先进后出）的栈形式。  

#### 软件架构 

不依赖于任何第三方库，甚至不依赖于C语言标准库，独立的单文件结构。  

#### 安装教程 

直接下载 queue.c 和 queue.h 参与编译即可。  

#### 使用说明 

* 定义队列 

```c
#define queue(type, capacity)
```
该队列不涉及内存空间的分配，所以在结束使用不用释放空间。  
在定义时候就类似`int a = 5;`简单的定义即可。  

| 参数 | 描述 | 
|-----|------|
| type | 数据类型，比如int、char、float、struct等等 |
| capacity | 队列容量，也就是队列最大能容纳多少个队列数据 |

| 返回值 | 描述 | 
|-----|------|
| queue | 队列的句柄 |

举例： 
```c
queue c = queue(char, 1024); // 定义类型为char容量为1024的队列
queue i = queue(int, 10); // 定义类型为int容量为10的队列
queue s = queue(struct STUDENT, 10); // 定义类型为结构体容量为10的队列
```

* 入队  

```c
int queue_push_front(queue queue, void* data);
int queue_push_back(queue queue, void* data);
```
这两个方法使用是一致的，分别从前部和尾部推入数据。  

| 参数 | 描述 | 
|-----|------|
| queue | 队列的句柄 |
| data | 入队数据的地址（数据类型需和定义时候的类型一致），可以传入`0`（NULL）则是推入一个空数据（原来地址保存是什么就是什么） |

| 返回值 | 描述 | 
|-----|------|
| 1 | 操作成功 |
| 0 | 操作失败 |

举例： 
```c
queue q = queue(int, 6); // 定义类型为int容量为6的队列
int i = 10;
queue_push_back(q, &i); // 根据 i 的地址，从尾部推入 i 的数据
queue_push_back(q, literal(int, 3)); // 从尾部推入数据 3
queue_push_front(q, literal(int, 4)); // 从头部推入数据 4
```
在这里面的`literal(type, value)`宏，是为了方便推入字面量数据的，也就类似获取到字面量`3`的地址，把这个地址传给`push`方法。  

* 出队  

```c
int queue_pop_front(queue queue, void* data);
int queue_pop_back(queue queue, void* data);
```
这两个方法使用是一致的，分别从前部和尾部弹出数据。 

| 参数 | 描述 | 
|-----|------|
| queue | 队列的句柄 |
| data | 接收出队数据的地址（数据类型需和定义时候的类型一致），可以传入`0`（NULL）则是不接收出队的数据 |

| 返回值 | 描述 | 
|-----|------|
| 1 | 操作成功 |
| 0 | 操作失败 |

举例： 
```c
queue q = queue(int, 6); // 定义类型为int容量为6的队列
int i = 10;

queue_push_back(q, &i);
queue_push_back(q, literal(int, 3));
queue_push_front(q, literal(int, 4));

queue_pop_front(q, &i); // 从前部弹出数据，保存在 i 中
queue_pop_front(q, 0); // 从前部弹出数据，不保存弹出数据
queue_pop_back(q, 0); // 从尾部弹出数据，不保存弹出数据
```

* 清空  

```c
void queue_clear(queue queue);
```
该函数清空队列所有的数据，恢复到初始化的状态。  
实际就是调整头部和尾部指向的索引，不实际删除数据。  

| 参数 | 描述 | 
|-----|------|
| queue | 队列的句柄 |

| 返回值 | 描述 | 
|-----|------|
| void |  |

举例： 
```c
queue q = queue(int, 10);
int data = 100;
queue_push(q, &data);
queue_clear(q); // 清空队列数据
```

* 获取  

```c
void* queue_data(queue queue, int index);
```
该函数是根据索引，获取队列中元素的地址。  

| 参数 | 描述 | 
|-----|------|
| queue | 队列的句柄 |
| index | 队列索引（从索引0开始，由对头向队尾） |

| 返回值 | 描述 | 
|-----|------|
| !0 | 队列项的地址 |
| 0 | 获取失败 |

套用该函数形成`at`宏定义方法： 
```c
#define queue_at(queue, type, i)
```
`at`方法使用上类似于C++的引用，实际就是指向这个地址进行操作。  

| 参数 | 描述 | 
|-----|------|
| queue | 队列的句柄 |
| type | 队列项的数据类型，与定义队列保持一致 |
| i | 队列索引（从索引0开始，由对头向队尾） |

| 返回值 | 描述 | 
|-----|------|
| 队列项的引用 | 在使用前必须先确保队列是有效的、类型是有效的、索引i是有效的 |

举例： 
```c
queue q = queue(int, 10);
int data = 100;
void *p;

queue_push(q, &data);
queue_push(q, &data);

p = queue_data(q, 0); // 获取队列项地址
if (p) printf("%d\r\n", *(int *)p); // 判断地址是否有效

queue_at(q, int, 1) = 100; // 修改索引为 1 的元素为 100
printf("q[0] = %d\n", queue_at(q, int, 0)); // 打印索引为 0 的元素
```

* 空和满  

```c
#define queue_empty(queue)
#define queue_full(queue)
```
这两个方法就是分别判断队列是否为空和是否为满，用法上一致。  
实际就是判断队列大小，等于0是空，等于容量是满。  

| 参数 | 描述 | 
|-----|------|
| queue | 队列的句柄 |

| 返回值 | 描述 | 
|-----|------|
| 0 | 不一致 |
| !0 | 一致 |

* 初始化定义  

```c
#define queue_define(name, array)
```
该方法根据事先定义好的数组来定义新的队列。  
**有些编译器使用旧版本的C语言，可能不支持queue(type, capacity)的用法（C99或者更新的的版本支持），此时才用queue_define**
一般情况下，不建议使用此方法来定义一个队列，优先使用`queue(type, capacity)`方法直接定义队列。  


| 参数 | 描述 | 
|-----|------|
| name | 队列的名字 |
| array | 缓冲数组的名字 |

举例： 
```c
int buffer[12];
queue_define(q, buffer);
```

* 队列结构体成员  

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
在`queue`结构体成员中，**请不要直接修改其中的任何成员**。  
可以读取`size`成员，也就是队列大小（队列项的个数）。 
可以读取`dsize`成员，也就是队列数据项的大小，比如为`sizeof(int)`。  
可以读取`capacity`成员，也就是队列的容量，对应`queue(type, capacity)`定义方法中的`capacity`。  

* 例子  

```c
int main(int argc, char *argv[])
{
    queue q = queue(int, 6); // 定义int型容量为6的队列
    int i = 0;

    // 根据容量，从尾部推入填满整个队列
    for (i = 0; i < q->capacity; i++)
    {
        queue_push_back(q, literal(int, 100 + i)); // 通过字面量传入参数
    }

    // 遍历队列
    for (i = 0; i < q->size; i++)
    {
        printf("q[%d] = %d\r\n", i, queue_at(q, int, i));
    }

    queue_pop_front(q, 0); // 从前部弹出
    queue_pop_back(q, 0); // 从尾部弹出
    queue_push_front(q, literal(int, 1024)); // 在前部推入 1024
    printf("------------- modify -------------\r\n");

    // 遍历队列
    for (i = 0; i < q->size; i++)
    {
        printf("q[%d] = %d\r\n", i, queue_at(q, int, i));
    }
    
    return 0;
}
```
结果： 
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

#### 联系方式 

Lamdonn@163.com

#pragma once
#ifndef __CUSTOM_PIPE_H__
#define __CUSTOM_PIPE_H__
#include"stdlib.h"
typedef  unsigned short u16;

/*---------------------u16数组的功能性函数--开始---------------------------------------------------*/
int PIPE_max(const void *a, const void *b);/*比较函数，供qsort内建函数使用*/
int PIPE_min(const void *a, const void *b);/*比较函数，供qsort内建函数使用*/
void PIPE_InitArray(u16 value, u16 *array, int numOfarra);/*数组初始化*/
u16 PIPE_leftmove(u16 value, u16 *array, int numOfarray);/*移动数组，弹出最左边的值，再将value添加到最右边*/
int PIPE_sum(u16 *array, int numOfarray);/*对数组求和*/
int PIPE_CopyArray(u16 *src_array, int numOf_srcarray, u16 *des_array, int numOf_desarray);/*复制数组*/
u16 PIPE_FindMax(u16 *array, int start, int end);/*找到数组中最大值*/

 /*---------------------u16数组的功能性函数--结束---------------------------------------------------*/


/*---------------------结构体定义----开始---------------------------------------------------*/

 //三个数据存储的单元及尺寸：capacityUnit（capacity），kernelUnit（kernel_size），kernelUnit_shadow（kernel_size）
//一个flag_free标志位，
//两个u16数据：input,output
 //管道的功能函数：run
struct PIPE;
typedef struct PIPE  *ptr_PIPE;

//大的管道，装子管道PIPE，包含了释放子管道的空
struct BigPipe;

typedef struct BigPipe  * ptr_BigPipe;

/*---------------------结构体定义-----结束---------------------------------------------------*/

/*---------------------结构体相关函数----开始---------------------------------------------------*/

//PIPE的：
#ifdef __cplusplus
extern "C" {
#endif

void initiator_PIPE(ptr_PIPE fpip, int kernel_size, int capacity_size, u16(*func)(ptr_PIPE  self, u16 value));/* 管道初始化函数：kernel_size一定得大于等于3*/
void close_PIPE(ptr_PIPE fpip);/*释放申请的内存*/

//BigPipe的：
void BigPipe_add(ptr_BigPipe self, ptr_PIPE fpip1);/*添加一个子管道PIPE*/
void BigPipe_input(ptr_BigPipe self, u16 value);	 /*往管道中输入数据*/
u16  BigPipe_output(ptr_BigPipe  self);			 /*获取管道输出数据*/


void initiator_BigPipe(ptr_BigPipe self, int maxlen);/*初始化大管道结构体*/
void close_BigPipe(ptr_BigPipe self);											  /*关闭大管道*/

  /*---------------------结构体相关函数----结束---------------------------------------------------*/

  /*---------------------功能函数----开始---------------------------------------------------*/

u16 func_Medif(ptr_PIPE  pipe, u16 value);/*中值滤波函数*/
u16 func_FindPeaks(ptr_PIPE  pipe, u16 value);/*查找峰值的函数*/
  /*---------------------功能函数----结束---------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif

struct PIPE {
	int capacity;
	int kernel_size;
	int current_index;
	int flag_free;
	u16 * capacityUnit;
	u16 *kernelUnit;
	u16 *kernelUnit_shadow;
	u16 datain, dataout;//管道输入与输出
	u16(*run)(ptr_PIPE self, u16 value);//功能性函数比如滤波，求峰值

};
struct BigPipe {
	int maxlen;
	int current_index;
	int flag_free;
	u16 datain, datamed, dataout;//管道输入与输出
	void(*add)(ptr_BigPipe self, ptr_PIPE fpip1);//添加一个子管道PIPE
	void(*input)(ptr_BigPipe self, u16 value);//管道中输入值
	u16(*output)(ptr_BigPipe self);//从管道中取出值，内部会自己处理流经子管道的数据
	ptr_PIPE *pipes;
};
#include <iostream>
//#include"stdlib.h"
#include "customPIPE.h"
using namespace std;

//typedef  unsigned short u16;
//
//
///*比较函数，供qsort内建函数使用*/
//int PIPE_max(const void *a, const void *b)
//{
//	return (int)(*(u16 *)a - *(u16*)b);
//}
//
//int PIPE_min(const void *a, const void *b)
//{
//	return (int)(*(u16 *)b - *(u16*)a);
//}
//
//
//
///*数组初始化*/
//void PIPE_InitArray(u16 value, u16 *array, int numOfarra)
//{
//	int i = 0;
//	for (i; i < numOfarra; i++)
//	{
//		array[i] = value;
//	}
//}
//
//
///*移动数组，弹出最左边的值，再将value添加到最右边*/
//u16 PIPE_leftmove(u16 value, u16 *array, int numOfarray)
//{
//	int i = 0;
//	u16 temp;
//	temp = array[0];
//	for (i; i < numOfarray -1; i++)
//	{
//		array[i] = array[i + 1];
//	}
//	array[numOfarray - 1] = value;
//	return temp;
//}
//
//
//
///*对数组求和*/
//int PIPE_sum(u16 *array, int numOfarray)
//{
//	int i = 0, sum = 0;
//
//	for (i; i < numOfarray; i++)
//	{
//		sum += array[i];
//	}
//	return sum;
//}
//
///*复制数组*/
//int PIPE_CopyArray(u16 *src_array, int numOf_srcarray, u16 *des_array, int numOf_desarray)
//{
//	int i = 0;
//	if (numOf_desarray < numOf_desarray)
//	{
//		return 0;
//	}
//	else
//	{
//		for (i; i < numOf_srcarray; i++)
//		{
//			des_array[i] = src_array[i];
//		}
//		return 1;
//	}
//
//}
//
///*找到数组中最大值*/
//u16 PIPE_FindMax(u16 *array, int start,int end)
//{
//	int i = start;
//	u16 maxvalue= array[0];
//	for (i; i < end; i++)
//	{
//		maxvalue = array[i]>maxvalue ? array[i] : maxvalue;
//	}
//	return maxvalue;
//}
///*----------------------------------------------*/
//
////三个数据存储的单元及尺寸：capacityUnit（capacity），kernelUnit（kernel_size），kernelUnit_shadow（kernel_size）
////一个flag_free标志位，
////两个u16数据：input,output
////管道的功能函数：run
//struct PIPE {
//	int capacity;
//	int kernel_size;
//	int current_index;
//	bool flag_free;
//	u16 * capacityUnit;
//	u16 *kernelUnit;
//	u16 *kernelUnit_shadow;
//	u16 datain,dataout;//管道输入与输出
//	u16(*run)(PIPE * self, u16 value);//功能性函数比如滤波，求峰值
//	
//};
//
//
///* 管道初始化函数：kernel_size一定得大于等于3*/
//void initiator_PIPE(PIPE *fpip, int kernel_size,int capacity_size, u16(*func)(PIPE * self, u16 value)) {
//	kernel_size = kernel_size >= 3 ? kernel_size : 3;
//	fpip->capacity = capacity_size;
//	fpip->kernel_size = kernel_size;
//	fpip->current_index = 0;
//	fpip->flag_free = false ;
//
//	fpip->capacityUnit = (u16 *)malloc(sizeof(u16)*capacity_size);
//	fpip->kernelUnit = (u16*)malloc(sizeof(u16)*kernel_size);
//	fpip->kernelUnit_shadow = (u16*)malloc(sizeof(u16)*kernel_size);
//	fpip->run = func;
//
//	PIPE_InitArray(0, fpip->capacityUnit, fpip->capacity);
//	PIPE_InitArray(0, fpip->kernelUnit, fpip->kernel_size);
//	PIPE_InitArray(0, fpip->kernelUnit_shadow, fpip->kernel_size);
//
//}
//
///*释放申请的内存*/
//void close_PIPE(PIPE *fpip)
//{
//	free(fpip->capacityUnit);
//	free(fpip->kernelUnit);
//	free(fpip->kernelUnit_shadow);
//	fpip->capacityUnit = NULL;
//	fpip->kernelUnit = NULL;
//	fpip->kernelUnit_shadow = NULL;
//	fpip->flag_free = true;
//	fpip->run = NULL;
//
//
//}
//
///*-------------------------------------*/
//
////大的管道，装子管道PIPE，包含了释放子管道的空间
//struct BigPipe {
//	int maxlen;
//	int current_index;
//	bool flag_free;
//	u16 datain, datamed,dataout;//管道输入与输出
//	void (*add)(BigPipe *self,PIPE *fpip1);//添加一个子管道PIPE
//	void (*input)(BigPipe *self,u16 value);//管道中输入值
//	u16 (*output)(BigPipe *self);//从管道中取出值，内部会自己处理流经子管道的数据
//	PIPE **pipes;
//};
//
//
///*添加一个子管道PIPE*/
//void BigPipe_add(BigPipe *self,PIPE *fpip1)
//{
//	if (self->current_index < self->maxlen)
//	{
//		self->pipes[self->current_index] = fpip1;
//		self->current_index += 1;
//	}
//}
//
///*往管道中输入数据*/
//void BigPipe_input(BigPipe* self, u16 value)
//{
//	self->datain = value;
//
//}
//
///*获取管道输出数据*/
//u16 BigPipe_output(BigPipe* self)
//{
//	int i = 0;
//	for (i; i < self->maxlen; i++)
//	{
//		self->datamed=self->pipes[i]->run(self->pipes[i], self->datain);
//		self->datain = self->datamed;
//	}
//	self->dataout = self->datamed;
//	return self->dataout;
//}
//
///*初始化大管道结构体*/
//void initiator_BigPipe(BigPipe *self, int maxlen)
//{
//	self->maxlen = maxlen;
//	self->current_index = 0;
//	self->flag_free = false;
//	self->datain = 0;
//	self->dataout = 0;
//	self->datamed = 0;
//	self->add = BigPipe_add;
//	self->input = BigPipe_input;
//	self->output = BigPipe_output;
//	self->pipes = (PIPE**)malloc(sizeof(PIPE*)*maxlen);
//}
//
///*关闭大管道*/
//void close_BigPipe(BigPipe *self)
//{
//	int i = 0;
//	for (i; i < self->maxlen; i++)
//	{
//		if (!(self->pipes[i]->flag_free))
//		{
//			close_PIPE(self->pipes[i]);
//		}
//	}
//
//	free(self->pipes);
//	self->pipes = NULL;
//	self->flag_free = true;
//
//}
///*----------------------------------*/
//
///*中值滤波函数*/
//u16 func_Medif(PIPE * pipe, u16 value)
//{
//	int result = 0;
//	pipe->datain = value;
//	PIPE_leftmove(value, pipe->kernelUnit, pipe->kernel_size);
//	PIPE_CopyArray(pipe->kernelUnit, pipe->kernel_size, pipe->kernelUnit_shadow, pipe->kernel_size);//数组拷贝
//	qsort(pipe->kernelUnit_shadow, pipe->kernel_size, sizeof(u16), PIPE_max);//排序
//	pipe->kernelUnit_shadow[0] = 0;//去掉最小值
//	pipe->kernelUnit_shadow[pipe->kernel_size-1] = 0;//去掉最大值
//	result = PIPE_sum(pipe->kernelUnit_shadow, pipe->kernel_size) / (pipe->kernel_size - 2);
//	pipe->dataout = (u16)result;
//	return (u16)result;
//}
//
///*查找峰值的函数*/
//u16 func_FindPeaks(PIPE *pipe, u16 value)
//{
//	int i = 0;
//	u16 out = 0x0000;
//	pipe->datain = value;
//	PIPE_leftmove(value, pipe->kernelUnit, pipe->kernel_size);
//	for (i; i < pipe->kernel_size-2; i++)
//	{
//		if ((pipe->kernelUnit[i] < pipe->kernelUnit[i + 1]) && (pipe->kernelUnit[i + 1] >= pipe->kernelUnit[i + 2]))//峰值判断
//		{
//			//printf("----A peak:%x\n", pipe->kernelUnit[i + 1]);//找到的峰值
//			pipe->capacityUnit[pipe->current_index] = pipe->kernelUnit[i + 1];//存入峰值
//			if (pipe->current_index <pipe->capacity-1)//存的峰值满了
//			{
//
//				pipe->current_index += 1;//峰值计数加1
//				
//			}
//			else
//			{
//				PIPE_leftmove(pipe->kernelUnit[i + 1], pipe->capacityUnit, pipe->capacity);
//			}
//		}
//	}
//	out = PIPE_FindMax(pipe->capacityUnit, 0, pipe->current_index + 1);
//	pipe->dataout = out;
//	return out;//返回最大的峰值
//}


int main()
{

	u16 a[] = { 0x0001, 0x0003, 0x0002, 0x0005,  0x00f6, 0x0007,0xffff, 0xffff, 0xffff, 0x0002, 0x0003, 0x0001, 0x000d ,
		0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002,0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002 ,
		0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002,0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002 ,
		0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002,0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002 ,
		0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002,0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002 ,
		0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002,0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002 ,
		0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002,0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002 ,
		0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002,0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002 ,
		0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x00bb, 0x0002,0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002 ,
		0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002,0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002 ,
		0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x00ba, 0x00bb, 0x00ba,0x0009, 0x0003, 0x0005, 0x0002 ,0x000a, 0x0003, 0x000b, 0x0002 };
	int lenths = sizeof(a) / sizeof(u16);
	int i = 0;

	/*第一种方式*/
	PIPE channelA_medifPipe;//为通道A建立一个滤波管道
	PIPE channelA_findpeakPipe;//再建立一个找峰值管道
	initiator_PIPE(&channelA_medifPipe, 3,0, func_Medif);//管道结构体初始化：管道自身的地址，kernelsize（滤波单元的大小）,管道处理函数（滤波函数）
	initiator_PIPE(&channelA_findpeakPipe, 3, 10, func_FindPeaks);//
	for (i; i < lenths; i++)
	{
		printf("final output:%x\n", channelA_findpeakPipe.run(&channelA_findpeakPipe, channelA_medifPipe.run(&channelA_medifPipe,a[i])));
		//printf("-----------filter:%x\n", channelA_medifPipe.dataout);//通过dataout查看流经当前管道的输出值
	}
	close_PIPE(&channelA_medifPipe);//销毁管道
	close_PIPE(&channelA_findpeakPipe);//销毁管道


	printf("-----------\n\n");

	/*第二种方式，将子管道加到大管道中*/
	//子管道创建
	
	PIPE channelB_medifPipe;
	PIPE channelB_findpeakPipe;
	initiator_PIPE(&channelB_medifPipe, 3, 0, func_Medif);//结构体初始化
	initiator_PIPE(&channelB_findpeakPipe, 3, 10, func_FindPeaks);
	//大管道创建
	BigPipe channelB_Pipe;
	initiator_BigPipe(&channelB_Pipe, 2);//结构体初始化
	channelB_Pipe.add(&channelB_Pipe, &channelB_medifPipe);//添加滤波管道
	channelB_Pipe.add(&channelB_Pipe, &channelB_findpeakPipe);//添加找峰值管道
	
	for (i=0; i < lenths; i++)
	{
		
		channelB_Pipe.input(&channelB_Pipe, a[i]);
		printf("---%x\n", channelB_Pipe.output(&channelB_Pipe));
	}
	
	close_BigPipe(&channelB_Pipe);//关闭管道

	system("pause");
}
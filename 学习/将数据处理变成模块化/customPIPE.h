#pragma once
#ifndef __CUSTOM_PIPE_H__
#define __CUSTOM_PIPE_H__
#include"stdlib.h"
typedef  unsigned short u16;

/*---------------------u16����Ĺ����Ժ���--��ʼ---------------------------------------------------*/
int PIPE_max(const void *a, const void *b);/*�ȽϺ�������qsort�ڽ�����ʹ��*/
int PIPE_min(const void *a, const void *b);/*�ȽϺ�������qsort�ڽ�����ʹ��*/
void PIPE_InitArray(u16 value, u16 *array, int numOfarra);/*�����ʼ��*/
u16 PIPE_leftmove(u16 value, u16 *array, int numOfarray);/*�ƶ����飬��������ߵ�ֵ���ٽ�value��ӵ����ұ�*/
int PIPE_sum(u16 *array, int numOfarray);/*���������*/
int PIPE_CopyArray(u16 *src_array, int numOf_srcarray, u16 *des_array, int numOf_desarray);/*��������*/
u16 PIPE_FindMax(u16 *array, int start, int end);/*�ҵ����������ֵ*/

 /*---------------------u16����Ĺ����Ժ���--����---------------------------------------------------*/


/*---------------------�ṹ�嶨��----��ʼ---------------------------------------------------*/

 //�������ݴ洢�ĵ�Ԫ���ߴ磺capacityUnit��capacity����kernelUnit��kernel_size����kernelUnit_shadow��kernel_size��
//һ��flag_free��־λ��
//����u16���ݣ�input,output
 //�ܵ��Ĺ��ܺ�����run
struct PIPE;
typedef struct PIPE  *ptr_PIPE;

//��Ĺܵ���װ�ӹܵ�PIPE���������ͷ��ӹܵ��Ŀ�
struct BigPipe;

typedef struct BigPipe  * ptr_BigPipe;

/*---------------------�ṹ�嶨��-----����---------------------------------------------------*/

/*---------------------�ṹ����غ���----��ʼ---------------------------------------------------*/

//PIPE�ģ�
#ifdef __cplusplus
extern "C" {
#endif

void initiator_PIPE(ptr_PIPE fpip, int kernel_size, int capacity_size, u16(*func)(ptr_PIPE  self, u16 value));/* �ܵ���ʼ��������kernel_sizeһ���ô��ڵ���3*/
void close_PIPE(ptr_PIPE fpip);/*�ͷ�������ڴ�*/

//BigPipe�ģ�
void BigPipe_add(ptr_BigPipe self, ptr_PIPE fpip1);/*���һ���ӹܵ�PIPE*/
void BigPipe_input(ptr_BigPipe self, u16 value);	 /*���ܵ�����������*/
u16  BigPipe_output(ptr_BigPipe  self);			 /*��ȡ�ܵ��������*/


void initiator_BigPipe(ptr_BigPipe self, int maxlen);/*��ʼ����ܵ��ṹ��*/
void close_BigPipe(ptr_BigPipe self);											  /*�رմ�ܵ�*/

  /*---------------------�ṹ����غ���----����---------------------------------------------------*/

  /*---------------------���ܺ���----��ʼ---------------------------------------------------*/

u16 func_Medif(ptr_PIPE  pipe, u16 value);/*��ֵ�˲�����*/
u16 func_FindPeaks(ptr_PIPE  pipe, u16 value);/*���ҷ�ֵ�ĺ���*/
  /*---------------------���ܺ���----����---------------------------------------------------*/

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
	u16 datain, dataout;//�ܵ����������
	u16(*run)(ptr_PIPE self, u16 value);//�����Ժ��������˲������ֵ

};
struct BigPipe {
	int maxlen;
	int current_index;
	int flag_free;
	u16 datain, datamed, dataout;//�ܵ����������
	void(*add)(ptr_BigPipe self, ptr_PIPE fpip1);//���һ���ӹܵ�PIPE
	void(*input)(ptr_BigPipe self, u16 value);//�ܵ�������ֵ
	u16(*output)(ptr_BigPipe self);//�ӹܵ���ȡ��ֵ���ڲ����Լ����������ӹܵ�������
	ptr_PIPE *pipes;
};
#include"customPIPE.h"



/*�ȽϺ�������qsort�ڽ�����ʹ��*/
int PIPE_max(const void *a, const void *b)
{
	return (int)(*(u16 *)a - *(u16*)b);
}

int PIPE_min(const void *a, const void *b)
{
	return (int)(*(u16 *)b - *(u16*)a);
}



/*�����ʼ��*/
void PIPE_InitArray(u16 value, u16 *array, int numOfarra)
{
	int i = 0;
	for (i; i < numOfarra; i++)
	{
		array[i] = value;
	}
}


/*�ƶ����飬��������ߵ�ֵ���ٽ�value��ӵ����ұ�*/
u16 PIPE_leftmove(u16 value, u16 *array, int numOfarray)
{
	int i = 0;
	u16 temp;
	temp = array[0];
	for (i; i < numOfarray - 1; i++)
	{
		array[i] = array[i + 1];
	}
	array[numOfarray - 1] = value;
	return temp;
}



/*���������*/
int PIPE_sum(u16 *array, int numOfarray)
{
	int i = 0, sum = 0;

	for (i; i < numOfarray; i++)
	{
		sum += array[i];
	}
	return sum;
}

/*��������*/
int PIPE_CopyArray(u16 *src_array, int numOf_srcarray, u16 *des_array, int numOf_desarray)
{
	int i = 0;
	if (numOf_desarray < numOf_desarray)
	{
		return 0;
	}
	else
	{
		for (i; i < numOf_srcarray; i++)
		{
			des_array[i] = src_array[i];
		}
		return 1;
	}

}

/*�ҵ����������ֵ*/
u16 PIPE_FindMax(u16 *array, int start, int end)
{
	int i = start;
	u16 maxvalue = array[0];
	for (i; i < end; i++)
	{
		maxvalue = array[i]>maxvalue ? array[i] : maxvalue;
	}
	return maxvalue;
}
/*----------------------------------------------*/



/* �ܵ���ʼ��������kernel_sizeһ���ô��ڵ���3*/
void initiator_PIPE(ptr_PIPE fpip, int kernel_size, int capacity_size, u16(*func)(ptr_PIPE self, u16 value)) {
	kernel_size = kernel_size >= 3 ? kernel_size : 3;
	fpip->capacity = capacity_size;
	fpip->kernel_size = kernel_size;
	fpip->current_index = 0;
	fpip->flag_free = 0;

	fpip->capacityUnit = (u16 *)malloc(sizeof(u16)*capacity_size);
	fpip->kernelUnit = (u16*)malloc(sizeof(u16)*kernel_size);
	fpip->kernelUnit_shadow = (u16*)malloc(sizeof(u16)*kernel_size);
	fpip->run = func;

	PIPE_InitArray(0, fpip->capacityUnit, fpip->capacity);
	PIPE_InitArray(0, fpip->kernelUnit, fpip->kernel_size);
	PIPE_InitArray(0, fpip->kernelUnit_shadow, fpip->kernel_size);

}

/*�ͷ�������ڴ�*/
void close_PIPE(ptr_PIPE fpip)
{
	free(fpip->capacityUnit);
	free(fpip->kernelUnit);
	free(fpip->kernelUnit_shadow);
	fpip->capacityUnit = NULL;
	fpip->kernelUnit = NULL;
	fpip->kernelUnit_shadow = NULL;
	fpip->flag_free = 1;
	fpip->run = NULL;


}



/*���һ���ӹܵ�PIPE*/
void BigPipe_add(ptr_BigPipe self, ptr_PIPE fpip1)
{
	if (self->current_index < self->maxlen)
	{
		self->pipes[self->current_index] = fpip1;
		self->current_index += 1;
	}
}

/*���ܵ�����������*/
void BigPipe_input(ptr_BigPipe self, u16 value)
{
	self->datain = value;

}

/*��ȡ�ܵ��������*/
u16 BigPipe_output(ptr_BigPipe self)
{
	int i = 0;
	for (i; i < self->maxlen; i++)
	{
		self->datamed = self->pipes[i]->run(self->pipes[i], self->datain);
		self->datain = self->datamed;
	}
	self->dataout = self->datamed;
	return self->dataout;
}

/*��ʼ����ܵ��ṹ��*/
void initiator_BigPipe(ptr_BigPipe self, int maxlen)
{
	self->maxlen = maxlen;
	self->current_index = 0;
	self->flag_free = 0;
	self->datain = 0;
	self->dataout = 0;
	self->datamed = 0;
	self->add = BigPipe_add;
	self->input = BigPipe_input;
	self->output = BigPipe_output;
	self->pipes = (ptr_PIPE*)malloc(sizeof(ptr_PIPE)*maxlen);
}

/*�رմ�ܵ�*/
void close_BigPipe(ptr_BigPipe self)
{
	int i = 0;
	for (i; i < self->maxlen; i++)
	{
		if ((self->pipes[i]->flag_free)==0)
		{
			close_PIPE(self->pipes[i]);
		}
	}

	free(self->pipes);
	self->pipes = NULL;
	self->flag_free = 1;

}
/*----------------------------------*/
/*��ֵ�˲�����*/
u16 func_Medif(ptr_PIPE pipe, u16 value)
{
	int result = 0;
	pipe->datain = value;
	PIPE_leftmove(value, pipe->kernelUnit, pipe->kernel_size);
	PIPE_CopyArray(pipe->kernelUnit, pipe->kernel_size, pipe->kernelUnit_shadow, pipe->kernel_size);//���鿽��
	qsort(pipe->kernelUnit_shadow, pipe->kernel_size, sizeof(u16), PIPE_max);//����
	pipe->kernelUnit_shadow[0] = 0;//ȥ����Сֵ
	pipe->kernelUnit_shadow[pipe->kernel_size - 1] = 0;//ȥ�����ֵ
	result = PIPE_sum(pipe->kernelUnit_shadow, pipe->kernel_size) / (pipe->kernel_size - 2);
	pipe->dataout = (u16)result;
	return (u16)result;
}

/*���ҷ�ֵ�ĺ���*/
u16 func_FindPeaks(ptr_PIPE pipe, u16 value)
{
	int i = 0;
	u16 out = 0x0000;
	pipe->datain = value;
	PIPE_leftmove(value, pipe->kernelUnit, pipe->kernel_size);
	for (i; i < pipe->kernel_size - 2; i++)
	{
		if ((pipe->kernelUnit[i] < pipe->kernelUnit[i + 1]) && (pipe->kernelUnit[i + 1] >= pipe->kernelUnit[i + 2]))//��ֵ�ж�
		{
			//printf("----A peak:%x\n", pipe->kernelUnit[i + 1]);//�ҵ��ķ�ֵ
			pipe->capacityUnit[pipe->current_index] = pipe->kernelUnit[i + 1];//�����ֵ
			if (pipe->current_index <pipe->capacity - 1)//��ķ�ֵ����
			{

				pipe->current_index += 1;//��ֵ������1

			}
			else
			{
				PIPE_leftmove(pipe->kernelUnit[i + 1], pipe->capacityUnit, pipe->capacity);
			}
		}
	}
	out = PIPE_FindMax(pipe->capacityUnit, 0, pipe->current_index + 1);
	pipe->dataout = out;
	return out;//�������ķ�ֵ
}
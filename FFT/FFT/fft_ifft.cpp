#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>  
#include "fft_ifft.h"


/*���ٸ���Ҷ�任
TDΪʱ��ֵ,FDΪƵ��ֵ,powerΪ2������*/
void FFT(COMPLEX * TD, COMPLEX * FD, int power)
{
	int count;
	int i, j, k, bfsize, p;
	double angle;
	COMPLEX *W, *X1, *X2, *X;

	/*���㸵��Ҷ�任����*/
	count = 1 << power;
	/*������������洢��*/
	W = (COMPLEX *)malloc(sizeof(COMPLEX)*count / 2);
	X1 = (COMPLEX *)malloc(sizeof(COMPLEX)*count);
	X2 = (COMPLEX *)malloc(sizeof(COMPLEX)*count);
	/*�����Ȩϵ��*/
	for (i = 0; i<count / 2; i++)
	{
		angle = -i* pi * 2 / count;
		W[i].re = cos(angle);
		W[i].im = sin(angle);
	}
	/*��ʱ���д��洢��*/
	memcpy(X1, TD, sizeof(COMPLEX)*count);
	/*��������*/
	for (k = 0; k<power; k++)
	{
		for (j = 0; j<1 << k; j++)
		{
			bfsize = 1 << (power - k);
			for (i = 0; i<bfsize / 2; i++)
			{
				p = j*bfsize;
				X2[i + p] = Add(X1[i + p], X1[i + p + bfsize / 2]);
				X2[i + p + bfsize / 2] = Mul(Sub(X1[i + p], X1[i + p + bfsize / 2]), W[i*(1 << k)]);
			}
		}
		X  = X1;
		X1 = X2;
		X2 = X ;
	}
	/*��������*/
	for (j = 0; j<count; j++)
	{
		p = 0;
		for (i = 0; i<power; i++)
		{
			if (j&(1 << i)) p += 1 << (power - i - 1);
		}
		FD[j] = X1[p];
	}
	/*�ͷŴ洢��*/
	free(W);
	free(X1);
	free(X2);
}

/*���ٸ���Ҷ���任,���ÿ��ٸ���Ҷ�任
FDΪƵ��ֵ,TDΪʱ��ֵ,powerΪ2������*/
void IFFT(COMPLEX *FD, COMPLEX *TD, int power)
{
	int i, count;
	COMPLEX *x;

	/*���㸵��Ҷ���任����*/
	count = 1 << power;
	/*������������洢��*/
	x = (COMPLEX *)malloc(sizeof(COMPLEX)*count);
	/*��Ƶ���д��洢��*/
	memcpy(x, FD, sizeof(COMPLEX)*count);
	/*��Ƶ���Ĺ���*/
	for (i = 0; i<count; i++)
	{
		x[i].im = -x[i].im;
	}
	/*���ÿ��ٸ���Ҷ�任*/
	FFT(x, TD, power);
	/*��ʱ���Ĺ���*/
	for (i = 0; i<count; i++)
	{
		TD[i].re /= count;
		TD[i].im = -TD[i].im / count;
	}
	/*�ͷŴ洢��*/
	free(x);
}



/*************************************************************************
*
* �������ƣ�
*   Fourier()
*
* ����:
*   COMPLEX* TD			- �����ʱ������
*	 long lWidth		- ͼ����
*	 long lHeight		- ͼ��߶�
*	 COMPLEX* FD		- �����Ƶ������
*
* ����ֵ:
*   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
*
* ˵��:
*   �ú������ж�ά���ٸ���Ҷ�任��
*
************************************************************************/

void FFT2(COMPLEX * TD, long lWidth, long lHeight, COMPLEX  * FD)
{
	COMPLEX *TempT, *TempF;
	// ѭ������
	long	i;
	long	j;

	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	long w = 1;
	long h = 1;
	int wp = 0;
	int hp = 0;

	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	while (w < lWidth){
		w *= 2;
		wp++;
	}

	while (h < lHeight){
		h *= 2;
		hp++;
	}
	// �����ڴ�
	TempT = (COMPLEX *)malloc(sizeof(COMPLEX)*h);
	TempF = (COMPLEX *)malloc(sizeof(COMPLEX)*h);

	// ��y������п��ٸ���Ҷ�任
	//rgb
	/*for (i = 0; i < w * 3; i++)
	{
	// ��ȡ����
	for (j = 0; j < h; j++)
	TempT[j] = TD[j * w * 3 + i];//rgb

	// һά���ٸ���Ҷ�任
	FFT(TempT, TempF, hp);

	// ����任���
	for (j = 0; j < h; j++)
	TD[j * w * 3 + i] = TempF[j];
	}
	*/
	//�Ҷ�
	for (i = 0; i < w; i++){
		// ��ȡ����
		for (j = 0; j < h; j++){
			TempT[j] = TD[j * w + i];
		}
		 // һά���ٸ���Ҷ�任
		FFT(TempT, TempF, hp);
		// ����任���
		for (j = 0; j < h; j++){
			TD[j * w + i] = TempF[j];
		}
	}
	// �ͷ��ڴ�
	free(TempT);
	free(TempF);

	// �����ڴ�
	TempT = (COMPLEX *)malloc(sizeof(COMPLEX)*w);
	TempF = (COMPLEX *)malloc(sizeof(COMPLEX)*w);
	// ��x������п��ٸ���Ҷ�任
	//rgb
	/*
	for (i = 0; i < h; i++)
	{
	for (k = 0; k < 3; k++)
	{
	// ��ȡ����
	for (j = 0; j < w; j++)
	TempT[j] = TD[i * w * 3 + j * 3 + k];

	// һά���ٸ���Ҷ�任
	FFT(TempT, TempF, wp);

	// ����任���
	for (j = 0; j < w; j++)
	FD[i * w * 3 + j * 3 + k] = TempF[j];
	}
	}
	*/
	//�Ҷ�
	for (i = 0; i < h; i++)
	{
		// ��ȡ����
		for (j = 0; j < w; j++){
			TempT[j] = TD[i * w + j];
		}
		// һά���ٸ���Ҷ�任
		FFT(TempT, TempF, wp);
		// ����任���
		for (j = 0; j < w; j++){
			FD[i * w + j] = TempF[j];
		}
	}
	// �ͷ��ڴ�
	free(TempT);
	free(TempF);
}

/*************************************************************************
*
* �������ƣ�
*   IFourier()
*
* ����:
*   LPBYTE TD			- ���صĿ�������
*   long lWidth		- ����ͼ��Ŀ��
*	 long lHeight		- ����ͼ��ĸ߶�
*	 COMPLEX* FD		- �����Ƶ������
*
* ����ֵ:
*   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
*
* ˵��:
*   �ú������ж�ά���ٸ���Ҷ��任��
*
************************************************************************/

void IFFT2(COMPLEX *TD, long lWidth, long lHeight, COMPLEX * FD)
{
	COMPLEX *TempT, *TempF;
	// ѭ������
	long	i;
	long	j;

	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	long w = 1;
	long h = 1;
	int wp = 0;
	int hp = 0;

	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	while (w < lWidth){
		w *= 2;
		wp++;
	}
	while (h < lHeight){
		h *= 2;
		hp++;
	}

	// ����ͼ��ÿ�е��ֽ���
	//long lLineBytes = WIDTHBYTES(lWidth * 24);

	// �����ڴ�

	TempT = (COMPLEX *)malloc(sizeof(COMPLEX)*w);
	TempF = (COMPLEX *)malloc(sizeof(COMPLEX)*w);

	// ��x������п��ٸ���Ҷ�任
	//rgb
	/*
	for (i = 0; i < h; i++)
	{
	for (k = 0; k < 3; k++)
	{
	// ��ȡ����
	for (j = 0; j < w; j++)
	TempF[j] = FD[i * w * 3 + j * 3 + k];

	// һά���ٸ���Ҷ�任
	IFFT(TempF, TempT, wp);

	// ����任���
	for (j = 0; j < w; j++)
	FD[i * w * 3 + j * 3 + k] = TempT[j];
	}
	}
	*/
	//�Ҷ�
	for (i = 0; i < h; i++){
		// ��ȡ����
		for (j = 0; j < w; j++)
			TempF[j] = FD[i * w + j];
		// һά���ٸ���Ҷ�任
		IFFT(TempF, TempT, wp);
		// ����任���
		for (j = 0; j < w; j++)
			FD[i * w + j] = TempT[j];
	}
	// �ͷ��ڴ�
	free(TempT);
	free(TempF);

	TempT = (COMPLEX *)malloc(sizeof(COMPLEX)*h);
	TempF = (COMPLEX *)malloc(sizeof(COMPLEX)*h);

	// ��y������п��ٸ���Ҷ�任
	//rgb
	/*
	for (i = 0; i < w * 3; i++)
	{
	// ��ȡ����
	for (j = 0; j < h; j++)
	TempF[j] = FD[j * w * 3 + i];

	// һά���ٸ���Ҷ�任
	IFFT(TempF, TempT, hp);

	// ����任���
	for (j = 0; j < h; j++)
	TD[j * w * 3 + i] = TempT[j];
	}
	*/
	//�Ҷ�
	for (i = 0; i < w; i++){
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempF[j] = FD[j * w + i];
		// һά���ٸ���Ҷ�任
		IFFT(TempF, TempT, hp);
		// ����任���
		for (j = 0; j < h; j++)
			TD[j * w + i] = TempT[j];
	}
	// �ͷ��ڴ�
	free(TempT);
	free(TempF);

	/*for (i = 0; i < h; i++)
	{
	for (j = 0; j < w * 3; j++)
	{
	if (i < lHeight && j < lLineBytes)
	*(TD + i * lLineBytes + j) = FD[i * w * 3 + j].re;
	}
	}
	*/
}

#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>  
#include "fft_ifft.h"


/*快速傅里叶变换
TD为时域值,FD为频域值,power为2的幂数*/
void FFT(COMPLEX * TD, COMPLEX * FD, int power)
{
	int count;
	int i, j, k, bfsize, p;
	double angle;
	COMPLEX *W, *X1, *X2, *X;

	/*计算傅里叶变换点数*/
	count = 1 << power;
	/*分配运算所需存储器*/
	W = (COMPLEX *)malloc(sizeof(COMPLEX)*count / 2);
	X1 = (COMPLEX *)malloc(sizeof(COMPLEX)*count);
	X2 = (COMPLEX *)malloc(sizeof(COMPLEX)*count);
	/*计算加权系数*/
	for (i = 0; i<count / 2; i++)
	{
		angle = -i* pi * 2 / count;
		W[i].re = cos(angle);
		W[i].im = sin(angle);
	}
	/*将时域点写入存储器*/
	memcpy(X1, TD, sizeof(COMPLEX)*count);
	/*蝶形运算*/
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
	/*重新排序*/
	for (j = 0; j<count; j++)
	{
		p = 0;
		for (i = 0; i<power; i++)
		{
			if (j&(1 << i)) p += 1 << (power - i - 1);
		}
		FD[j] = X1[p];
	}
	/*释放存储器*/
	free(W);
	free(X1);
	free(X2);
}

/*快速傅里叶反变换,利用快速傅里叶变换
FD为频域值,TD为时域值,power为2的幂数*/
void IFFT(COMPLEX *FD, COMPLEX *TD, int power)
{
	int i, count;
	COMPLEX *x;

	/*计算傅里叶反变换点数*/
	count = 1 << power;
	/*分配运算所需存储器*/
	x = (COMPLEX *)malloc(sizeof(COMPLEX)*count);
	/*将频域点写入存储器*/
	memcpy(x, FD, sizeof(COMPLEX)*count);
	/*求频域点的共轭*/
	for (i = 0; i<count; i++)
	{
		x[i].im = -x[i].im;
	}
	/*调用快速傅里叶变换*/
	FFT(x, TD, power);
	/*求时域点的共轭*/
	for (i = 0; i<count; i++)
	{
		TD[i].re /= count;
		TD[i].im = -TD[i].im / count;
	}
	/*释放存储器*/
	free(x);
}



/*************************************************************************
*
* 函数名称：
*   Fourier()
*
* 参数:
*   COMPLEX* TD			- 输入的时域序列
*	 long lWidth		- 图象宽度
*	 long lHeight		- 图象高度
*	 COMPLEX* FD		- 输出的频域序列
*
* 返回值:
*   BOOL               - 成功返回TRUE，否则返回FALSE。
*
* 说明:
*   该函数进行二维快速付立叶变换。
*
************************************************************************/

void FFT2(COMPLEX * TD, long lWidth, long lHeight, COMPLEX  * FD)
{
	COMPLEX *TempT, *TempF;
	// 循环变量
	long	i;
	long	j;

	// 进行傅里叶变换的宽度和高度（2的整数次方）
	long w = 1;
	long h = 1;
	int wp = 0;
	int hp = 0;

	// 计算进行付立叶变换的宽度和高度（2的整数次方）
	while (w < lWidth){
		w *= 2;
		wp++;
	}

	while (h < lHeight){
		h *= 2;
		hp++;
	}
	// 分配内存
	TempT = (COMPLEX *)malloc(sizeof(COMPLEX)*h);
	TempF = (COMPLEX *)malloc(sizeof(COMPLEX)*h);

	// 对y方向进行快速付立叶变换
	//rgb
	/*for (i = 0; i < w * 3; i++)
	{
	// 抽取数据
	for (j = 0; j < h; j++)
	TempT[j] = TD[j * w * 3 + i];//rgb

	// 一维快速傅立叶变换
	FFT(TempT, TempF, hp);

	// 保存变换结果
	for (j = 0; j < h; j++)
	TD[j * w * 3 + i] = TempF[j];
	}
	*/
	//灰度
	for (i = 0; i < w; i++){
		// 抽取数据
		for (j = 0; j < h; j++){
			TempT[j] = TD[j * w + i];
		}
		 // 一维快速傅立叶变换
		FFT(TempT, TempF, hp);
		// 保存变换结果
		for (j = 0; j < h; j++){
			TD[j * w + i] = TempF[j];
		}
	}
	// 释放内存
	free(TempT);
	free(TempF);

	// 分配内存
	TempT = (COMPLEX *)malloc(sizeof(COMPLEX)*w);
	TempF = (COMPLEX *)malloc(sizeof(COMPLEX)*w);
	// 对x方向进行快速付立叶变换
	//rgb
	/*
	for (i = 0; i < h; i++)
	{
	for (k = 0; k < 3; k++)
	{
	// 抽取数据
	for (j = 0; j < w; j++)
	TempT[j] = TD[i * w * 3 + j * 3 + k];

	// 一维快速傅立叶变换
	FFT(TempT, TempF, wp);

	// 保存变换结果
	for (j = 0; j < w; j++)
	FD[i * w * 3 + j * 3 + k] = TempF[j];
	}
	}
	*/
	//灰度
	for (i = 0; i < h; i++)
	{
		// 抽取数据
		for (j = 0; j < w; j++){
			TempT[j] = TD[i * w + j];
		}
		// 一维快速傅立叶变换
		FFT(TempT, TempF, wp);
		// 保存变换结果
		for (j = 0; j < w; j++){
			FD[i * w + j] = TempF[j];
		}
	}
	// 释放内存
	free(TempT);
	free(TempF);
}

/*************************************************************************
*
* 函数名称：
*   IFourier()
*
* 参数:
*   LPBYTE TD			- 返回的空域数据
*   long lWidth		- 空域图象的宽度
*	 long lHeight		- 空域图象的高度
*	 COMPLEX* FD		- 输入的频域数据
*
* 返回值:
*   BOOL               - 成功返回TRUE，否则返回FALSE。
*
* 说明:
*   该函数进行二维快速付立叶逆变换。
*
************************************************************************/

void IFFT2(COMPLEX *TD, long lWidth, long lHeight, COMPLEX * FD)
{
	COMPLEX *TempT, *TempF;
	// 循环变量
	long	i;
	long	j;

	// 进行傅里叶变换的宽度和高度（2的整数次方）
	long w = 1;
	long h = 1;
	int wp = 0;
	int hp = 0;

	// 计算进行傅里叶变换的宽度和高度（2的整数次方）
	while (w < lWidth){
		w *= 2;
		wp++;
	}
	while (h < lHeight){
		h *= 2;
		hp++;
	}

	// 计算图像每行的字节数
	//long lLineBytes = WIDTHBYTES(lWidth * 24);

	// 分配内存

	TempT = (COMPLEX *)malloc(sizeof(COMPLEX)*w);
	TempF = (COMPLEX *)malloc(sizeof(COMPLEX)*w);

	// 对x方向进行快速付立叶变换
	//rgb
	/*
	for (i = 0; i < h; i++)
	{
	for (k = 0; k < 3; k++)
	{
	// 抽取数据
	for (j = 0; j < w; j++)
	TempF[j] = FD[i * w * 3 + j * 3 + k];

	// 一维快速傅立叶变换
	IFFT(TempF, TempT, wp);

	// 保存变换结果
	for (j = 0; j < w; j++)
	FD[i * w * 3 + j * 3 + k] = TempT[j];
	}
	}
	*/
	//灰度
	for (i = 0; i < h; i++){
		// 抽取数据
		for (j = 0; j < w; j++)
			TempF[j] = FD[i * w + j];
		// 一维快速傅立叶变换
		IFFT(TempF, TempT, wp);
		// 保存变换结果
		for (j = 0; j < w; j++)
			FD[i * w + j] = TempT[j];
	}
	// 释放内存
	free(TempT);
	free(TempF);

	TempT = (COMPLEX *)malloc(sizeof(COMPLEX)*h);
	TempF = (COMPLEX *)malloc(sizeof(COMPLEX)*h);

	// 对y方向进行快速付立叶变换
	//rgb
	/*
	for (i = 0; i < w * 3; i++)
	{
	// 抽取数据
	for (j = 0; j < h; j++)
	TempF[j] = FD[j * w * 3 + i];

	// 一维快速傅立叶变换
	IFFT(TempF, TempT, hp);

	// 保存变换结果
	for (j = 0; j < h; j++)
	TD[j * w * 3 + i] = TempT[j];
	}
	*/
	//灰度
	for (i = 0; i < w; i++){
		// 抽取数据
		for (j = 0; j < h; j++)
			TempF[j] = FD[j * w + i];
		// 一维快速傅立叶变换
		IFFT(TempF, TempT, hp);
		// 保存变换结果
		for (j = 0; j < h; j++)
			TD[j * w + i] = TempT[j];
	}
	// 释放内存
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

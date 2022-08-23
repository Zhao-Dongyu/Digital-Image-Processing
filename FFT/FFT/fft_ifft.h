#pragma once
#ifndef COM_H_INCLUDED
#define COM_H_INCLUDED

#define pi (double)3.14159265359

/*复数定义*/
typedef struct
{
	double re;
	double im;
}COMPLEX;


/*复数加运算*/
static COMPLEX Add(COMPLEX c1, COMPLEX c2)
{
	COMPLEX c;
	c.re = c1.re + c2.re;
	c.im = c1.im + c2.im;
	return c;
}


/*复数减运算*/

static COMPLEX Sub(COMPLEX c1, COMPLEX c2)
{
	COMPLEX c;
	c.re = c1.re - c2.re;
	c.im = c1.im - c2.im;
	return c;
}

/*复数乘运算*/

static COMPLEX Mul(COMPLEX c1, COMPLEX c2)
{
	COMPLEX c;
	c.re = c1.re*c2.re - c1.im*c2.im;
	c.im = c1.re*c2.im + c2.re*c1.im;
	return c;
}
void FFT(COMPLEX * TD, COMPLEX * FD, int power);
void IFFT(COMPLEX *FD, COMPLEX *TD, int power);
void FFT2(COMPLEX * TD, long lWidth, long lHeight, COMPLEX  * FD);
void IFFT2(COMPLEX *TD, long lWidth, long lHeight, COMPLEX * FD);

#endif

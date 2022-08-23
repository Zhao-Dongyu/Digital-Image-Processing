#pragma once

#define height  440  
#define width   455

typedef unsigned char  BYTE;    // 定义BYTE类型，占1个字节 

void FILT33MEAN(void *I_image, void *O_image, int size_x, int size_y);
void FILT33GMV(void *I_image, void *O_image, int size_x, int size_y);
void FILT_MIDDLE(void *I_image, void *O_image, int size_x, int size_y);

#pragma once

#define height  440  
#define width   455

typedef unsigned char  BYTE;    // ����BYTE���ͣ�ռ1���ֽ� 

void FILT33MEAN(void *I_image, void *O_image, int size_x, int size_y);
void FILT33GMV(void *I_image, void *O_image, int size_x, int size_y);
void FILT_MIDDLE(void *I_image, void *O_image, int size_x, int size_y);

#ifndef __FFT_IFFT_H

#define __FFT_IFFT_H

#include "arm_math.h"
#include "math.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "tim.h"

#define FFT_IFFT_SIZE 1024
#define FFT_IFFT_SAMPLE_RATE 40000  //ADDA采样率相同

//FFT_IFFT控制结构体
typedef struct {
	uint16_t FFT_IFFT_adc_data[FFT_IFFT_SIZE*2];
	//三个缓冲区
	float FFT_IFFT_INPUT_COPY[FFT_IFFT_SIZE];       //复制并单位转换
	float FFT_IFFT_OUTPUT[FFT_IFFT_SIZE];           //FFT变换结果缓存
	float FFT_IFFT_OUTPUT_FILTER[FFT_IFFT_SIZE];    //FFT滤波结果缓存
	float FFT_IFFT_OUTPUT_FILTER_CHANGE[FFT_IFFT_SIZE];    //IFFT滤波结果缓存
	uint16_t FFT_IFFT_OUTPUT_BUFFER_1[FFT_IFFT_SIZE];  //变换单位之后缓冲区——1输出
	uint16_t FFT_IFFT_OUTPUT_BUFFER_2[FFT_IFFT_SIZE];  //缓冲区——2输出
	
	uint16_t FFT_IFFT_dac_data[FFT_IFFT_SIZE*2];
} FFT_IFFT_HandleTypeDef;

void FFT_IFFT_Iint(FFT_IFFT_HandleTypeDef *hfftifft);


extern FFT_IFFT_HandleTypeDef ADC1_CH1_FFT_IFFT;

#endif

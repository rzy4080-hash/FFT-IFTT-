#include "FFT_IFFT.h"

FFT_IFFT_HandleTypeDef ADC1_CH1_FFT_IFFT;
arm_rfft_fast_instance_f32 S;

//ADC半中断回调逻辑
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	//1.更新后半缓冲区
	for (int i = FFT_IFFT_SIZE; i < FFT_IFFT_SIZE*2; i++)
	{
		ADC1_CH1_FFT_IFFT.FFT_IFFT_dac_data[i] = ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT_BUFFER_2[i];
	}
	//2.复制前半缓冲区
		for (int i = 0; i < FFT_IFFT_SIZE; i++)
	{
		ADC1_CH1_FFT_IFFT.FFT_IFFT_INPUT_COPY[i] = ADC1_CH1_FFT_IFFT.FFT_IFFT_adc_data[i] / 4095.0f * 3.5f;
	}
	//3.对前半缓冲区进行FFT变换
	arm_rfft_fast_f32(&S, ADC1_CH1_FFT_IFFT.FFT_IFFT_INPUT_COPY, ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT, 0);
	
	//4.对前半缓冲区进行滤波处理
	for (int i = 200; i < FFT_IFFT_SIZE; i++)
	{
		ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT[i] = 0;
	}
	//5.对处理过的前半缓冲区进行IFFT重建
	arm_rfft_fast_f32(&S, ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT, ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT_FILTER_CHANGE, 1);
	//6.转换单位
	for (int i = 0; i < FFT_IFFT_SIZE; i++)
	{
		ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT_BUFFER_1[i] = 1000+ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT_FILTER_CHANGE[i]/3.3f*3000;
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	//1.更新前半缓冲区
	for (int i = 0; i < FFT_IFFT_SIZE; i++)
	{
		ADC1_CH1_FFT_IFFT.FFT_IFFT_dac_data[i] = ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT_BUFFER_1[i];
	}
	//2.复制后半缓冲区
		for (int i = FFT_IFFT_SIZE; i < FFT_IFFT_SIZE*2; i++)
	{
		ADC1_CH1_FFT_IFFT.FFT_IFFT_INPUT_COPY[i] = ADC1_CH1_FFT_IFFT.FFT_IFFT_adc_data[i] / 4095.0f * 3.5f;
	}
	//3.对前半缓冲区进行FFT变换
	arm_rfft_fast_f32(&S, ADC1_CH1_FFT_IFFT.FFT_IFFT_INPUT_COPY, ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT, 0);
	
	//4.对前半缓冲区进行滤波处理
	for (int i = 200; i < FFT_IFFT_SIZE; i++)
	{
		ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT[i] = 0;
	}
	//5.对处理过的前半缓冲区进行IFFT重建
	arm_rfft_fast_f32(&S, ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT, ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT_FILTER_CHANGE, 1);
	//6.转换单位
	for (int i = 0; i < FFT_IFFT_SIZE; i++)
	{
		ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT_BUFFER_2[i] = 1000+ADC1_CH1_FFT_IFFT.FFT_IFFT_OUTPUT_FILTER_CHANGE[i]/3.3f*3000;
	}
}

void FFT_IFFT_Iint(FFT_IFFT_HandleTypeDef *hfftifft)
{
	arm_rfft_fast_init_f32(&S, FFT_IFFT_SIZE);
	for (int i = 0; i < FFT_IFFT_SIZE*2; i++)
	{
		ADC1_CH1_FFT_IFFT.FFT_IFFT_adc_data[i] = 2048;
	}
	
	for (int i = 0; i < FFT_IFFT_SIZE*2; i++)
	{
		ADC1_CH1_FFT_IFFT.FFT_IFFT_dac_data[i] = 2048;
	}
	
}
	








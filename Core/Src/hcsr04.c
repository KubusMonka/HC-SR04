//Jakub Mońka
#include "main.h"
#include "gpio.h"
#include "hcsr04.h"


HCSR04_Status_t HCSR04Init (HCSR04_t *hcsr04, TIM_HandleTypeDef *htimer, GPIO_TypeDef *Trig_Port, uint16_t Trig_Pin,GPIO_TypeDef *Echo_Port, uint16_t Echo_Pin)
{
	hcsr04->htim = htimer;
	hcsr04->Trigger_Port = Trig_Port;
	hcsr04->Trigger_Pin = Trig_Pin;
	hcsr04->Echo_Port = Echo_Port;
	hcsr04->Echo_Pin = Echo_Pin;

	HAL_TIM_Base_Start(hcsr04->htim);

	if(hcsr04->htim == NULL)
	{
		return HCSR04_InitError;
	} else
	{
		return 	HCSR04_OK;
	}

}

static void HAL_Delay_us (HCSR04_t *hcsr04, uint16_t time_us)
{
	hcsr04->htim->Instance->CNT = 0;

	while (hcsr04->htim->Instance->CNT <= time_us)
	{
		//just wait
	}
}

HCSR04_Status_t HCSR04StartMeasure (HCSR04_t *hcsr04)
{
	HAL_GPIO_WritePin(hcsr04->Trigger_Port,hcsr04->Trigger_Pin,GPIO_PIN_SET);
	HAL_Delay_us(hcsr04, 10);

	HAL_GPIO_WritePin(hcsr04->Trigger_Port,hcsr04->Trigger_Pin,GPIO_PIN_RESET);
	return 	HCSR04_OK;
}

HCSR04_Status_t HCSR04WaitForResponse (HCSR04_t *hcsr04)
{

	while(GPIO_PIN_RESET == HAL_GPIO_ReadPin(hcsr04->Echo_Port,hcsr04->Echo_Pin))
			{
		// wait for rising edge
			}
	hcsr04->htim->Instance->CNT = 0;


	while ( GPIO_PIN_SET == HAL_GPIO_ReadPin(hcsr04->Echo_Port,hcsr04->Echo_Pin))
	{
		// wait for falling edge
	}
	hcsr04->Result_us = hcsr04->htim->Instance->CNT;

	return 	HCSR04_OK;
}

HCSR04_Status_t HCSR04CalculateResultFloat (HCSR04_t *hcsr04, float *Result)
{

	*Result = ((float)hcsr04->Result_us) * HCSR04_CALCULATION_CONST ; //T*V
	return 	HCSR04_OK;
}


HCSR04_Status_t HCSR04CalculateResultIntiger (HCSR04_t *hcsr04, uint16_t *Result)
{

	*Result = (hcsr04->Result_us) /58  ; //Documentation SCSR04
	return 	HCSR04_OK;
}














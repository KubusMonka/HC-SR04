//Jakub Mońka
#include "main.h"
#include "gpio.h"
#include "hcsr04.h"


HCSR04_Status_t HCSR04Init (HCSR04_t *hcsr04, TIM_HandleTypeDef *htim_trigger,TIM_HandleTypeDef *htim_echo,
							uint32_t Trigger_TimChannel,uint32_t Echo_TimChannelStart, uint32_t Echo_TimChannelStop)
{
	hcsr04->htim_echo =htim_echo;
	hcsr04->htim_trigger = htim_trigger;
	hcsr04->Trigger_TimChannel = Trigger_TimChannel;
	hcsr04->Echo_TimChannelStart = Echo_TimChannelStart;
	hcsr04->Echo_TimChannelStop = Echo_TimChannelStop;

	HAL_TIM_Base_Start(hcsr04->htim_echo);

	HAL_TIM_IC_Start(hcsr04->htim_echo,hcsr04->Echo_TimChannelStart);
	HAL_TIM_IC_Start_IT(hcsr04->htim_echo,hcsr04->Echo_TimChannelStop);

	HAL_TIM_Base_Start(hcsr04->htim_trigger);
	HAL_TIM_PWM_Start(hcsr04->htim_trigger,hcsr04->Trigger_TimChannel);
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

void HCSR04_InterruptHandler(HCSR04_t *hcsr04)
{

	hcsr04->Result_us = __HAL_TIM_GET_COMPARE(hcsr04->htim_echo,hcsr04->Echo_TimChannelStop) - __HAL_TIM_GET_COMPARE(hcsr04->htim_echo,hcsr04->Echo_TimChannelStart);


}


//static void HAL_Delay_us (HCSR04_t *hcsr04, uint16_t time_us)
//{
//	hcsr04->htim->Instance->CNT = 0;
//
//	while (hcsr04->htim->Instance->CNT <= time_us)
//	{
//		//just wait
//	}
//}

//HCSR04_Status_t HCSR04StartMeasure (HCSR04_t *hcsr04)
//{
//	HAL_GPIO_WritePin(hcsr04->Trigger_Port,hcsr04->Trigger_Pin,GPIO_PIN_SET);
//	HAL_Delay_us(hcsr04, 10);
//
//	HAL_GPIO_WritePin(hcsr04->Trigger_Port,hcsr04->Trigger_Pin,GPIO_PIN_RESET);
//	return 	HCSR04_OK;
//}

//HCSR04_Status_t HCSR04WaitForResponse (HCSR04_t *hcsr04)
//{
//
//
////	while(GPIO_PIN_RESET == HAL_GPIO_ReadPin(hcsr04->Echo_TimChannelStart,hcsr04->Echo_TimChannelStop))
////			{
////		// wait for rising edge
////			}
////	hcsr04->htim->Instance->CNT = 0;
////
////
////	while ( GPIO_PIN_SET == HAL_GPIO_ReadPin(hcsr04->Echo_TimChannelStart,hcsr04->Echo_TimChannelStop))
////	{
////		// wait for falling edge
////	}
////	hcsr04->Result_us = hcsr04->htim->Instance->CNT;
//
//	return 	HCSR04_OK;
//}















//Jakub Mońka


#ifndef INC_HCSR04_H_
#define INC_HCSR04_H_



#define HCSR04_CALCULATION_CONST ((float)0.01715)

typedef enum
{
	HCSR04_OK = 0,
	HCSR04_Error,
	HCSR04_InitError,
	HCSR04_CalculationError




}HCSR04_Status_t;

typedef struct
{
	HCSR04_Status_t 	Status;
	TIM_HandleTypeDef 	*htim;

	GPIO_TypeDef 		*Trigger_Port;
	uint16_t 			Trigger_Pin;

	uint32_t 		Echo_TimChannelStart;
	uint32_t 		 Echo_TimChannelStop;

	uint16_t 			Result_us;



} HCSR04_t;


HCSR04_Status_t HCSR04Init (HCSR04_t *hcsr04, TIM_HandleTypeDef *htimer, GPIO_TypeDef *Trig_Port, uint16_t Trig_Pin,uint32_t Echo_TimChannelStart, uint32_t Echo_TimChannelStop);
HCSR04_Status_t HCSR04StartMeasure (HCSR04_t *hcsr04);
HCSR04_Status_t HCSR04WaitForResponse (HCSR04_t *hcsr04);
HCSR04_Status_t HCSR04CalculateResultFloat (HCSR04_t *hcsr04, float *Result);
HCSR04_Status_t HCSR04CalculateResultIntiger (HCSR04_t *hcsr04, uint16_t *Result);
void HCSR04_InterruptHandler(HCSR04_t *hcsr04);


#endif /* INC_HCSR04_H_ */

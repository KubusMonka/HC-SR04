# HC-SR04 

Working with HC-SR04 on STM32F411RE

Steps:
- GPIO - Input/Output - Code with blocking functions 
- Unblock Echo with (Timer- Input Compare)
- Unblock Trigger with PWM

Logic Analyzer
![Trigger](https://github.com/KubusMonka/HC-SR04/assets/32546678/6b3bf69d-75f0-473f-a061-4c562a18ad61)

/* Timer Tick 1us */

/*ECHO - Input Compare - TIM3 -Compare CCR2 and CCR1 (htim->Instance->)
Channel1-direct 
Channel2-indirect
*/

/*Trigger - PWM - TIM3 - Channel3 */

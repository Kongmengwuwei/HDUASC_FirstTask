#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "streamLED.h"
#include "Key.h"
#include "menu.h"
#include "Timer.h"
#include "Encoder.h"

int main(){
	
	OLED_Init();
	LED_Init();
	Key_Init();
	Timer_Init();
	Encoder_Init();
		
	int menu2;
	
	while(1)
	{		
		menu2 =menu1();
		if(menu2==1){menu2_LED();}
		if(menu2==2){menu2_PID();}
		if(menu2==3){menu2_Image();}
		if(menu2==4){menu2_Angle();}
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Key_Tick();
		StreamLED_Tick();
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

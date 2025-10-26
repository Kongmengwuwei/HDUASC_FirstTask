#include "stm32f10x.h"                  // Device header
#include "Delay.h"

extern uint8_t LED_dir;
extern uint8_t LED_speed;

void LED_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void LED_Stream(void){
	
	static uint8_t LEDnum=0;
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	
	if(LEDnum==5)LEDnum=1;
	if(LEDnum==0)LEDnum=4;
	switch(LEDnum){
		case 1:
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			break;
		case 2:
			GPIO_ResetBits(GPIOB,GPIO_Pin_13);
			break;
		case 3:
			GPIO_ResetBits(GPIOB,GPIO_Pin_14);
			break;
		case 4:
			GPIO_ResetBits(GPIOB,GPIO_Pin_15);
			   break;
		default:
			break;
		}
	if(LED_dir==1)LEDnum++;
	if(LED_dir==0)LEDnum--;	
		
	switch(LED_speed){
		case 0:
			Delay_ms(500);
			break;
		case 1:
		    Delay_ms(1000);
			break;
		case 2:
			Delay_ms(200);
			break;
		default:
			break;
	}
}


void StreamLED_Tick(void){
	static uint16_t Count;
	static uint16_t time;
	static uint8_t LEDnum;
	switch(LED_speed){
		case 0:
			time=500;
			break;
		case 1:
		    time=1000;
			break;
		case 2:
			time=200;
			break;
		default:
			break;
	}
	
	Count++;
	if (Count >= time)
	{
		Count = 0;
		
		GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		if(LEDnum==5)LEDnum=1;
		if(LEDnum==0)LEDnum=4;
		switch(LEDnum){
			case 1:
				GPIO_ResetBits(GPIOB,GPIO_Pin_12);
				break;
			case 2:
				GPIO_ResetBits(GPIOB,GPIO_Pin_13);
				break;
			case 3:
				GPIO_ResetBits(GPIOB,GPIO_Pin_14);
				break;
			case 4:
				GPIO_ResetBits(GPIOB,GPIO_Pin_15);
			    break;
			default:
				break;
			}
		if(LED_dir==0)LEDnum++;
		if(LED_dir==1)LEDnum--;			
	}
}

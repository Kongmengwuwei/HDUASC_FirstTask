#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Key.h"
#include "Encoder.h"

uint8_t LED_speed=0,LED_dir=0;
uint8_t kp[2],ki[2],kd[2];

int Edit_LED(uint8_t *p,int flag){
	OLED_ShowChar(1,16,'E');
	while(1){
		OLED_ShowNum(flag+1,16,*p,1);
		
		if(flag==1){
			if(*p==3)*p=0;
			if(*p>3)*p=2;
		}
		if(flag==2){
			if(*p==2)*p=0;
			if(*p>2)*p=1;
		}
		
		if (Key_Check(KEY_1,KEY_SINGLE)){//增加
			*p+=1;
		}
		if (Key_Check(KEY_2,KEY_SINGLE)){//减少
			*p-=1;
		}
		if (Key_Check(KEY_3,KEY_UP)){//取消选中
			OLED_ShowChar(1,16,' ');
			return 0;
		}
	}
}

int Edit_PID(uint8_t *p,int flag){
	OLED_ShowChar(1,16,'E');
	while(1){
		OLED_ShowNum(flag+1,16,*p,1);
		OLED_ShowSignedNum(flag+1,13,*(p+1),1);
		
		*p+=Encoder_Get();
		
		if (Key_Check(KEY_1,KEY_SINGLE)){//增加
			*p+=1;
		}
		if (Key_Check(KEY_1,KEY_REPEAT)){//增加
			*p+=1;
		}
		if (Key_Check(KEY_2,KEY_SINGLE)){//减少
			*p-=1;
		}
		if (Key_Check(KEY_2,KEY_REPEAT)){//增加
			*p-=1;
		}
		if (Key_Check(KEY_3,KEY_UP)){//取消选中
			OLED_ShowChar(1,16,' ');
			return 0;
		}
		
		if(*p==10){
			*p=0;
			*(p+1)+=1;		
		}
		if(*p>10){
			*p=9;
			*(p+1)-=1;		
		}
		if(*(p+1)>10){
			*p=0;
			*(p+1)=0;
		}
	}
}

int menu1(void){
	
	static uint8_t Flag =1;
	OLED_ShowString(1,2," LED Control");
	OLED_ShowString(2,2," PID");
	OLED_ShowString(3,2," Image");
	OLED_ShowString(4,2," Angle");
	while(1){
		
		if (Key_Check(KEY_1,KEY_SINGLE)){//上升
			Flag--;
			if(Flag==0)Flag=4;
		}
		if (Key_Check(KEY_2,KEY_SINGLE)){//下降
			Flag++;
			if(Flag==5)Flag=1;
		}
		if (Key_Check(KEY_3,KEY_UP)){//确认
			OLED_Clear();
			return Flag;
		}

		switch(Flag){
			case 1:
				OLED_ShowChar(1,1,'>');
			    OLED_ShowChar(2,1,' ');
		        OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,' ');
			    break;
			case 2:
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,'>');
			    OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,' ');
			    break;
			case 3:
				OLED_ShowChar(1,1,' ');
		        OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,'>');
				OLED_ShowChar(4,1,' ');
			    break;
			case 4:
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,'>');
			    break;
			default:
				break;
		}
	}
	
}

int menu2_LED(void){
	uint8_t flag =1;
	OLED_ShowString(1,1,"LED Control");
	OLED_ShowString(2,2,"LED_speed");
	OLED_ShowString(3,2,"LED_dir");
	while(1){
		OLED_ShowNum(2,16,LED_speed,1);
		OLED_ShowNum(3,16,LED_dir,1);
		
		if (Key_Check(KEY_1,KEY_SINGLE)){//上升
			flag--;
			if(flag==0)flag=2;
		}
		if (Key_Check(KEY_2,KEY_SINGLE)){//下降
			flag++;
			if(flag==3)flag=1;
		}
		if (Key_Check(KEY_3,KEY_UP)){//选中
			if(flag==1)Edit_LED(&LED_speed,flag);
			if(flag==2)Edit_LED(&LED_dir,flag);
		}
		if (Key_Check(KEY_4,KEY_UP)){//返回
			OLED_Clear();
			return 0;
		}
		switch(flag){
			case 1:
				OLED_ShowChar(2,1,'>');
			    OLED_ShowChar(3,1,' ');
			    break;
			case 2:
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,'>');
			    break;
			default:
				break;
		}
	}
}
int menu2_PID(void){
	uint8_t flag =1;
	OLED_ShowString(1,1,"PID");
	OLED_ShowString(2,2,"kp");
	OLED_ShowString(3,2,"ki");
	OLED_ShowString(4,2,"kd");
	kp[0]=8,ki[0]=1,kd[0]=5;
	while(1){
		OLED_ShowSignedNum(2,13,kp[1],1);
		OLED_ShowSignedNum(3,13,ki[1],1);
		OLED_ShowSignedNum(4,13,kd[1],1);
		OLED_ShowChar(2,15,'.');
		OLED_ShowChar(3,15,'.');
		OLED_ShowChar(4,15,'.');
		OLED_ShowNum(2,16,kp[0],1);
		OLED_ShowNum(3,16,ki[0],1);
		OLED_ShowNum(4,16,kd[0],1);

		if (Key_Check(KEY_1,KEY_SINGLE)){//上升
			flag--;
			if(flag==0)flag=3;
		}
		if (Key_Check(KEY_2,KEY_SINGLE)){//下降
			flag++;
			if(flag==4)flag=1;
		}
		if (Key_Check(KEY_3,KEY_UP)){//选中
			if(flag==1)Edit_PID(kp,flag);
			if(flag==2)Edit_PID(ki,flag);
			if(flag==3)Edit_PID(kd,flag);
		}
		if (Key_Check(KEY_4,KEY_UP)){//返回
			OLED_Clear();
			return 0;
		}
		switch(flag){
			case 1:
				OLED_ShowChar(2,1,'>');
			    OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,' ');
			    break;
			case 2:
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,'>');
				OLED_ShowChar(4,1,' ');
			    break;
			case 3:
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,' ');
			    OLED_ShowChar(4,1,'>');
			default:
				break;
		}
	}
}

int menu2_Image(void){
	OLED_ShowString(1,1,"Image");
	OLED_ShowString(2,1,">Image");
	while(1){
		if (Key_Check(KEY_4,KEY_UP)){//返回
			OLED_Clear();
			return 0;
		}
	}
}

int menu2_Angle(void){
	OLED_ShowString(1,1,"Angle");
	OLED_ShowString(2,1,">Angle");
	while(1){
		if (Key_Check(KEY_4,KEY_UP)){//返回
			OLED_Clear();
			return 0;
		}
	}
}

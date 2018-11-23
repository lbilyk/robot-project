#include "main.h"
//variable names for the commands and needed words
	static const char* test = ".";
	static const char* space = " ";
	static const char* mot = "motor";
	static const char* Left = "left";
	static const char* Right = "right";
	static const char* Forward = "forward";
	static const char* Backward = "back";
	static const char* Stop = "stop";
	static const char* servo = "servo";
	static const char* stepper = "stepper";
	static const char* stop = "stop";

//static void TIM_Config(void);
int main(void)
{
	const char* tx = ">";
	uint8_t rxbyte;
	int index;
	uint8_t echobit [2];
	uint8_t Buffer[100];
	const char* endofstr =  "\r\n";
	const char newl = '\n';
	const char endl = '\r';
	initializeSystems();

	USARTInit();
	USARTSend(endl);
	USARTSend(newl);
	sendstr((uint8_t*)tx);

	while(1)
		{
			rxbyte = USART_R(USART1);

      //if the received bit is a delete key
      if (rxbyte == '\b') {
          //set the character that was wrong to null
          Buffer[index - 1] = '\0';
          //index backwards
          index = index - 1;
					//show the change
					USARTSend('\b');
      }

      //if the recieved key is enter
      else if (rxbyte == '\r' || index == 100) {
          //adds a new line and end of string to what was sent
					sendstr((uint8_t*)endofstr);
					
          //in case you want to see what was sent
					//sendstr(Buffer);sendstr((uint8_t*)endofstr);
					
					//reset buffer and string index
					commandselect(Buffer);sendstr((uint8_t*)endofstr);
				
					//re transmitt the command promt signal
          sendstr((uint8_t*)tx);

					index = 0;
          memset(Buffer, 0, sizeof(Buffer));
					
      }

      //if recived key is not special case
      else {
          //echo back if no conditions met
          Buffer[index] = rxbyte;
          //echobit[0] = rxbyte;
					//echo back what you put in 
					USARTSend(Buffer[index]);
          //setting the buffer for whole word and what is echoed back
          index++;
		}
	
	}
	
	return 1;
}

void sendstr(uint8_t* Buffer)
{
	for(int i = 0; i < (strlen((const char*)Buffer));i++)
	USARTSend(Buffer[i]);
	
	return;
}
void delay(unsigned int time)
{
	for(int i = 0; i < time; i++);

	return;
}


void commandselect(uint8_t* command)
{
	char* argument;
	
	//w in these just stands for word version ie speedw is speed as a char
	char* speedw;
	int speed;
	char* anglew;
	int angle;
	char* dirw;
	int dir;
	char* test;
	strcpy(test,(const char*)command);
	LCD_clearscreen();
	

	argument = strtok((char*)command,space);
	LCD_displaystr(argument);
	if (strcmp(argument,mot) == 0){
			argument = strtok(NULL,space);// grabs argument
			LCD_displaystr(argument);
			speedw = strtok(NULL,space);//grabs the speed value
			LCD_displaystr(speedw);
			speed = atoi(speedw);//converts a given speed value to a value the board can read
			if (speed < 70) speed = 70; //sets the limit of lowest speed to 70 to avoid motor not running 
		
		//checks for the direction
				if(strcmp(argument,Forward) == 0)
					if (speed == NULL)
					motorControl(100,0);
				else
						motorControl(speed,0);
				else if(strcmp(argument,Left) == 0)
					motorControl(100,3);
				else if(strcmp(argument,Right) == 0)
					motorControl(100,2);
				else if(strcmp(argument,Backward) == 0)
					motorControl(100,1);
				else if(strcmp(argument,Stop) == 0)
					motorControl(100,4);
	}
	else if (strcmp(argument,servo) == 0){
		anglew = strtok(NULL,space);//grabs the speed value
		LCD_displaystr(anglew);
		angle = atoi(anglew);//converts a given speed value to a value the board can read
		if (angle > 180 ||angle < 0)
			angle = 90;
		Servo_SetAngle(angle);
	}
	else if (strcmp(argument,stepper) == 0)
	{
		dirw = strtok(NULL,space);//grabs the speed value
		dir = atoi(dirw);//converts a given dir value to a value the board can read
		LCD_displaystr(dirw);
		//loops if value is greater then 1 or less then 0
		if (dir > 1)
			{
			for (int i =0; i < dir ;i++)
				stepperControl(1);
			dir = 1;
			}
		else if (dir < 0)
			{
			for (int i =0; i > dir ;i--)
				stepperControl(0);
			}
			else{
				stepperControl(dir);
			}
	}
	else if (strcmp(argument,stop) == 0)
	{
		motorControl(100,4);
		Servo_SetAngle(90);
	}

	
}

void initializeSystems(void){

char* test;
	SysTickInit();
	pwmInit();
	stepperInit();
	switchInit();
	LCD_gpio();
	LCD_init();
	Delay(20);
	LCD_clearscreen();

	Servo_TimerInit();
	Servo_GPIOsetup();
	motorInit();
	
	
	stepperCalibrate();
	Servo_SetAngle(90);
	
	return;
	
}

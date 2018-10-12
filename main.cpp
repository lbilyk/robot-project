#include "main.h"
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
	Direction motor_direction;
	int speed =100; //at least 7
	int direction =0; //forward:0 || reverse:1 || right:2 || left:3 || stop:4
	
	SysTickInit();
	pwmInit();
	motorInit();
	stepperInit();
	LCD_gpio();
	LCD_init();
	switchInit();
	extInit();
	
		USARTInit();
		//USARTSend(endl);
		//USARTSend(newl);
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
	const char* pwm = "pwm";
	const char* test = "good to go";
	const char* test2 = "on";
	const char* test3 = "argument read";
	
	if (CompareC((uint8_t*)pwm, command) == 1)
		sendstr((uint8_t*)test);
	
	else if (CompareC((uint8_t*)pwm, command) == 2)
		if (argcheck(command,test2) == 1)
			sendstr((uint8_t*)test3);
			
}

int CompareC(uint8_t* baseword, uint8_t* command)
{
	//needed variable for later compairson
	int i;
	int length = (strlen((const char*)baseword));
	
	//check the letters up till the end of the string
	for(i = 0; i < length; i++)
	{
		if (baseword[i] != command[i] )
			return 0;
	}
	
	//check after the string if there is an argument
	if(command[i] == ' ')
		return 2;
	
	else
		return 1;
}

int argcheck (uint8_t* cmd,const char* argch)
{
	//variable for location of space
	int sloc;
	int length = strlen((const char*)cmd);
	uint8_t arg[5];
	
	for(int i = 0; i < length; i++)
	{
		if (cmd[i] == ' ' )
			sloc = i;
	}
	
	if (length > (sloc + 1))
		{
			for(int j = 0; j < length; j++)
				{
					arg[j] = cmd[(sloc+1) + j]; 
				}
				if (strcmp((const char*)arg,argch) == 0)
					return 1;
		}
		return 0;
}

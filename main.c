
static void TIM_Config(void);
extern void systemInit();

int main(void)
{
	int speed = 8;
	int dir = 0;
	
	void motorInit();
	int motorControl(speed, dir);
	
}
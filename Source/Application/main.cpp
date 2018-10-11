
//For CHIP_Init which must be called in main
#include "em_chip.h"

#include "Factory.hpp"
#include "Constants.hpp"

void auditBatterySimulator(Factory* factory);

// Globals for persistent storage
uint8_t cmd_array[I2C_CMD_ARRAY_SIZE];
uint8_t data_array[I2C_DATA_ARRAY_SIZE];

int main(void)
{
    /* Initialize chip and check for chip errata */
	CHIP_Init();

    Factory factory = Factory();
    StateManager* stateManager = factory.createStateManager();
    EFM32_Timer0* timer0 = factory.createTimer0();
    EFM32_I2C* I2C = factory.createI2C();
    EFM32_PWM* PWM0 = factory.createPWM();
    factory.createGPIO();

    /* Initializations */
    initTimer0();
    initUSART1();
    initI2C();

    timer0->start();

    static unsigned int referenceTime_microsecond;
    bool sendI2CCommandDelay = false;
    referenceTime_microsecond = timer0->getReferenceTime_microsecond();

    cmd_array[0] = 0x05;
	I2C->transfer(TEMP_SENSOR_ADDRESS, cmd_array, data_array, 1, 1, I2C_FLAG_WRITE);

	while(timer0 ->getElapsedTime_microsecond(referenceTime_microsecond) <= TIME_1_SECOND/1000){};
	referenceTime_microsecond = timer0->getReferenceTime_microsecond();

	cmd_array[0] = 0x05;
	I2C->transfer(TEMP_SENSOR_ADDRESS, cmd_array, data_array, 1, 2, I2C_FLAG_READ);

    /* Infinite loop */
    while (true)
    {
    	if (timer0->getElapsedTime_microsecond(referenceTime_microsecond) >= TIME_1_SECOND)
    	{
    		if (factory.m_PB0.readInput())
    		{
    			PWM0->onAndOffLED();
    		}

    		stateManager->execute();
    		referenceTime_microsecond = timer0->getReferenceTime_microsecond();

    		auditBatterySimulator(&factory);

    		sendI2CCommandDelay = false;
    	}

		if (!factory.m_PB1.readInput())
		{
			if (!sendI2CCommandDelay)
			{
				I2C->writeCommand(ACCELEROMETER_ADDRESS, 0x00, I2C_WRITE_READ);
				sendI2CCommandDelay = true;
			}
		}
    }
}

// Temp pour laudit
void auditBatterySimulator(Factory* factory)
{
	static int count = 0;

	switch (count)
	{
		case 0:
			factory->m_BAT.D0D1.setOutputHigh();
			count++;
			break;

		case 1:
			factory->m_BAT.D0D1.setOutputHigh();
			count++;
			break;

		case 2:
			factory->m_BAT.D2D3.setOutputHigh();
			count++;
			break;

		case 3:
			factory->m_BAT.D2D3.setOutputHigh();
			count++;
			break;

		case 4:
			factory->m_BAT.D4D5.setOutputHigh();
			count++;
			break;

		case 5:
			factory->m_BAT.D4D5.setOutputHigh();
			count++;
			break;

		case 6:
			factory->m_BAT.D6D7.setOutputHigh();
			count++;
			break;

		case 7:
			factory->m_BAT.D6D7.setOutputHigh();
			count++;
			break;

		case 8:
			factory->m_BAT.D8D9.setOutputHigh();
			count++;
			break;

		case 9:
			factory->m_BAT.D8D9.setOutputHigh();
			count++;
			break;

		default:
			count = 0;
			factory->m_BAT.D0D1.setOutputLow();
			factory->m_BAT.D2D3.setOutputLow();
			factory->m_BAT.D4D5.setOutputLow();
			factory->m_BAT.D6D7.setOutputLow();
			factory->m_BAT.D8D9.setOutputLow();
			break;
	}
}

/*
 * GPIO.hpp
 *
 *  Created on: Feb 13, 2018
 *      Author: lfani
 */

#ifndef INCLUDE_PERIPHERALS_EFM32GPIO_HPP_
#define INCLUDE_PERIPHERALS_EFM32GPIO_HPP_

#include "IGPIO.hpp"
#include "em_device.h"

class EFM32_GPIO: public IGPIO
{
public:
	EFM32_GPIO(unsigned short pinNumber, unsigned short bankLetter);
	~EFM32_GPIO() {};

	void turnOFF();
	void turnON();
	void toggle();

private:
	bool m_State;
	unsigned short m_PinNumber;
};


#endif /* INCLUDE_PERIPHERALS_EFM32GPIO_HPP_ */

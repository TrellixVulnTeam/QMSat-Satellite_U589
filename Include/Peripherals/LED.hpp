/*
 * LED.hpp
 *
 *  Created on: 2018-01-25
 *      Author: Guillaume
 */

#ifndef INCLUDE_EF32GG_LED_HPP_
#define INCLUDE_EF32GG_LED_HPP_

#include "ILED.hpp"

class LED: public ILED
{
public:
	LED();
	LED(unsigned short p_PinNumber);
	~LED() {};

	void turnOFF();
	void turnON();
	void toggle();

private:
	bool m_State;
	unsigned short m_PinNumber;
};

#endif /* INCLUDE_EF32GG_LED_HPP_ */

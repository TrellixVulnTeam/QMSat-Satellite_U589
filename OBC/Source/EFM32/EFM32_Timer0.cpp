/*
 * EFM32_Timer0.cpp
 *
 *  Created on: January 25, 2018
 *   Authors: Luis Anillo
 * 			  Guillaume Beaupré.
 *
 *   \brief Timer0 Class Definition
 */

#include "EFM32_Timer0.hpp"

static unsigned int s_ElapsedTime_Timer0_microsecond;
static unsigned int s_Period_Timer0_microsecond;
static unsigned int s_IntMaxValue = 4294967000;

/****************************************************/
EFM32_Timer0::EFM32_Timer0(unsigned int p_Period_microsecond)
{
	s_Period_Timer0_microsecond = p_Period_microsecond;
	TIMER0->TOP = p_Period_microsecond*24;  //HFPERCLK is at 24MHz
	m_ReferenceTime_microsecond = 0;
	s_ElapsedTime_Timer0_microsecond = 0;
}

void EFM32_Timer0::start() {
	TIMER0->CMD = 0x1;
}

void EFM32_Timer0::stop() {
	TIMER0->CMD = 0x2;
}

/****************************************************/
unsigned int EFM32_Timer0::getReferenceTime_microsecond()
{
	m_ReferenceTime_microsecond = s_ElapsedTime_Timer0_microsecond;
	return m_ReferenceTime_microsecond;
}

/****************************************************/
unsigned int EFM32_Timer0::getElapsedTime_microsecond(unsigned int p_ReferenceTime_microsecond)
{
	if (p_ReferenceTime_microsecond > s_ElapsedTime_Timer0_microsecond)
	{
		return((s_IntMaxValue - p_ReferenceTime_microsecond) + s_ElapsedTime_Timer0_microsecond);
	}
	return (s_ElapsedTime_Timer0_microsecond - p_ReferenceTime_microsecond);
}

/****************************************************/
/*interrupt d'incrémentation*/
void TIMER0_IRQHandler(void)
{
    TIMER0->IFC = 1; // Clear overflow flag
    s_ElapsedTime_Timer0_microsecond += s_Period_Timer0_microsecond;
    if(s_ElapsedTime_Timer0_microsecond >= s_IntMaxValue)
    {
    	s_ElapsedTime_Timer0_microsecond = 0; //Assure that the elapsed time stays within the limit of an int 32 bits
    }
}

/****************************************************/
/*initialization*/
void initTimer0()
{
	TIMER0->IEN = 1;             // Enable Timer0 overflow interrupt
	NVIC_EnableIRQ(TIMER0_IRQn); // Enable TIMER0 interrupt vector in NVIC
}

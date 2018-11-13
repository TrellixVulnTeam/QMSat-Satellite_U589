/*
 * RunState.cpp
 *
 *  Created on: 2018-01-25
 *      Author: Guillaume Beaupr�
 */

#include "RunState.hpp"

/****************************************************/
RunState::RunState()
{
	m_stateId = Run;
}

/****************************************************/
RunState::RunState(ISerialComm* p_UartUI, ISerialComm* p_UartAlim)
{
	m_stateId = Run;

	m_USART = p_UartUI;
	m_UartAlim = p_UartAlim;
}

/****************************************************/
short RunState::getStateId()
{
	return m_stateId;
}

/****************************************************/
void RunState::onEntry()
{
	//m_USART->sendSerial("Entering Run State\n",19);
}

/****************************************************/
short RunState::execute()
{
	//m_USART->sendSerial("Executing Run State\n",20);
	m_UartAlim->sendSerial("Sending to Alim...\n",19);
	return Init;
}

/****************************************************/
void RunState::onExit()
{

}



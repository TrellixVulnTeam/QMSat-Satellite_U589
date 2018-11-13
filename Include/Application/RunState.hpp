/*
 * RunState.hpp
 *
 *  Created on: 2018-01-25
 *      Author: Guillaume
 */

#ifndef INCLUDE_APPLICATION_RUNSTATE_HPP_
#define INCLUDE_APPLICATION_RUNSTATE_HPP_

#include "IState.hpp"
#include "ISerialComm.hpp"

class RunState: public IState
{
public:
	RunState();
	RunState(ISerialComm* p_UartUI, ISerialComm* p_UartAlim);
	~RunState() {};

	short getStateId();

private:
	short m_stateId;

	ISerialComm* m_USART;
	ISerialComm* m_UartAlim;

	void onEntry();
	void onExit();
	short execute();
};

#endif /* INCLUDE_APPLICATION_RUNSTATE_HPP_ */

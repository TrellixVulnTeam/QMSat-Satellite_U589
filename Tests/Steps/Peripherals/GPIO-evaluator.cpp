#include "GPIO-evaluator.hpp"

/**************************************************/
GPIOEvaluator::GPIOEvaluator()
{

}

/**************************************************/
void GPIOEvaluator::GPIOInitialiseInput(int p_pinNumber, int p_bankLetter, int p_typeIO)
{
    m_UUT = EFM32_GPIO(p_pinNumber, p_bankLetter, true, p_typeIO);
}

/**************************************************/
void GPIOEvaluator::GPIOInitialiseOutput(int p_pinNumber, int p_bankLetter, int p_typeIO)
{
    m_UUT = EFM32_GPIO(p_pinNumber, p_bankLetter, false, p_typeIO);
}

/**************************************************/
bool GPIOEvaluator::verifyInitializeError()
{
    return m_UUT.getError();
}

/**************************************************/
bool GPIOEvaluator::verifyIOType(int p_expectedInput)
{
    if (p_expectedInput == 1)
    {
        return m_UUT.getIsInput();
    }
    else
    {
        return !(m_UUT.getIsInput());
    }
}

/**************************************************/
bool GPIOEvaluator::GPIOSetState(int p_expectedState, int p_GPIOType)
{
    if (p_GPIOType == 0) //If it is an input
    {
        if (p_expectedState == 0) //If it is set low
            return !(m_UUT.setOutputLow()); //Should return false since INPUT

        if (p_expectedState == 1) //If it is set high
            return !(m_UUT.setOutputHigh()); //Should return false since INPUT
    }
    else //if (p_GPIOType == 1) //If it is an output
    {
        if (p_expectedState == 0) //If it is set low
            if (m_UUT.setOutputLow()) //Should return true if successful
                return !(m_UUT.readInput()); // Should return false since it's low

        if (p_expectedState == 1) //If it is set high
            if (m_UUT.setOutputHigh()) //Should return true if successful
                return m_UUT.readInput(); // Should return true since it's high
    }

    return false;

}

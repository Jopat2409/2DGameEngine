#include "..\include\engine\gametimer.hpp"
#include <iostream>

core::GameTimer::GameTimer()
{

}

int core::GameTimer::Init()
{
    m_StartTime = GetSystemTime();
    return 0;
}

void core::GameTimer::Exit()
{

}

void core::GameTimer::Tick()
{
    m_Tickbase += 1;
}

int core::GameTimer::GetTickbase()
{
    return m_Tickbase;
}

core::gametime_t core::GameTimer::GetGameTime()
{
    /**
     * Returns the current time in milliseconds
     *
     * @return current game time in milliseconds
    */
    return std::chrono::duration_cast<std::chrono::duration<gametime_t>>(GetSystemTime() - m_StartTime).count() * 1000;
}

core::timepoint_t core::GameTimer::GetSystemTime()
{
    return std::chrono::high_resolution_clock::now();
}

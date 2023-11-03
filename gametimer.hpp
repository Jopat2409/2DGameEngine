#ifndef _INTERNAL_GAMETIMER_H
#define _INTERNAL_GAMETIMER_H

#include "EngineExport.hpp"
#include "system.hpp"
#include <chrono>


namespace core{

    typedef double gametime_t;
    using timepoint_t = std::chrono::high_resolution_clock::time_point;

    class GameTimer : public System
    {
    public:

        GameTimer();

        int Init() override;
        void Exit() override;
        void Tick() override;

        ENGINE_API int GetTickbase();
        ENGINE_API gametime_t GetGameTime();


    private:

        int m_Tickbase{0};
        timepoint_t m_StartTime;

        timepoint_t GetSystemTime();
    };
}


#define SYS_TIMER "TIMER001"

#endif

// -*- lsst-c++ -*-
#ifndef _INTERNAL_CONVAR_H
#define _INTERNAL_CONVAR_H

#include "EngineExport.hpp"

#include <optional>
#include <cstdlib>
#include <cmath>


namespace core
{
    class ENGINE_API ConVar
    {
    public:
        ConVar(const char* name, const char* value);
        ConVar(const char* name, const char* value, float minValue, float maxValue);

        void ConstructConvar(const char* name, const char* value, 
                                        bool hasMinValue, float minValue, 
                                        bool hasMaxValue, float maxValue);

        ~ConVar();

        void AddConstraints(bool hasMinValue, float minValue, bool hasMaxValue, float maxValue);
        void SetValue(const char* value);
        void SetName(const char* name);

        inline int GetInt();
        float GetFloat();
        const char* GetString() { return m_szValue; };
        const char* GetName();
    private:
        std::optional<float> m_fValue;
        std::optional<int> m_nValue;
        const char* m_szValue;
        const char* m_szName;

        std::optional<float> m_fMinValue;
        std::optional<float> m_fMaxValue;

        void SetIntValue();
        void SetFloatValue();
    };
}

#endif

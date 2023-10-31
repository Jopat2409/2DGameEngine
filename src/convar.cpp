#include <engine/convar.hpp>
#include <engine/manager.hpp>
#include <engine/logger.hpp>

core::ConVar::ConVar(const char* name, const char* value)
{
    ConstructConvar(name, value, false, 0, false, 0);
}

core::ConVar::ConVar(const char* name, const char* value, float minValue, float maxValue)
{
    ConstructConvar(name, value, true, minValue, true, maxValue);
}

core::ConVar::~ConVar()
{
    //delete[] m_szName;
    //delete[] m_szValue;
}

void core::ConVar::ConstructConvar(const char* name, const char* value, 
                                        bool hasMinValue, float minValue, 
                                        bool hasMaxValue, float maxValue)
{
    SetName(name);
    SetValue(value);
    AddConstraints(hasMinValue, minValue, hasMaxValue, maxValue);
    GET_SYSTEM(SYS_CONSOLE, core::Console)->RegisterConvar(this);
}

void core::ConVar::SetValue(const char* value)
{
    m_szValue = value;
    SetFloatValue();
    SetIntValue();
}

void core::ConVar::SetFloatValue()
{
    int c_shift{0}, c_mult{-1}, count{0};
    float total{0};
    char c{m_szValue[count]};
    while(c != '\0')
    {
        // check for digit or .
        if(isdigit(c)){
            total += (c - '0')*pow(0.1, c_shift);
            c_shift++;
        }else if(c == '.' && c_mult == -1){
            c_mult = c_shift;
        }else{
            return;
        }
        count++;
        c = m_szValue[count];
    };
    total *= (c_mult == -1 ? c_shift : c_mult);
    m_fValue = total;
}

void core::ConVar::SetIntValue()
{
    if(m_fValue.has_value())
        m_nValue = (int)m_fValue.value();
}

void core::ConVar::SetName(const char* name)
{
    m_szName = name;
}

void core::ConVar::AddConstraints(bool hasMinValue, float minValue, bool hasMaxValue, float maxValue)
{
    if(hasMinValue)
        m_fMinValue = minValue;
    if(hasMaxValue)
        m_fMaxValue = maxValue;
}

const char* core::ConVar::GetName()
{
    return m_szName;
}

float core::ConVar::GetFloat()
{
    return m_fValue.value();
}

int core::ConVar::GetInt()
{
    return m_nValue.value();
}
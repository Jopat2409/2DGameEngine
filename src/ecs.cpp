#include "..\include\engine\ecs.hpp"

int ent::ECS::Init()
{
    return 0;
}
void ent::ECS::Exit()
{

}
void ent::ECS::Tick()
{

}
int ent::ECS::CreateEntity(int compFlags)
{
    int ent_id = GetNextEntity();
    GET_COMPONENT(ent_id, c_info).flags = compFlags;
}
int ent::ECS::GetNextEntity()
{
    m_entityPtr++;
    return m_entityPtr - 1;
}
int ent::ECS::GetMaxEntityIndex()
{
    return m_entityPtr;
}
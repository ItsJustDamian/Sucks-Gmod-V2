#include "C_BaseEntity.h"

int C_BaseEntity::GetHealth()
{
	typedef int(__thiscall * fn)(void*);
	return CallVFunc<fn>(this, 108)(this);
}

int C_BaseEntity::GetMaxHealth()

{
	typedef int(__thiscall * fn)(void*);
	return CallVFunc<fn>(this, 109)(this);
}

int C_BaseEntity::GetFlags()
{
	return *(int*)((uintptr_t)this + 0x350);
}

int C_BaseEntity::GetClassID()
{
	return 0;
}

bool C_BaseEntity::IsDead()
{
	typedef int(__thiscall * fn)(void*);
	return CallVFunc<fn>(this, 129)(this) == 0;
}

bool C_BaseEntity::IsAlive()
{
	return (!IsDead() && GetHealth() > 0);
}

QAngle C_BaseEntity::GetOrigin()
{
	return *(QAngle*)(((uintptr_t)this + 0x260));
}

QAngle C_BaseEntity::GetViewOffset()
{
	return *(QAngle*)(((uintptr_t)this + 0xE8));
}

QAngle C_BaseEntity::GetEyePos()
{
	return GetOrigin() + GetViewOffset();
}

bool C_BaseEntity::PushEntity()
{
	typedef bool(__thiscall * fn)(void*);
	return CallVFunc<fn>(this, 172)(this);
}

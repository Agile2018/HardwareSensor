#include "Memory.h"

Memory::Memory()
{
}

Memory::~Memory()
{
}

void Memory::SetSizeTotalMemory(long quantity)
{
	_sizeTotalMemory = quantity;
}

void Memory::SetMyConsumption(long quantity)
{
	_myConsumption = quantity;
}

long Memory::GetSizeTotalMemory()
{
	return _sizeTotalMemory;
}

long Memory::GetMyConsumption()
{
	return _myConsumption;
}


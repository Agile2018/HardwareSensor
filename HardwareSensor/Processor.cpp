#include "Processor.h"

Processor::Processor()
{
}

Processor::~Processor()
{
}

void Processor::SetConsumption(int consumption)
{
	_consumption = consumption;
}

int Processor::GetConsumption()
{
	return _consumption;
}


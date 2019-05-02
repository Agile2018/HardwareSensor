#include "Lot.h"

Lot::Lot()
{
}

Lot::~Lot()
{
}

void Lot::SetNumberOfFaces(int faces)
{
	_numberOfFaces = faces;
}

void Lot::SetTimeOfTemplate(double time)
{
	_timeOfTemplate = time;
}

double Lot::GetTimeOfTemplate()
{
	return _timeOfTemplate;
}

int Lot::GetNumberOfFaces()
{
	return _numberOfFaces;
}


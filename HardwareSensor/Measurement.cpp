#include "Measurement.h"

Measurement::Measurement()
{
}

Measurement::~Measurement()
{
}

void Measurement::Start()
{
	startCount = std::chrono::steady_clock::now();
}

void Measurement::End()
{
	endCount = std::chrono::steady_clock::now();
}

double Measurement::ElapseTime()
{
	auto time_span = static_cast<chrono::duration<double>>(endCount - startCount);
	return time_span.count();
}
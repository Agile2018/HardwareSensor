#include "Image.h"

Image::Image()
{
}

Image::~Image()
{
}

void Image::SetTimeOfDetection(double time)
{
	_timeOfDetection = time;
}

void Image::SetNumberOfFaces(int faces)
{
	_numberOfFaces = faces;
}

void Image::SetTimeOfTemplate(double time)
{
	_timeOfTemplate = time;
}

double Image::GetTimeOfTemplate()
{
	return _timeOfTemplate;
}

double Image::GetTimeOfDetection()
{
	return _timeOfDetection;
}

int Image::GetNumberOfFaces()
{
	return _numberOfFaces;
}

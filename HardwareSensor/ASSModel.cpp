#include "ASSModel.h"

ASSModel::ASSModel()
{
}

ASSModel::~ASSModel()
{
}

char* ASSModel::GetTemplate()
{
	return templateImage;
}

int ASSModel::GetSize()
{
	return templateSize;
}

void ASSModel::SetTemplate(char* templateInput)
{
	templateImage = templateInput;
}

void ASSModel::SetSize(int size)
{
	templateSize = size;
}


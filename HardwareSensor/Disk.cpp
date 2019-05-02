#include "Disk.h"

Disk::Disk()
{
}

Disk::~Disk()
{
}

void Disk::SetUseOfDisk(long size)
{
	_useOfDisk = size;
}

long Disk::GetUseOfDisk()
{
	return _useOfDisk;
}


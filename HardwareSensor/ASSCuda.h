#ifndef ASSCuda_h
#define ASSCuda_h

#include <cuda_runtime.h>
#include <helper_cuda.h>
#include "Format.h"
#include <iostream>
#include <memory>
#include <string>

class ASSCuda
{
public:
	ASSCuda();
	~ASSCuda();
	bool isExistCuda();
	string GetDescripton();
private:
	Format* format = new Format();
	string description;
};


#endif

#ifndef ASSInitLibRecognition_h
#define ASSInitLibRecognition_h

#include <iostream>
#include "iface.h"
#include "ASSFaceError.h"
#include <sstream> 
#include <fstream> 
#include "faceidkitlib.h"
using namespace std;

class ASSInitLibRecognition
{
public:
	ASSInitLibRecognition();
	~ASSInitLibRecognition();
	void InitLib();
	void SetParams(bool cuda);
	void SetConfigurationIdentify(string nameFile);
	void InitDatabase();
	ASSFaceError* aSFaceError = new ASSFaceError();
private:
	string GetConfiguration(string nameFile);
	bool InitCuda();
};

#endif
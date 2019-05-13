#include "InitHardwareSensor.h"

InitHardwareSensor::InitHardwareSensor(int detection, int cpu)
{
	bool cuda = false;
	if (cpu == 2) cuda = true;
	aSSInitLibRecognition->SetParams(cuda);
	aSSInitLibRecognition->InitLib();
	aSSCentralProcessingVideo->SetOptionDetection(detection);
	if (detection == 1)
	{
		cout << "SIMPLE DETECTION ENABLE" << endl;
	}
	else if (detection == 2)
	{
		cout << "BATCH DETECTION ENABLE" << endl;
	}
	if (!cuda)
	{
		cout << "CUDA NOT SELECTED" << endl;
	}
	else
	{
		cout << "CUDA SELECTED" << endl;
	}

}

InitHardwareSensor::~InitHardwareSensor()
{
}

void InitHardwareSensor::SetConfigurationIdentity(string fileName) {
	aSSCentralProcessingVideo->aSSFaceIdentify->SetConfiguration(fileName);
	aSSCentralProcessingVideo->aSSFaceIdentify->InitDatabase();
}

void InitHardwareSensor::SetFileconfigurationDetect(string fileName)
{

	aSSCentralProcessingVideo->aSSFaceDetect->SetFileConfiguration(fileName);
	aSSCentralProcessingVideo->aSSFaceDetect->setJsonConfig();
}

void InitHardwareSensor::SetConfigurationVideo(string fileName)
{
	aSSCentralProcessingVideo->aSSVideoConfig->FileConfiguration(fileName);
	aSSCentralProcessingVideo->aSSVideoConfig->setJsonConfig();
	manageDirectory->SetNameDirectory(aSSCentralProcessingVideo->aSSVideoConfig->getNameWindow());
	manageDirectory->CreateDirectoryVideo();
	aSSCentralProcessingVideo->SetDirectory(aSSCentralProcessingVideo->aSSVideoConfig->getNameWindow());

}

void InitHardwareSensor::RunProcessVideo()
{
	aSSCentralProcessingVideo->RunProcessVideo();
}
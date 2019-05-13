#ifndef InitHardwareSensor_h
#define InitHardwareSensor_h
#include "ASSInitLibRecognition.h"
#include "ASSCentralProcessingVideo.h"
#include "ManageFile.h"

class InitHardwareSensor
{
public:
	InitHardwareSensor(int detection, int cpu);
	~InitHardwareSensor();
	ASSCentralProcessingVideo* aSSCentralProcessingVideo = new ASSCentralProcessingVideo();
	void SetFileconfigurationDetect(string fileName);
	void SetConfigurationVideo(string fileName);
	void SetConfigurationIdentity(string fileName);
	void RunProcessVideo();

private:
	ManageFile* manageDirectory = new ManageFile();
	ASSInitLibRecognition* aSSInitLibRecognition = new ASSInitLibRecognition();

};


#endif // !InitHardwareSensor_h

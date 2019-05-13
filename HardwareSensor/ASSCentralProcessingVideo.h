#ifndef ASSCentralProcessingVideo_h
#define ASSCentralProcessingVideo_h

#include <chrono>
#include <thread>
#include "ASSCheckHardware.h"
#include "ASSVideoCapture.h"
#include "ASSFaceDetect.h"
#include "ASSFaceEither.h"
#include "ASSVideoConfig.h"
//#include "faceidkitlib.h"
#include "ASSFaceIdentify.h"
#include "ASSCuda.h"
#include <ctime>
#include <iomanip>
#include <stdlib.h>

const string LOG_HARDWARE_CONSUMPTION = "log_hardware_consumption.txt";
const string LOG_INFO_PROCESSOR = "log_processor.txt";

class ASSCentralProcessingVideo
{
public:
	ASSCentralProcessingVideo();
	~ASSCentralProcessingVideo();	
	ASSFaceDetect* aSSFaceDetect = new ASSFaceDetect();
	ASSVideoConfig* aSSVideoConfig = new ASSVideoConfig();
	ASSFaceIdentify* aSSFaceIdentify = new ASSFaceIdentify();
	void RunProcessVideo();
	void SetDirectory(string directory);
	void SetOptionDetection(int option);
	void SaveDetailsHardware();
	Rx::subject<Mat> frame;
	Rx::observable<Mat> observableFrame = frame.get_observable();
private:
	ASSCuda* aSSCuda = new ASSCuda();
	ASSCheckHardware* aSSCheckHardware = new ASSCheckHardware();
	ManageFile* manageLogHardware = new ManageFile();
	ManageFile* manageDetailProcessor = new ManageFile();
	Format* format = new Format();
	//Rx::subscriber<char*> templateOut = templateImage.get_subscriber();
	Rx::subscriber<Mat> frameOut = frame.get_subscriber();
	void ObserverError();
	void ObserverTemplateImage();
	void Identify(ASSModel* modelImage);
	string GetTimeInitProcess();
	void SetTimeLogs();
	//void ObserverTemplate();
	//void InitParamsDetect();	
	void SaveDataHardwareConsumption();
	string _directory;
	ASSVideoCapture* aSSVideoCapture = new ASSVideoCapture(aSSVideoConfig);
	//int SetStateFlow(int day, int minute);
	//double timeDurationSingle = 0;
	void RefreshData();
	std::chrono::steady_clock::time_point startCountFacesDetected = std::chrono::steady_clock::now();
	//int countImagesDetected = 0;
	int optionProcess = 1;
	void SingleDetection(Mat image);
	void BatchDetection(Mat image);
	void DetectFaces(Mat image);
	bool flagNextFrame = false;
	//void GetImage(Mat image);
	
};




#endif
#include "ASSCentralProcessingVideo.h"

ASSCentralProcessingVideo::ASSCentralProcessingVideo()
{
	aSSCheckHardware->GetSystemTimesAddress();
	//InitParamsDetect();
	ObserverError();
	manageLogHardware->SetNameFile(LOG_HARDWARE_CONSUMPTION);
	manageDetailProcessor->SetNameFile(LOG_INFO_PROCESSOR);
	//ObserverTemplate();
}

ASSCentralProcessingVideo::~ASSCentralProcessingVideo()
{
}

void ASSCentralProcessingVideo::ObserverError()
{
	auto faceError = aSSFaceDetect->observableError.map([](string message) {
		return message;
	});

	auto subscriptionError = faceError.subscribe([this](string message) {
		cout << message << endl;
		
	});
}

void ASSCentralProcessingVideo::SetTimeLogs() {
	string date = GetTimeInitProcess();
	manageLogHardware->WriteFile(date);
	aSSFaceDetect->InitDateLogs(date);
}

string ASSCentralProcessingVideo::GetTimeInitProcess() {
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	string date = format->FormatString("INIT LOG UTC: %s\n",
		asctime(timeinfo));
	return date;
}

void ASSCentralProcessingVideo::SaveDataHardwareConsumption() {
	std::time_t t = std::time(nullptr);
	tm *ltm = std::localtime(&t);
	int hour = ltm->tm_hour;
	int min = ltm->tm_min;

	string time = to_string(hour) + ":" + to_string(min);
	long memory = aSSCheckHardware->CheckMemoryCurrentlyAvailable();
	int cpuUse = aSSCheckHardware->CpuUsage();
	string log = time + "," + to_string(memory) + "," + to_string(cpuUse) + "\n";
	manageLogHardware->WriteFile(log);

}


void ASSCentralProcessingVideo::RefreshData() {
	std::chrono::steady_clock::time_point endCountFacesDetected = std::chrono::steady_clock::now();
	int diff = std::chrono::duration_cast<std::chrono::minutes>(endCountFacesDetected - startCountFacesDetected).count();
	if (diff >= 1)
	{
		
		std::thread(&ASSCentralProcessingVideo::SaveDataHardwareConsumption, this).detach();
		startCountFacesDetected = std::chrono::steady_clock::now();
		
	}
}

void ASSCentralProcessingVideo::SingleDetection(Mat image) {
	aSSVideoCapture->writeImage(image);
	
	aSSFaceDetect->SetFileImage(aSSVideoCapture->GetNameWindow() + "/" + aSSVideoCapture->GetNameFileImage());
	/*chrono::steady_clock sc;
	auto start = sc.now();*/
	int count = aSSFaceDetect->ProccessDetectSingle();
	/*if (count != 0)
	{
		auto end = sc.now();
		auto time_span = static_cast<chrono::duration<double>>(end - start);
		timeDurationSingle = time_span.count();

	}*/
	//countImagesDetected += count;
}

void ASSCentralProcessingVideo::BatchDetection(Mat image) {
	aSSVideoCapture->writeImageBatch(image);
	if (aSSVideoCapture->getCountBatch() % 10 == 0) {
		aSSFaceDetect->SetFileImage(aSSVideoCapture->GetNameFileImage());
		int count = aSSFaceDetect->ProccessDetectBatch();
	}
}

void ASSCentralProcessingVideo::DetectFaces(Mat image) {
	
	RefreshData();
	
	switch (optionProcess)
	{
	case 1:
		SingleDetection(image);
		//cout << "SINGLE DETECTION" << endl;
		break;
	case 2:
		BatchDetection(image);
		//cout << "BATCH DETECTION" << endl;
		break;
	default:
		break;
	}

	flagNextFrame = false;
}

void ASSCentralProcessingVideo::RunProcessVideo() {
	
	auto frame_input
		= aSSVideoCapture->observableImage.map([](Mat p) {
		return p;
	});

	auto subscription = frame_input.subscribe([this](Mat p) {
		cv::resize(p, p, cv::Size(), 0.5, 0.5, INTER_LINEAR_EXACT);

		
		if (!flagNextFrame) {
			flagNextFrame = true;

			std::thread squ(&ASSCentralProcessingVideo::DetectFaces, this, p);
			squ.detach();

		}

		aSSVideoCapture->countFrame += 1;
		
		frameOut.on_next(p);


	});

	SetTimeLogs();
	
	aSSVideoCapture->processVideo();

	subscription.unsubscribe();

}

void ASSCentralProcessingVideo::SetDirectory(string directory) {

	_directory = directory;
	manageLogHardware->SetNameDirectory(_directory);
	manageDetailProcessor->SetNameDirectory(_directory);
	aSSFaceDetect->SetDirectory(_directory);
}

void ASSCentralProcessingVideo::SetOptionDetection(int option) {

	optionProcess = option;

}

void ASSCentralProcessingVideo::SaveDetailsHardware() {
	string date = GetTimeInitProcess();
	manageDetailProcessor->WriteFile(date);
	string cpuDetail = aSSCheckHardware->SysInfoCpu();
	
	if (aSSCuda->isExistCuda()) {
		cout << "CUDA EXISTS" << endl;
	}
	string gpuDetail = aSSCuda->GetDescripton();
	
	string detailDisk = aSSCheckHardware->SysInfoDisk();
	string sdk = format->FormatString("--------------------------------------\n");
	sdk += format->FormatString("INNOVATRICS LIBRARY SDK: %s\n", aSSFaceDetect->Version());
	
	string logData = cpuDetail + "\n" + gpuDetail + "\n" + detailDisk + "\n" + sdk + "\n";
	manageDetailProcessor->WriteFile(logData);
}

//void ASSCentralProcessingVideo::ObserverTemplate() {
//
//	auto template_input
//		= aSSFaceDetect->observableTemplate.map([](char* m) {
//		return m;
//	});
//
//	auto subscription = template_input.subscribe([this](char* m) {
//		
//		templateOut.on_next(m);
//		
//	});
//
//}
#include "ASSFaceDetect.h"


ASSFaceDetect::ASSFaceDetect()
{
	manageFileError->SetNameFile(FILE_ERROR);
	manageLogDetailImage->SetNameFile(LOG_DETECTION_SIMPLE);
	manageLogBachDetection->SetNameFile(LOG_DETECTION_BATCH);
	ObserverError();
}

ASSFaceDetect::~ASSFaceDetect()
{
	Terminate();
}

void ASSFaceDetect::ObserverError()
{
	auto faceError = aSFaceError->observableError.map([](ASSFaceEither* faceEither) {
		return faceEither;
	});

	auto subscriptionError = faceError.subscribe([this](ASSFaceEither* faceEither) {

		if (faceEither->GetCode() == ASSFaceError::ErrorFace::out ||
			faceEither->GetCode() == ASSFaceError::ErrorFace::log)
		{
			std::time_t result = std::time(nullptr);
			string time = std::asctime(std::localtime(&result));
			string content = time + ": " + faceEither->GetLabel() + "\n";

			manageFileError->WriteFile(content);

		}

		if (faceEither->GetCode() == ASSFaceError::ErrorFace::window)
		{
			std::thread gi(&ASSFaceDetect::SendError, this, faceEither->GetLabel());
			gi.detach();
			
		}
	});
}

void ASSFaceDetect::SendError(string error) {
	shootError.on_next(error);
}


string ASSFaceDetect::getJsonConfig() {
	Json::Value jsonMap;
	std::map<std::string, std::int16_t> params;
	params.insert(std::pair<std::string, std::int16_t>(MAXFACES, _maxDetect));
	params.insert(std::pair<std::string, std::int16_t>(MINEYE, minEyeDistance));
	params.insert(std::pair<std::string, std::int16_t>(MAXEYE, maxEyeDistance));
	params.insert(std::pair<std::string, std::int16_t>(ACCURACY, _accuracy));
	std::map<std::string, std::int16_t>::const_iterator it = params.begin(),
		end = params.end();
	for (; it != end; ++it) {
		jsonMap[it->first] = it->second;

	}
	Json::Value root;
	root["config"] = "detect_config";
	root["params"] = jsonMap;

	Json::StyledWriter writer;
	string output = writer.write(root);
	return output;
}

void ASSFaceDetect::setJsonConfig() {
	string jsonString = GetConfig(_fileConfiguration);
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(jsonString, root);
	if (!parsingSuccessful)
	{
		cout << "Error parsing the string" << endl;
		return;
	}

	const Json::Value params = root["params"];
	for (Json::Value::const_iterator it = params.begin();
		it != params.end(); ++it) {
		
		if (it.key().asString() == MAXFACES) {
			_maxDetect = it->asInt();
		}
		else if (it.key().asString() == MINEYE) {
			minEyeDistance = it->asInt();
		}
		else if (it.key().asString() == MAXEYE) {
			maxEyeDistance = it->asInt();
		}
		else if (it.key().asString() == ACCURACY) {
			_accuracy = it->asInt();
		}

	}

}
string ASSFaceDetect::Version() {
	int major;
	int minor;
	int revision;

	int error = IFACE_GetVersionInfo(&major, &minor, &revision);

	if (error == IFACE_OK)
	{
		stringstream ss;
		ss << major << "." << minor << "." << revision;
		return ss.str();
	}
	else
	{
		return "";
	}
}

void ASSFaceDetect::Init() {
	int errorCode;

	errorCode = IFACE_Init();
	aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);


}

//void ASSFaceDetect::CreateHandlerParams() {
//	int errorCode;
//	errorCode = IFACE_CreateFaceHandler(&faceHandler);
//	aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
//}

void ASSFaceDetect::SetMaxDetect(int max) {
	_maxDetect = max;
}

//void ASSFaceDetect::SetHandlerParams() {
//	int errorCode;
//	errorCode = IFACE_SetParam(faceHandler, IFACE_PARAMETER_FACEDET_SPEED_ACCURACY_MODE,
//		IFACE_FACEDET_SPEED_ACCURACY_MODE_DEFAULT);
//	aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
//}

void ASSFaceDetect::Terminate() {
	int errorCode = IFACE_Terminate();
	aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
}

//void ASSFaceDetect::Start() {
//
//	CreateHandlerParams();
//
//	SetHandlerParams();
//
//}

void ASSFaceDetect::resetCountBatch() {
	_countBatch = 0;
}

void ASSFaceDetect::SetFileImage(string strFileImage) {
	_strFileImage = strFileImage;
}

//void ASSFaceDetect::LoadImageFromMemory(const char* imgData, int size) {
//
//	int errorCode, lenght,  width, height;
//
//	try
//	{
//		std::cout << "IMAGE SIZE IFACE: " << imageSize << std::endl;
//
//		const char* imgBuffer = reinterpret_cast<const char*>(rawImageFrame);
//		std::cout << "PASE CAST " << std::endl;
//		if (imgBuffer != NULL)
//		{
//			std::cout << "CAST SIZE " << (unsigned)strlen(imgBuffer) << std::endl;
//			errorCode = IFACE_LoadImageFromMemory(imgBuffer, imageSize, &width,
//				&height, &lenght, rawImageData);
//			if (errorCode != IFACE_OK) {
//				aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
//			}
//
//		}
//		else
//		{
//			std::cout << "PASE CAST NULL " << std::endl;
//		}
//
//
//	}
//	catch (const std::exception& ex)
//	{
//		std::cout << ex.what() << std::endl;
//	}
//}
//
//void ASSFaceDetect::SaveImageToMemory(unsigned char* rawImage, int rawWidth, int rawHeight) {
//
//	int errorCode;
//
//	try
//	{
//		int length = (unsigned)strlen((char*)rawImage);
//		rawImageFrame = new unsigned char[length];
//		errorCode = IFACE_SaveImageToMemory(rawImage, rawWidth, rawHeight,
//			3, IFACE_IMAGE_SAVE_TYPE_JPG, &imageSize, rawImageFrame);
//
//		std::cout << rawImageFrame << std::endl;
//
//		if (errorCode != IFACE_OK) {
//			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
//		}
//
//	}
//	catch (const std::exception& ex)
//	{
//		std::cout << ex.what() << std::endl;
//	}
//}

int ASSFaceDetect::ProccessDetectBatch() {
	int errorCode, countDetect = 0;
	void* facesDetect[BATCH_SIZE];
	void* faceHandler;
	

	errorCode = IFACE_CreateFaceHandler(&faceHandler);
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
	}

	for (int i = 0; i < BATCH_SIZE; i++)
	{

		errorCode = IFACE_CreateFace(&(facesDetect[i]));
		if (errorCode != IFACE_OK) {
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}

	}

	for (int i = 0; i < BATCH_SIZE; i++)
	{
		int lenght, widthFace, heightFace;

		_countBatch++;
		string fileImage = _directory + "/" + to_string(_countBatch) + _strFileImage;
		
		errorCode = IFACE_LoadImage(fileImage.c_str(), &widthFace, &heightFace, &lenght, NULL);
		if (errorCode != IFACE_OK)
		{
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
		}

		unsigned char* rawImage = new unsigned char[lenght];
		errorCode = IFACE_LoadImage(fileImage.c_str(), &widthFace,
			&heightFace, &lenght, rawImage);
		if (errorCode != IFACE_OK)
		{
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
		}

		void* faceTemp;
		errorCode = IFACE_CreateFace(&(faceTemp));
		if (errorCode != IFACE_OK) {
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}
		int detectedFaces = _maxDetect;

		errorCode = IFACE_DetectFaces(rawImage, widthFace, heightFace,
			minEyeDistance, maxEyeDistance, faceHandler, &detectedFaces, &faceTemp);
		delete rawImage;
		if (errorCode != IFACE_OK) {
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}


		if (detectedFaces != EMPTY_FACE)
		{
			errorCode = IFACE_CloneEntity(faceTemp, facesDetect[countDetect]);

			if (errorCode != IFACE_OK) {
				aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
			}
			countDetect++;
		}
		errorCode = IFACE_ReleaseEntity(faceTemp);
		if (errorCode != IFACE_OK) {
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}

	}

	GetModelBatch(countDetect, facesDetect);

	if (_countBatch == _quantityBatch)
	{
		_countBatch = 0;
	}

	for (int i = 0; i < BATCH_SIZE; i++)
	{
		errorCode = IFACE_ReleaseEntity(facesDetect[i]);
		if (errorCode != IFACE_OK) {
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}

	}
	errorCode = IFACE_ReleaseEntity(faceHandler);
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
	}

	return countDetect;


}

int ASSFaceDetect::ProccessDetectSingle() {
	int lenght, width, height, errorCode, templates;

	errorCode = IFACE_LoadImage(_strFileImage.c_str(), &width, &height, &lenght, NULL);
	if (errorCode == IFACE_OK)
	{
		unsigned char* rawImage = new unsigned char[lenght];
		errorCode = IFACE_LoadImage(_strFileImage.c_str(), &width,
			&height, &lenght, rawImage);
		if (errorCode != IFACE_OK)
		{
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
		}
		else
		{
			templates = GetModel(rawImage, width, height);
		}
		delete rawImage;
	}
	else {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
	}

	return templates;
}

void ASSFaceDetect::SetAccuracy(int accuracy) {
	_accuracy = accuracy;
}

void ASSFaceDetect::GetModelBatch(int countDetect, void* facesDetect[BATCH_SIZE]) {
	int errorCode;
	int templateBatchDataSize;
	Lot* lot = new Lot();
	countFaceDetect = countDetect;

	char** batchTemplates = new char*[BATCH_SIZE];
	void* faceHandler;

	errorCode = IFACE_CreateFaceHandler(&faceHandler);
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
	}

	errorCode = IFACE_CreateTemplateBatch(faceHandler, BATCH_SIZE, facesDetect,
		&templateBatchDataSize, NULL);
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
	}


	for (int i = 0; i < BATCH_SIZE; ++i)
	{

		batchTemplates[i] = new char[templateBatchDataSize];
	}

	measurement->Start();
	errorCode = IFACE_CreateTemplateBatch(faceHandler, BATCH_SIZE, facesDetect,
		&templateBatchDataSize, batchTemplates);
	measurement->End();
	lot->SetTimeOfTemplate(measurement->ElapseTime());

	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
	}
	for (int i = 0; i < countDetect; i++)
	{
		ASSModel* model = new ASSModel();
		model->SetTemplate(batchTemplates[i]);
		model->SetSize(templateBatchDataSize);

		templateOut.on_next(model);
	}

	for (int i = 0; i < BATCH_SIZE; ++i)
	{

		delete batchTemplates[i];
	}
	errorCode = IFACE_ReleaseEntity(faceHandler);
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
	}
	lot->SetNumberOfFaces(countDetect);
	if (countDetect != 0)
	{
		std::thread(&ASSFaceDetect::SaveDataBatchDetect, this,
			lot).detach();

	}

}


void ASSFaceDetect::SaveDataBatchDetect(Lot* detailLot) {
	std::stringstream concat;
	concat << detailLot->GetNumberOfFaces() << "," << detailLot->GetTimeOfTemplate() << endl;
	std::string content = concat.str();
	
	/*string content = to_string(detailLot->GetNumberOfFaces()) + "," +
		to_string(detailLot->GetTimeOfTemplate()) + "\n";*/
	manageLogBachDetection->WriteFile(content);
}


int ASSFaceDetect::GetModel(unsigned char* rawImage, int width, int height) {
	int detectedFaces = _maxDetect;
	int errorCode;
	int result = 0;
	void* faceTemp;
	void* faceHandler;
	Image* detailsOfMeasure = new Image();

	errorCode = IFACE_CreateFaceHandler(&faceHandler);
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
	}

	errorCode = IFACE_CreateFace(&(faceTemp));
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
	}
	measurement->Start();
	errorCode = IFACE_DetectFaces(rawImage, width, height,
		minEyeDistance, maxEyeDistance, faceHandler, &detectedFaces, &faceTemp);
	measurement->End();
	detailsOfMeasure->SetTimeOfDetection(measurement->ElapseTime());

	if (errorCode == IFACE_OK) {
		if (detectedFaces != EMPTY_FACE)
		{
			measurement->Start();
			int quality = CreateTemplate(faceTemp);
			measurement->End();
			detailsOfMeasure->SetTimeOfTemplate(measurement->ElapseTime());
			detailsOfMeasure->SetQualityTemplate(quality);
		}
	}
	else {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
	}
	
	errorCode = IFACE_ReleaseEntity(faceTemp);
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
	}
	errorCode = IFACE_ReleaseEntity(faceHandler);
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
	}
	detailsOfMeasure->SetNumberOfFaces(detectedFaces);
	if (detectedFaces != 0) {
		std::thread(&ASSFaceDetect::SaveDataMeasure, this,
			detailsOfMeasure).detach();

	}

	return detectedFaces;
}

void ASSFaceDetect::SaveDataMeasure(Image* detailImage) {
	std::stringstream concat;
	concat << detailImage->GetNumberOfFaces() << "," << detailImage->GetTimeOfDetection() 
		<< "," << detailImage->GetTimeOfTemplate() << "," << detailImage->GetQualityTemplate() << endl;
	std::string content = concat.str();
	/*string content = to_string(detailImage->GetNumberOfFaces()) + "," +
		to_string(detailImage->GetTimeOfDetection()) + "," +
		to_string(detailImage->GetTimeOfTemplate()) + "," +
		to_string(detailImage->GetQualityTemplate()) + "\n";*/
	//cout << "SAVE DETEC SIMPLE: " << content << endl;
	manageLogDetailImage->WriteFile(content);
}

void ASSFaceDetect::InitDateLogs(string date) {
	manageFileError->WriteFile(date);
	manageLogDetailImage->WriteFile(date);
	manageLogBachDetection->WriteFile(date);
}

int ASSFaceDetect::CreateTemplate(void* face) {
	int errorCode;
	int templateSize;
	void* faceHandler;
	int majorVersion0, minorVersion0, majorVersion1, minorVersion1, quality0, quality1;

	errorCode = IFACE_CreateFaceHandler(&faceHandler);
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
	}

	errorCode = IFACE_CreateTemplate(face, faceHandler, 0, &templateSize, NULL);
	if (errorCode == IFACE_OK) {
		char* templateData = new char[templateSize];
		errorCode = IFACE_CreateTemplate(face, faceHandler, 0,
			&templateSize, templateData);
		if (errorCode != IFACE_OK) {
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}
		else
		{
			ASSModel* model = new ASSModel();
			model->SetTemplate(templateData);
			model->SetSize(templateSize);

			templateOut.on_next(model);
			
			errorCode = IFACE_GetTemplateInfo(faceHandler, templateData, &majorVersion0, &minorVersion0, &quality0);
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}
		delete[] templateData;
	}
	else {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
	}
	errorCode = IFACE_ReleaseEntity(faceHandler);
	aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
	return quality0;
}

void ASSFaceDetect::Release() {
	/*int errorCode;
	errorCode = IFACE_ReleaseEntity(faceHandler);
	aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);*/
	delete[] rawImageData;


}

void ASSFaceDetect::SetminEyeDistance(int min) {
	minEyeDistance = min;
}

void ASSFaceDetect::SetmaxEyeDistance(int max) {
	maxEyeDistance = max;
}

void ASSFaceDetect::SetFileConfiguration(string file) {
	_fileConfiguration = file;
}

void ASSFaceDetect::SetDirectory(string directory) {
	_directory = directory;
	manageFileError->SetNameDirectory(_directory);
	manageLogDetailImage->SetNameDirectory(_directory);
	manageLogBachDetection->SetNameDirectory(_directory);
}

string ASSFaceDetect::GetConfig(string nameFile) {
	string config;
	ifstream inconfig;
	inconfig.open(nameFile);
	if (inconfig.good()) {
		stringstream strStream;
		strStream << inconfig.rdbuf();
		config = strStream.str();
		inconfig.close();
	}
	else {
		string msg = "File configuration not found";
		aSFaceError->CheckError(ASSFACE_ERROR_FILE, msg, aSFaceError->ErrorFace::out);
		
	}
	return config;
}
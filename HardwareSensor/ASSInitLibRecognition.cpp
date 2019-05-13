#include "ASSInitLibRecognition.h"

ASSInitLibRecognition::ASSInitLibRecognition()
{
}

ASSInitLibRecognition::~ASSInitLibRecognition()
{
}

void ASSInitLibRecognition::InitLib() {
	int errorCode;

	errorCode = IFACE_Init();
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
	}
	else {
		cout << "License OK" << endl;
	}

}

void ASSInitLibRecognition::SetParams(bool cuda) {
	int errorCode;
	if (!cuda || !InitCuda())
	{
		errorCode = IFACE_SetParam(IFACE_GLOBAL_PARAMETERS,
			IFACE_PARAMETER_GLOBAL_THREAD_NUM, IFACE_GLOBAL_THREAD_NUM_DEFAULT);
		if (errorCode != IFACE_OK) {
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}
		else {
			cout << "Params OK" << endl;
		}
	}
	
}

void ASSInitLibRecognition::SetConfigurationIdentify(string nameFile)
{
	int errorCode;
	string stringOfConfiguration = GetConfiguration(nameFile);
	//cout << "Configuration Identify: " << stringOfConfiguration << endl;
	if (!stringOfConfiguration.empty())
	{
		errorCode = faceid_init_library(stringOfConfiguration.c_str());
		if (errorCode != IFACE_OK) {
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}
	}
}

void ASSInitLibRecognition::InitDatabase()
{
	connectToDatabase("type=memory");
	clearDatabase();
}

string ASSInitLibRecognition::GetConfiguration(string nameFile)
{
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


bool ASSInitLibRecognition::InitCuda() {
	int errorCode;
	errorCode = IFACE_SetParam(nullptr,
		IFACE_PARAMETER_GLOBAL_GPU_ENABLED, "true");
	if (errorCode == IFACE_OK) {
		errorCode = IFACE_SetParam(nullptr,
			IFACE_PARAMETER_GLOBAL_GPU_DEVICE_ID, "0");
		if (errorCode != IFACE_OK) {
			char errorMessage[256];
			IFACE_GetErrorMessage(errorCode, 256, errorMessage);
			string str(errorMessage);
			str = "CUDA not enabled: " + str;
			aSFaceError->CheckError(errorCode, str, aSFaceError->ErrorFace::log);
			return false;
		}
		else {
			cout << "CUDA successfully enabled " << endl;
			return true;
		}
	}
	else {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		return false;
	}


}
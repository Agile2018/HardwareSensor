#include "ASSFaceIdentify.h"

ASSFaceIdentify::ASSFaceIdentify()
{
	manageFileError->SetNameFile(FILE_ERROR_IDENTIFY);
	manageLogIdentify->SetNameFile(LOG_IDENTIFY);
	ObserverError();
}

ASSFaceIdentify::~ASSFaceIdentify()
{
}

void ASSFaceIdentify::ObserverError() {
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
			SendError(faceEither->GetLabel());
		

		}
	});

}

void ASSFaceIdentify::SendError(string error) {
	shootError.on_next(error);
}

void ASSFaceIdentify::SetConfiguration(string nameFile)
{
	int errorCode;
	stringOfConfiguration = GetConfiguration(nameFile);
	//cout << "Configuration Identify: " << stringOfConfiguration << endl;
	if (!stringOfConfiguration.empty())
	{
		errorCode = faceid_init_library(stringOfConfiguration.c_str());
		if (errorCode != IFACE_OK) {
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}
	}
}

string ASSFaceIdentify::GetConfiguration(string nameFile)
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

void ASSFaceIdentify::InitDatabase()
{
	connectToDatabase("type=memory");
	clearDatabase();
}

void ASSFaceIdentify::Identify(ASSModel* modelImage)
{
	int userID = 0;
	int score = 0;
	int result = 0;
	int errorCode;
	Identification* identification = new Identification();

	const unsigned char* templateData = reinterpret_cast<const unsigned char*>(modelImage->GetTemplate());
	measurement->Start();
	errorCode = identify(templateData, modelImage->GetSize(), &userID, &score);
	measurement->End();
	identification->SetTimeOfIdentify(measurement->ElapseTime());
	identification->SetScore(score);
	cout << "identify result " << errorCode << ", userID " << userID << ",score " << score << endl;
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
	}
	else 
	{
		std::thread(&ASSFaceIdentify::Enroll, this,
			templateData, modelImage->GetSize(), userID, identification).detach();
		//Enroll(templateData, modelImage->GetSize(), userID);

	}
	
}

void ASSFaceIdentify::Enroll(const unsigned char* templateData, 
	int modelSize, int userId, Identification* identification)
{
	int errorCode;
	int userID = userId;
	measurement->Start();
	if (userID == 0)
	{
		errorCode = addUserToDatabase(templateData, modelSize, &userID);
		if (errorCode != IFACE_OK) {
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}
		cout << "addUserToDatabase result " << errorCode << ", userId " << userID << endl;

	}
	else
	{
		errorCode = addTemplateToUserInDatabase(templateData, modelSize, userID);
		if (errorCode != IFACE_OK) {
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}
		cout << "addTemplateToUserInDatabase result " << errorCode << ", userId " << userID << endl;
	}
	measurement->End();
	identification->SetTimeOfEnroll(measurement->ElapseTime());
	identification->SetUserId(userID);
	std::thread(&ASSFaceIdentify::SaveDataIdentify, this,
		identification).detach();
}

void ASSFaceIdentify::SaveDataIdentify(Identification* identification) {
	std::stringstream dataForSave;
	dataForSave << identification->GetUserId() << "," 
		<< identification->GetScore() << "," << identification->GetTimeOfIdentify() 
		<< "," << identification->GetTimeOfEnroll() << endl;
	std::string content = dataForSave.str();
	manageLogIdentify->WriteFile(content);

}

int ASSFaceIdentify::UserEnrolled() {
	int quantity = 0;
	getNumberOfUsers(&quantity);

	return quantity;

}

void ASSFaceIdentify::SetDirectory(string directory) {
	manageFileError->SetNameDirectory(directory);
	manageLogIdentify->SetNameDirectory(directory);
}

void ASSFaceIdentify::InitDateLog(string date) {
	manageLogIdentify->WriteFile(date);
	
}
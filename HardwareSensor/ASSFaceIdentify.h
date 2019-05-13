#ifndef ASSFaceIdentify_h
#define ASSFaceIdentify_h

#include <json\json.h>
#include <sstream> 
#include <iostream> 
#include <fstream> 
#include "ASSFaceError.h"
#include "faceidkitlib.h"
#include "ASSModel.h"
#include "ManageFile.h"
#include "Identification.h"
#include "Measurement.h"

const string FILE_ERROR_IDENTIFY = "error.txt";
const string LOG_IDENTIFY = "log_identify.txt";
using namespace std;

class ASSFaceIdentify
{
public:
	ASSFaceIdentify();
	~ASSFaceIdentify();
	void SetConfiguration(string nameFile);
	void SetDirectory(string directory);
	void InitDatabase();
	void Identify(ASSModel* modelImage);
	int UserEnrolled();
	void InitDateLog(string date);
	Rx::subject<string> errorFace;
	Rx::observable<string> observableError = errorFace.get_observable();
private:
	Measurement* measurement = new Measurement();
	ManageFile* manageFileError = new ManageFile();
	ManageFile* manageLogIdentify = new ManageFile();
	ASSFaceError* aSFaceError = new ASSFaceError();
	Rx::subscriber<string> shootError = errorFace.get_subscriber();
	string stringOfConfiguration;
	string GetConfiguration(string nameFile);
	void Enroll(const unsigned char* templateData, 
		int modelSize, int userId, Identification* identification);
	void ObserverError();
	void SendError(string error);
	void SaveDataIdentify(Identification* identification);
};


#endif // !ASSFaceIdentify_h


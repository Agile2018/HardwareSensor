#ifndef ASSFaceDetect_h
#define ASSFaceDetect_h

#include "ASSFaceError.h"
#include "ManageFile.h"
#include "Measurement.h"
#include "Image.h"
#include "Lot.h"
#include <map>
#include <json\json.h>
#include <sstream> 
#include <iostream> 
#include <fstream> 

const string FILE_ERROR = "error.txt";
const string LOG_DETECTION_SIMPLE = "log_detection_simple.txt";
const string LOG_DETECTION_BATCH = "log_detection_batch.txt";

using namespace std;
namespace Rx {
	using namespace rxcpp;
	using namespace rxcpp::subjects;
	using namespace rxcpp::operators;
	using namespace rxcpp::util;
}

class ASSFaceDetect
{
public:
	ASSFaceError* aSFaceError = new ASSFaceError();
	ASSFaceDetect();
	~ASSFaceDetect();
	string Version();
	void Terminate();
	void SetMaxDetect(int max);
	//void Start();	
	int ProccessDetectSingle();
	void SetFileImage(string strFileImage);
	//void SaveImageToMemory(unsigned char* rawImage, int rawWidth, int rawHeight);
	void Release();
	int ProccessDetectBatch();
	void SetminEyeDistance(int min);
	void SetmaxEyeDistance(int max);
	void SetAccuracy(int accuracy);
	//void LoadImageFromMemory(const char* imgData, int size);
	string getJsonConfig();
	int countFaceDetect;
	void resetCountBatch();
	void SetFileConfiguration(string file);
	unsigned char* rawImageData;
	void setJsonConfig();
	void SendError(string error);
	void SetDirectory(string directory);
	Rx::subject<string> errorFace;
	Rx::observable<string> observableError = errorFace.get_observable();
	/*Rx::subject<char*> templateImage;
	Rx::observable<char*> observableTemplate = templateImage.get_observable();*/
private:
	ManageFile* manageFileError = new ManageFile();
	ManageFile* manageLogDetailImage = new ManageFile();
	ManageFile* manageLogBachDetection = new ManageFile();
	Measurement* measurement = new Measurement();
	string _directory;
	void SaveDataMeasure(Image* detailImage);
	void SaveDataBatchDetect(Lot* detailLot);
	void ObserverError();
	string GetConfig(string nameFile);
	int _maxDetect = MAX_DETECT;
	Rx::subscriber<string> shootError = errorFace.get_subscriber();
	//Rx::subscriber<char*> templateOut = templateImage.get_subscriber();
	int GetModel(unsigned char* rawImage, int width, int height);
	int minEyeDistance = MIN_EYE_DISTANCE;
	int maxEyeDistance = MAX_EYE_DISTANCE;
	string _strFileImage;
	string _fileConfiguration;
	int _accuracy = ACCURASY;
	int  imageSize;
	unsigned char* rawImageFrame;
	int _quantityBatch = 30;
	int _countBatch = 0;
	int countBatch = 0;
	//void* faceHandler;
	void GetModelBatch(int countDetect, void* facesDetect[BATCH_SIZE]);
	void Init();
	/*void CreateHandlerParams();
	void SetHandlerParams();*/
	int CreateTemplate(void* face);
	const string MAXFACES = "maxfaces";
	const string MINEYE = "mineye";
	const string MAXEYE = "maxeye";
	const string ACCURACY = "accuracy";
};

#endif

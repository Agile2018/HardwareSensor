#ifndef ASSVideoCapture_h
#define ASSVideoCapture_h

#include <opencv2/core.hpp>
#include <opencv2/core/opengl.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
#include "ASSVideoConfig.h"
#include "ASSFaceCodes.h"
#include <stdlib.h>
#include "rx.hpp"
#include <windows.h>
#include <cmath>

using namespace cv;


namespace Rx {
	using namespace rxcpp;
	using namespace rxcpp::subjects;
	using namespace rxcpp::operators;
	using namespace rxcpp::util;
}

typedef signed char sbyte;
typedef unsigned char byte;

class ASSVideoCapture
{
public:
	ASSVideoCapture(ASSVideoConfig* config);
	~ASSVideoCapture();
	void processVideo();
	void writeImage(Mat frame);
	void writeImageBatch(Mat frame);
	string GetNameWindow();
	string GetNameFileImage();
	Mat readImage(string fileName);
	float countFrame = 0;
	float lapseFrame = 8;	
	void setQuantityBach(int value);
	int getCountBatch();
	void resetCountBatch();
	int getFps();
	Rx::subject<Mat> frameImage;
	Rx::observable<Mat> observableImage = frameImage.get_observable();
private:
	Rx::subscriber<Mat> frameout = frameImage.get_subscriber();
	void sendFrame(Mat inputImg);
	Mat _frame;
	string nameFileImageTemp;
	bool flagCapture = true;
	int _deviceId = -1;
	int fps_camera = 0;
	int _quantityBatch = 30;
	int _countBatch = 0;
	ASSVideoConfig* _asvideoConfig;
	bool buildPathVideo();
	bool isPositiveInteger(string &device);
	bool searchProtocol(string &device);
	void setFps(VideoCapture cap);
	string buildUrl(string device);
	string _urlVideo;

};


#endif
#include "ASSVideoCapture.h"


ASSVideoCapture::ASSVideoCapture(ASSVideoConfig* config)
{
	_asvideoConfig = config;
	

}

ASSVideoCapture::~ASSVideoCapture()
{
	
}

string ASSVideoCapture::GetNameFileImage() {
	return nameFileImageTemp;
}

string ASSVideoCapture::GetNameWindow() {
	return _asvideoConfig->getNameWindow();
}

int ASSVideoCapture::getFps() {
	return fps_camera;
}

void ASSVideoCapture::setFps(VideoCapture cap) {
	if (_asvideoConfig->getFps().empty()) {
		fps_camera = (int)(cap.get(CAP_PROP_FPS));
		if (fps_camera < 0) {
			cap.set(CAP_PROP_FPS, FPS);
			fps_camera = FPS;
		}
	}
	else {
		string value = _asvideoConfig->getFps();
		fps_camera = atoi(value.c_str());
	}
}

void ASSVideoCapture::processVideo() {
	
	if (buildPathVideo()) {
		VideoCapture capture;
		if (_deviceId != -1) {
			capture.open(_deviceId);
		}
		else {
			capture.open(_urlVideo);
		}

		if (!capture.isOpened()) {
			cout << "Unable to open video file: " << _urlVideo << endl;
			return;
		}
		setFps(capture);
		while (flagCapture) {
			if (!capture.read(_frame)) {
				cout << "Unable to read next frame." << endl;
				cout << "Exiting..." << endl;
				return;
			}
			else {
				sendFrame(_frame);
				if (waitKey(1000 / fps_camera) >= 0) {
					flagCapture = false;
				}
			}
		}
		capture.release();
	}

}

Mat ASSVideoCapture::readImage(string fileName) {
	return imread(fileName, IMREAD_COLOR);
}

int ASSVideoCapture::getCountBatch() {
	return _countBatch;
}
void ASSVideoCapture::resetCountBatch() {
	_countBatch = 0;
}

void ASSVideoCapture::writeImageBatch(Mat frame) {

	_countBatch++;
	string fileTemp = _asvideoConfig->getNameWindow() + "/" + to_string(_countBatch) + nameFileImageTemp;
	imwrite(fileTemp, frame);
	if (_countBatch == _quantityBatch)
	{
		_countBatch = 0;
	}

}

void ASSVideoCapture::writeImage(Mat frame) {
	string path = _asvideoConfig->getNameWindow() + "/" + nameFileImageTemp;
	imwrite(path, frame);
}

void ASSVideoCapture::setQuantityBach(int value) {
	_quantityBatch = value;
}

void ASSVideoCapture::sendFrame(Mat inputImg) {

	frameout.on_next(inputImg);
}

bool ASSVideoCapture::buildPathVideo() {
	string path = _asvideoConfig->getPath();
	nameFileImageTemp = _asvideoConfig->getImageTemp();
	if (!path.empty()) {
		if (isPositiveInteger(path)) {
			_deviceId = stoi(path);
		}
		else if (searchProtocol(path)) {
			_urlVideo = buildUrl(path);
		}
		else {
			_urlVideo = path;
		}
		return true;
	}
	else {
		return false;
	}
}

bool ASSVideoCapture::isPositiveInteger(string &device) {
	return !device.empty() &&
		(std::count_if(device.begin(), device.end(), std::isdigit) == device.size());
}


bool ASSVideoCapture::searchProtocol(string &device) {
	string http = "http://";
	string rtsp = "rtsp://";

	if (device.find(http) == string::npos && device.find(rtsp) == string::npos) {
				
		return false;
	}
	else {
		return true;
	}
}

string ASSVideoCapture::buildUrl(string device) {
	string url;
	string protocol = device.substr(0, 7);
	
	device.replace(0, 7, "");
	if (protocol == "http://")
	{
		url = protocol + _asvideoConfig->getUser() + ":" +
			_asvideoConfig->getPassword() + "@" +
			device + "/axis-cgi/mjpg/video.cgi?resolution=" +
			_asvideoConfig->getResolution() + "&req_fps=30&.mjpg";

	}
	if (protocol == "rtsp://")
	{
		url = protocol + _asvideoConfig->getUser() + ":" +
			_asvideoConfig->getPassword() + "@" +
			device;

	}

	
	return url;
}

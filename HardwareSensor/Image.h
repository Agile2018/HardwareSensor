#ifndef Image_h
#define Image_h

class Image
{
public:
	Image();
	~Image();
	void SetTimeOfDetection(double time);
	void SetNumberOfFaces(int faces);
	void SetTimeOfTemplate(double time);
	double GetTimeOfDetection();
	int GetNumberOfFaces();
	double GetTimeOfTemplate();
	void SetQualityTemplate(int quality);
	int GetQualityTemplate();
private:
	double _timeOfDetection;
	int _numberOfFaces;
	double _timeOfTemplate;
	int _qualityTemplate;
};


#endif // !Image_h


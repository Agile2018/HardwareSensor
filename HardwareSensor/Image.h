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

private:
	double _timeOfDetection;
	int _numberOfFaces;
	double _timeOfTemplate;

};


#endif // !Image_h


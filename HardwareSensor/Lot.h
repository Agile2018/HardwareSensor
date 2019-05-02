#ifndef Lot_h
#define Lot_h

class Lot
{
public:
	Lot();
	~Lot();
	void SetNumberOfFaces(int faces);
	void SetTimeOfTemplate(double time);
	int GetNumberOfFaces();
	double GetTimeOfTemplate();

private:
	double _timeOfTemplate;
	int _numberOfFaces;
};

#endif // !Lot_h


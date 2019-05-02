#ifndef Measurement_h
#define Measurement_h

class Measurement
{
public:
	//Measurement();
	//~Measurement();
	virtual void Start() {};
	virtual double End() = 0;
protected:
	double _initCount;
	double _endCount;
};

//Measurement::Measurement()
//{
//}
//
//Measurement::~Measurement()
//{
//}
#endif // !Measurement_h


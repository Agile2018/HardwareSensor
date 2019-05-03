#ifndef Measurement_h
#define Measurement_h
#include <chrono>

using namespace std;

class Measurement
{
public:
	Measurement();
	~Measurement();
	void Start();
	void End();
	double ElapseTime();
private:
	
	std::chrono::steady_clock::time_point startCount;
	std::chrono::steady_clock::time_point endCount;
};

#endif // !Measurement_h


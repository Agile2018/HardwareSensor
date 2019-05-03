#ifndef Processor_h
#define Processor_h
#include <iostream>
#include <stdlib.h>
using namespace std;
class Processor
{
public:
	Processor();
	~Processor();
	void SetConsumption(int consumption);
	int GetConsumption();
	void SetDescription(string description);
	string GetDescription();
private:
	int _consumption;
	string _description;
};

#endif // !Processor_h


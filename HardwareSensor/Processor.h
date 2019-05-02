#ifndef Processor_h
#define Processor_h

class Processor
{
public:
	Processor();
	~Processor();
	void SetConsumption(int consumption);
	int GetConsumption();
private:
	int _consumption;
};

#endif // !Processor_h


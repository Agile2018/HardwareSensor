#ifndef Memory_h
#define Memory_h

class Memory
{
public:
	Memory();
	~Memory();
	void SetSizeTotalMemory(long quantity);
	void SetMyConsumption(long quantity);
	long GetSizeTotalMemory();
	long GetMyConsumption();

private:
	long _sizeTotalMemory;
	long _myConsumption;
};


#endif // !Memory_h


#ifndef Disk_h
#define Disk_h

class Disk
{
public:
	Disk();
	~Disk();
	void SetUseOfDisk(long size);
	long GetUseOfDisk();
private:
	long _useOfDisk;
};

#endif // !Disk_h


#ifndef ManageFile_h
#define ManageFile_h

#include <iostream>
#include <fstream> 
#include <stdlib.h>
#include <direct.h>

using namespace std;

class ManageFile
{
public:
	ManageFile();
	~ManageFile();
	void SetNameDirectory(string name);
	void SetNameFile(string name);
	bool WriteFile(string content);
	bool DeleteFile();
	bool CreateDirectory();
private:
	string _nameDirectory;
	string _nameFile;
};

#endif // !ManageFile_h


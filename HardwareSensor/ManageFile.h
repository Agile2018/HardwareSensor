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
	void WriteFile(string content);
	bool DeleteFileLog();
	void CreateDirectoryVideo();
private:
	string _nameDirectory;
	string _nameFile;
};

#endif // !ManageFile_h


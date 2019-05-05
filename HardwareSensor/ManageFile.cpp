#include "ManageFile.h"

ManageFile::ManageFile()
{
}

ManageFile::~ManageFile()
{
}

void ManageFile::SetNameDirectory(string name)
{
	_nameDirectory = name;
}

void ManageFile::SetNameFile(string name)
{
	_nameFile = name;
}

void ManageFile::WriteFile(string content)
{
	string path = _nameDirectory + "/" + _nameFile;
	ofstream file_obj;
	file_obj.open(path, ios::app);
	//file_obj << (char *)&content << endl;
	file_obj.write(content.c_str(), sizeof(char)*content.size());

	file_obj.close();
}

void ManageFile::CreateDirectoryVideo()
{
	mkdir((char *)&_nameDirectory);
	//remove(_nameFile.c_str());
}

bool ManageFile::DeleteFileLog()
{
	if (remove(_nameFile.c_str()) != 0) {
		return false;
	}
	else {
		return true;
	}
}


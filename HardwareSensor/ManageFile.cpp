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

bool ManageFile::WriteFile(string content)
{
	string path = _nameDirectory + "/" + _nameFile;
	ofstream file_obj;
	file_obj.open(path, ios::app);
	file_obj << (char *)&content << endl;
	file_obj.close();
}

bool ManageFile::CreateDirectory()
{
	mkdir((char *)&_nameDirectory);
	remove(_nameFile.c_str());
}

bool ManageFile::DeleteFile()
{
	if (remove(_nameFile.c_str()) != 0) {
		return false;
	}
	else {
		return true;
	}
}


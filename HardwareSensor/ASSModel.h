#ifndef ASSModel_h
#define ASSModel_h

class ASSModel
{
public:
	ASSModel();
	~ASSModel();
	char* GetTemplate();
	int GetSize();
	void SetTemplate(char* templateInput);
	void SetSize(int size);
private:
	char* templateImage;
	int templateSize;
};

#endif // !ASSModel_h


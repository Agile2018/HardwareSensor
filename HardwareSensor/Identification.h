#ifndef Identification_h
#define Identification_h

class Identification
{
public:
	Identification();
	~Identification();
	void SetTimeOfIdentify(double time);
	void SetTimeOfEnroll(double time);
	void SetUserId(int id);
	void SetScore(int inputScore);
	double GetTimeOfIdentify();
	double GetTimeOfEnroll();
	int GetUserId();
	int GetScore();
private:
	double timeOfIdentify;
	double timeOfEnroll;
	int userId;
	int score;
};


#endif // !Identification_h


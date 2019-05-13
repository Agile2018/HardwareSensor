#include "Identification.h"

Identification::Identification()
{
}

Identification::~Identification()
{
}

void Identification::SetTimeOfIdentify(double time) {
	timeOfIdentify = time;
}

void Identification::SetTimeOfEnroll(double time) {
	timeOfEnroll = time;
}

void Identification::SetUserId(int id) {
	userId = id;
}

void Identification::SetScore(int inputScore) {
	score = inputScore;
}

double Identification::GetTimeOfIdentify() {
	return timeOfIdentify;
}

double Identification::GetTimeOfEnroll() {
	return timeOfEnroll;
}

int Identification::GetUserId() {
	return userId;
}

int Identification::GetScore() {
	return score;
}






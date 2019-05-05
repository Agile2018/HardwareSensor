// HardwareSensor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
#include "InitHardwareSensor.h"

void GetDetailHardware(InitHardwareSensor* initHardwareSensor) {
	initHardwareSensor->aSSCentralProcessingVideo->SaveDetailsHardware();
}
void GetIndicatorsVideo1(int detection, int cpu) {
	InitHardwareSensor* initHardwareSensor = new InitHardwareSensor(detection, cpu);
	initHardwareSensor->SetConfigurationVideo("video1.txt");
	initHardwareSensor->SetFileconfigurationDetect("detect1.txt");
	std::thread sv1(GetDetailHardware, initHardwareSensor);
	sv1.detach();

	auto frame_input
		= initHardwareSensor->aSSCentralProcessingVideo->observableFrame.map([](Mat img) {
		return img;
	});

	auto subscriptionFrame = frame_input.subscribe([](Mat img) {
		cv::imshow("video 1", img);
	});

	initHardwareSensor->RunProcessVideo();
}


int main(int argc, char* argv[])
{
	string strDetection = argv[1];
	string strCpu = argv[2];

	int detection = std::atoi(strDetection.c_str());
	int cpu = std::atoi(strCpu.c_str());
	cout << detection << cpu << endl;

	GetIndicatorsVideo1(detection, cpu);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

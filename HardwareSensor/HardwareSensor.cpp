// HardwareSensor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
#include "InitHardwareSensor.h"


string GetConfig(string nameFile) {
	string config;
	ifstream inconfig;
	inconfig.open(nameFile);
	if (inconfig.good()) {
		stringstream strStream;
		strStream << inconfig.rdbuf();
		config = strStream.str();
		inconfig.close();
	}
	else {
		cout << "File configuration not found" << endl;
	}
	return config;
}

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

void GetIndicatorsVideo2(int detection, int cpu) {
	InitHardwareSensor* initHardwareSensor = new InitHardwareSensor(detection, cpu);
	initHardwareSensor->SetConfigurationVideo("video2.txt");
	initHardwareSensor->SetFileconfigurationDetect("detect2.txt");
	std::thread sv1(GetDetailHardware, initHardwareSensor);
	sv1.detach();

	auto frame_input
		= initHardwareSensor->aSSCentralProcessingVideo->observableFrame.map([](Mat img) {
		return img;
	});

	auto subscriptionFrame = frame_input.subscribe([](Mat img) {
		cv::imshow("video 2", img);
	});

	initHardwareSensor->RunProcessVideo();
}

void GetIndicatorsVideo3(int detection, int cpu) {
	InitHardwareSensor* initHardwareSensor = new InitHardwareSensor(detection, cpu);
	initHardwareSensor->SetConfigurationVideo("video3.txt");
	initHardwareSensor->SetFileconfigurationDetect("detect3.txt");
	std::thread sv1(GetDetailHardware, initHardwareSensor);
	sv1.detach();

	auto frame_input
		= initHardwareSensor->aSSCentralProcessingVideo->observableFrame.map([](Mat img) {
		return img;
	});

	auto subscriptionFrame = frame_input.subscribe([](Mat img) {
		cv::imshow("video 3", img);
	});

	initHardwareSensor->RunProcessVideo();
}

void GetIndicatorsVideo4(int detection, int cpu) {
	InitHardwareSensor* initHardwareSensor = new InitHardwareSensor(detection, cpu);
	initHardwareSensor->SetConfigurationVideo("video4.txt");
	initHardwareSensor->SetFileconfigurationDetect("detect4.txt");
	std::thread sv1(GetDetailHardware, initHardwareSensor);
	sv1.detach();

	auto frame_input
		= initHardwareSensor->aSSCentralProcessingVideo->observableFrame.map([](Mat img) {
		return img;
	});

	auto subscriptionFrame = frame_input.subscribe([](Mat img) {
		cv::imshow("video 4", img);
	});

	initHardwareSensor->RunProcessVideo();
}

void ShootTwoVideo(int detection, int cpu) {
	std::thread sv1(GetIndicatorsVideo1, detection, cpu);
	std::thread sv2(GetIndicatorsVideo2, detection, cpu);
	sv1.join();
	sv2.join();
}

void ShootThreeVideo(int detection, int cpu) {
	std::thread sv1(GetIndicatorsVideo1, detection, cpu);
	std::thread sv2(GetIndicatorsVideo2, detection, cpu);
	std::thread sv3(GetIndicatorsVideo3, detection, cpu);
	sv1.join();
	sv2.join();
	sv3.join();
}

void ShootFourVideo(int detection, int cpu) {
	std::thread sv1(GetIndicatorsVideo1, detection, cpu);
	std::thread sv2(GetIndicatorsVideo2, detection, cpu);
	std::thread sv3(GetIndicatorsVideo3, detection, cpu);
	std::thread sv4(GetIndicatorsVideo4, detection, cpu);
	sv1.join();
	sv2.join();
	sv3.join();
	sv4.join();
}


int main(int argc, char* argv[])
{
	
	if (argc == 3)
	{
		string strDetection = argv[1];
		string strCpu = argv[2];

		int detection = std::atoi(strDetection.c_str());
		int cpu = std::atoi(strCpu.c_str());

		if ((detection == 1 || detection == 2) && (cpu == 1 || cpu == 2))
		{
			string devices = GetConfig("devices.txt");
			switch (devices[0])
			{
				case '1':
					GetIndicatorsVideo1(detection, cpu);
					break;
				case '2':
					ShootTwoVideo(detection, cpu);					
					break;
				case '3':
					ShootThreeVideo(detection, cpu);
					break;
				case '4':
					ShootFourVideo(detection, cpu);
					break;
			default:
				break;
			}
			
		}
		else {
			cout << "Set two parameters: Int 1 or 2 for type of detection (simple or batch) and 1 or 2 for cpu or gpu.";
		}

	}
	else {
		cout << "Set two parameters: Int 1 or 2 for type of detection (simple or batch) and 1 or 2 for cpu or gpu.";
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

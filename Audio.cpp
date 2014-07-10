// Audio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
void done()
{
	std::cout << "Done" << std::endl;
	int tmp;
	std::cin >> tmp;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	AudioRecorder recorder;
	recorder.Init();
	recorder.StartRecording();
	done();
	return 0;
}


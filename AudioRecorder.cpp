#include "stdafx.h"
#include "AudioRecorder.h"

const int BUFFER_DURATION = 10;
const int CHANNEL_COUNT = 1;
const int SAMPLE_RATE = 44100;
const int DATA_SIZE = SAMPLE_RATE * BUFFER_DURATION;
const int BUFFER_SIZE = 10;
const int NUMBER_OF_BUFFERS = 5;

AudioRecorder::AudioRecorder()
{
	buffers[NUMBER_OF_BUFFERS] = {};
}


bool AudioRecorder::Init()
{
	/** Set up the format **/
	format.nChannels = CHANNEL_COUNT;
	format.cbSize = 0;
	format.wFormatTag = WAVE_FORMAT_PCM;
	format.nSamplesPerSec = SAMPLE_RATE;
	format.wBitsPerSample = 8;	
	format.nAvgBytesPerSec = SAMPLE_RATE * (format.wBitsPerSample / 8);
	format.nBlockAlign = format.nChannels * format.wBitsPerSample / 8;

	/** Open Device **/
	 res = waveInOpen(&micHandle, WAVE_MAPPER, &format, (DWORD_PTR)waveOutCallback, (DWORD_PTR) this, CALLBACK_FUNCTION );
	if (res != MMSYSERR_NOERROR){
		std::cerr << "waveInOpen() Failed " << res << std::endl;
		return false;
	}

	WAVEHDR buffer;
	short int data[DATA_SIZE];

	buffer.lpData = (LPSTR)data;
	buffer.dwBufferLength = DATA_SIZE;
	buffer.dwBytesRecorded = 0;
	buffer.dwUser = 0;
	buffer.dwFlags = 0;
	buffer.dwLoops = 0;

	/***
	res = waveInPrepareHeader(micHandle, &buffer, sizeof(WAVEHDR));
	if (res != MMSYSERR_NOERROR)
	{
		std::cerr << "waveInPrepareHeader() Failed " << res << std::endl;
		return false;
	}

	res = waveInAddBuffer(micHandle, &buffer, sizeof(WAVEHDR));
	if (res != MMSYSERR_NOERROR)
	{
		std::cerr << "waveInAddBuffer() Failed " << res << std::endl;
		return false;
	} ***/
	
	addBuffer(buffer);
	/** Crash happens here ***/
	res = waveInStart(micHandle);
	if (res != MMSYSERR_NOERROR)
	{
		std::cerr << "waveInStart() Failed " << res << std::endl;
	}
	
	Sleep(10000);
	
	return true;
}

bool AudioRecorder::addBuffer(WAVEHDR buffer)
{
	 res = waveInPrepareHeader(micHandle, &buffer, sizeof(WAVEHDR));
	if (res != MMSYSERR_NOERROR)
	{
		std::cerr << "waveInPrepareHeader() Failed " << res << std::endl;
		return false;
	}
	
	res = waveInAddBuffer(micHandle, &buffer, sizeof(WAVEHDR));
	if (res != MMSYSERR_NOERROR)
	{
		std::cerr << "waveInAddBuffer() Failed " << res << std::endl;
		return false;
	}

	return true;
}


void CALLBACK waveOutCallback(HWAVEIN hWaveOut, UINT uMesg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	if (uMesg == WIM_DATA)
	{
		std::cout << "complete" << std::endl;
	}
}



bool AudioRecorder::StartRecording()
{
	
	return true;
}



void AudioRecorder::HandleError(std::string additional_info)
{
	int error_code = GetLastError();
	LPSTR buffer = NULL;
	int size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, NULL);

	std::string message;
	if (additional_info != "")
	{
		message = "[" + additional_info + "] " + buffer;
	}
	else {
		message = buffer;
	}

	std::cerr << message << std::endl;

	LocalFree(buffer);
}

AudioRecorder::~AudioRecorder()
{
}


void playData(WAVEHDR hdr)
{
	WAVEFORMATEX format;
	/** Set up the format **/
	format.nChannels = CHANNEL_COUNT;
	format.cbSize = 0;
	format.wFormatTag = WAVE_FORMAT_PCM;
	format.nSamplesPerSec = SAMPLE_RATE;
	format.wBitsPerSample = 8;
	format.nAvgBytesPerSec = SAMPLE_RATE * (format.wBitsPerSample / 8);
	format.nBlockAlign = format.nChannels * format.wBitsPerSample / 8;

	HWAVEOUT waveOut;


	MMRESULT res = waveOutOpen(&waveOut, WAVE_MAPPER, &format, 0, 0, CALLBACK_NULL);

	if (res != MMSYSERR_NOERROR)
	{
		std::cout << "Failed" << std::endl;
	}

	waveOutPrepareHeader(waveOut, &hdr, sizeof(WAVEHDR));

	waveOutWrite(waveOut, &hdr, sizeof(WAVEHDR));

	Sleep(500);
	while (waveOutUnprepareHeader(waveOut, &hdr, sizeof(WAVEHDR)) == WAVERR_STILLPLAYING)
	{
	}

}
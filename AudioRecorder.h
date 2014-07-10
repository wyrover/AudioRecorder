#pragma once
#include "CircularBuffer.h"

class AudioRecorder
{
public:
	AudioRecorder();
	~AudioRecorder();

	bool Init();
	bool packetAvailiable();

	bool StartRecording();
	void StopRecording();


	WAVEHDR getLatestPacket();

private:
	MMRESULT res;
	HWAVEIN micHandle;
	WAVEFORMATEX format;
	WAVEHDR buffers[];

	void HandleError(std::string additional_info);
	bool addBuffer(WAVEHDR buffer);
};

static void CALLBACK waveOutCallback(HWAVEIN hWaveOut, UINT uMesg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
void playData(WAVEHDR hdr);


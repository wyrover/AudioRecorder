#pragma once

class AudioRecorder
{
public:
	AudioRecorder();
	~AudioRecorder();
	void Update();

	bool Init(void(*callback)(WAVEHDR data));

	bool StartRecording();
	void StopRecording();

	WAVEHDR getNewWAVEHDR();

private:
	void(*callback)(WAVEHDR data);
	bool running;  

	MMRESULT res;
	HWAVEIN micHandle;
	WAVEFORMATEX format;
	WAVEHDR buffers[];

	bool addBuffer(WAVEHDR *buffer);
};

static void CALLBACK waveInCallback(HWAVEIN hWaveOut, UINT uMesg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
void playData(WAVEHDR hdr);


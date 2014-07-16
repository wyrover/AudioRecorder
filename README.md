Audio Recorder
==============

##### C++ Win32 Audio Recording using the Windows Wave API

Firstly, create a callback function: this is called everytime a new buffer is filled.

``` c++
void callback(WAVEHDR data)
{
	LPSTR audioData = data.lpData;
}
```

Then, just init and start the recording:

``` c++
AudioRecorder recorder;

// Inits everything
recorder.Init(callback);

// Start the recording process
recorder.StartRecording();

while (condition_to_continue_running)
{
	// Update the recorder: using this prevents the audio recorder from having to run in a new 
	// thread.
	recorder.Update();
}

// Stop recording from the microphone
recorder.StopRecording();
```


##### Notes 

The sound buffers (WAVEHDR::lpData) are pointers, and will be overwritten after number of audio buffers * duration of each buffer.

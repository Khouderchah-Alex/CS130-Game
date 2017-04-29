#pragma once

#include <unordered_map>
#include <al.h>
#include <alc.h>

struct SoundFileData
{
	unsigned int dataSize;
	ALuint frequency;
	ALenum format;
	unsigned char* buf;
	bool isLoop;
	std::string name;
};

<<<<<<< HEAD
struct SoundFileData
{
	unsigned int dataSize;
	ALuint frequency;
	ALenum format;
	unsigned char* buf;
	bool isLoop;
	std::string name;
};


=======
>>>>>>> origin/soundImplementation
class Sound
{
public:
	Sound();
	~Sound();
	std::string play(std::string);
	std::string stop(std::string);
	std::string pause(std::string);
	std::string InitializeSound(std::vector<SoundFileData>);


private:
	//OpenAl needs to know to play the sound is the position and velocity of the
	//source and the listener
	//orientation of the listener is described by two vectors, one pointing in the direction the listener
	//looks at and a second pointing up

	
	ALfloat SourcePos[3];
	ALfloat SourceVel[3];
	ALfloat ListenerPos[3];
	ALfloat ListenerVel[3];
	ALfloat ListenerOri[6];

	ALCcontext *context;
	ALCdevice *device;

	ALuint buffers[32];
	ALuint sources[32];

	int numberOfSounds;
	static std::unordered_map<std::string, int> sourceToNameConnection;
};
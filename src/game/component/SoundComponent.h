#pragma once

#include "Base.h"
#include "IComponent.h"
#include "TransformComponent.h"


class TransformComponent;


class SoundComponent : public IComponent
{
public:
	SoundComponent(Entity entity);
	~SoundComponent();

	void Refresh();
	void Tick(deltaTime_t dt);
	float m_ImpulseWait;

	void PlaySound(std::string);
	void PauseSound(std::string);
	void StopSound(std::string);

	void LoadSound(std::string, std::string, bool);
	TransformComponent * getTransformComponent();
	std::vector<ALuint> & getSource();

private:
	std::vector<SoundFileData> s_SoundFileData;
	std::unordered_map<std::string, int> s_SourceToNameConnection;

	std::vector<ALuint> m_Buffers;
	std::vector<ALuint> m_Sources;

	//orientation of the listener is described by two vectors, one pointing in the direction the listener
	//looks at and a second pointing up
	ALfloat m_SourcePos[3];
	ALfloat m_SourceVel[3];
	ALfloat m_ListenerPos[3];
	ALfloat m_ListenerVel[3];
	ALfloat m_ListenerOri[6];

	TransformComponent *m_pTransformComp;
};


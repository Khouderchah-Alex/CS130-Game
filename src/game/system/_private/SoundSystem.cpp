#include "SoundSystem.h"
#include "glm/vec3.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "PhysicsComponent.h"
#include <al.h>
#include <alc.h>

SoundSystem::SoundSystem() :
	m_pSoundComponent(EntityManager::GetAll<SoundComponent>())
{
}

bool SoundSystem::Initialize()
{
	//initialize the OpenAl
	m_pDevice = alcOpenDevice(NULL);
	if (!m_pDevice)
	{
		return false;
	}
	m_pContext = alcCreateContext(m_pDevice, NULL);
	alcMakeContextCurrent(m_pContext);
	if (!m_pContext)
	{
		return false;
	}

	return true;
}

void SoundSystem::Shutdown()
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(m_pContext);
	alcCloseDevice(m_pDevice);
}

void SoundSystem::Tick(deltaTime_t)
{
	
	//Updates sound location and velocity based on its TransformComponent position and PhysicsComponent speed
	//Also plays/pauses/stops any sound from the queue that is provided by the SoundComponent
	for (size_t i = 1; i < m_pSoundComponent.size(); ++i)
	{
		std::vector<ALuint *> &PlaySoundQueue = m_pSoundComponent[i]->GetPlaySoundQueue();
		std::vector<ALuint *> &PauseSoundQueue = m_pSoundComponent[i]->GetPauseSoundQueue();
		std::vector<ALuint *> &StopSoundQueue = m_pSoundComponent[i]->GetStopSoundQueue();
		while (PlaySoundQueue.size() > 0 && GetGameState()==EGS_STARTED)
			{
				alSourcePlay(*PlaySoundQueue.back());
				PlaySoundQueue.pop_back();
			}
		
		while(PauseSoundQueue.size() > 0)
		{
			alSourcePause(*PauseSoundQueue.back());
			PauseSoundQueue.pop_back();
		}

		while(StopSoundQueue.size() > 0)
		{
			alSourceStop(*StopSoundQueue.back());
			StopSoundQueue.pop_back();
		}

		TransformComponent *pTransform = EntityManager::GetComponent<TransformComponent>(m_pSoundComponent[i]->GetEntity());
		PhysicsComponent *pPhysics= EntityManager::GetComponent<PhysicsComponent>(m_pSoundComponent[i]->GetEntity());

		std::vector<ALuint> sources = m_pSoundComponent[i]->getSource();

		for (unsigned int j = 0; j < sources.size(); j++)
		{
			alSourcefv(sources[j], AL_POSITION, glm::value_ptr(pTransform->GetPosition()));
			alSourcefv(sources[j], AL_VELOCITY, glm::value_ptr(pPhysics->GetVelocity()));
		}
	}

	//Updating the listener position and orientation
	CameraComponent * pCurrentCamera = CameraComponent::GetCurrentCamera();

	TransformComponent *pTrans = EntityManager::GetComponent<TransformComponent>(pCurrentCamera->GetEntity());
	alListenerfv(AL_POSITION, glm::value_ptr(pTrans->GetPosition()));

	glm::mat3 orientationMatrix = glm::toMat3(pTrans->GetOrientation());
	glm::vec3 facingDir(0, 0, -1);
	facingDir = normalize(orientationMatrix * facingDir);
	glm::vec3 upDir(0, 1, 0);
	upDir = normalize(orientationMatrix * upDir);

	float listenerOri[6] = { facingDir[0], facingDir[1], facingDir[2], upDir[0], upDir[1], upDir[2] };
	alListenerfv(AL_ORIENTATION, listenerOri);
}

#include "TetradGame.h"

#include "EntityManager.h"
#include "ErrorSystem.h"
#include "EventSystem.h"
#include "ObserverComponent.h"
#include "PhysicsSystem.h"
#include "CollisionComponent.h"


TetradGame::TetradGame() :
	m_pDrawSystem(nullptr), m_pSystemObserver(nullptr),
	m_pInputSystem(nullptr), m_pSoundSystem(nullptr)
{
}

bool TetradGame::Initialize(const GameAttributes& attributes)
{
	// Game class contains important initializing functionality
	if(!Game::Initialize(attributes))
	{
		ERROR("Failed to initialize engine systems!\n", EEB_CONTINUE);
		return false;
	}

	// Create background
	// TODO - transform values only work for this particular aspect ratio
	// Only leaving the code like this in case we want to do something different
	// after the midterm demo
	Entity entity = EntityManager::CreateEntity();
	entity.Add<TransformComponent>()->Init(glm::vec3(0, 0, 1), glm::vec3(1.5f, 1.15f, 1));
	entity.Add<MovableComponent>();
	DrawComponent *pDraw = entity.Add<DrawComponent>();
	pDraw->SetGeometry(ShapeType::PLANE);
	pDraw->SetTexture(TEXTURE_PATH + "City.tga", TextureType::RGB);
	entity.Add<MaterialComponent>()->SetTimeRate(-0.2f);

	// Create floor
	entity = EntityManager::CreateEntity();
	entity.Add<TransformComponent>()->Init(glm::vec3(0, -1.f, 1), glm::vec3(1.5f, 0.1f, 1));
	entity.Add<MovableComponent>();
	//entity.Add<PhysicsComponent>();
	pDraw = entity.Add<DrawComponent>();
	pDraw->SetGeometry(ShapeType::PLANE);
	pDraw->SetTexture(FLOOR_PATH, TextureType::RGBA);
	entity.Add<MaterialComponent>()->SetTimeRate(-0.75f);
	CollisionComponent * pCol = entity.Add<CollisionComponent>();
	pCol->addPlane(0,-1,1);

	// Create camera
	entity = EntityManager::CreateEntity();
	entity.Add<TransformComponent>()->Init(glm::vec3(0, 0, 5));
	entity.Add<MovableComponent>();
	CameraComponent *pCamera = entity.Add<CameraComponent>();
	pCamera->SetCurrentCamera(pCamera);
	SoundComponent *pSound = entity.Add<SoundComponent>();
	pSound->LoadSound("backgroundMusic", SOUND_PATH + "backgroundMusic.wav", IS_LOOP);
	pSound->PlaySound("backgroundMusic");

	

	// Create jumping boxes
	for(int i = 0; i < 1; ++i)
	{
		entity = EntityManager::CreateEntity();
		entity.Add<TransformComponent>()->Init(glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(.2f, .2f, .2f));
		entity.Add<MovableComponent>();
		pDraw = entity.Add<DrawComponent>();
		pDraw->SetGeometry(ShapeType::PLANE);
		pDraw->SetTexture(TEXTURE_PATH + "bird.tga", TextureType::RGBA);
		entity.Add<PhysicsComponent>();
		ObserverComponent *pObserver = entity.Add<ObserverComponent>();
		pObserver->Subscribe(*m_pInputSystem);
		pObserver->AddEvent(EGameEvent(EGE_PLAYER1_JUMP), new Action_Jump(entity, 0));
		pObserver->AddEvent(EGameEvent(EGE_PLAYER2_JUMP), new Action_Jump(entity, 1));

		SoundComponent *pSound = entity.Add<SoundComponent>();
		pSound->LoadSound("wingsFlap", SOUND_PATH + "wingSound.wav", !IS_LOOP);
		CollisionComponent * pCol = entity.Add<CollisionComponent>();
		pCol->addSphere(1, 0.2f, 0.0f, 1.0f, 0.0f, ENABLE_ROTATION);
	}

	/*
	entity = EntityManager::CreateEntity();
	entity.Add<TransformComponent>()->Init(glm::vec3(0.5f, 1.f, 0.f),
		glm::vec3(.2f, .2f, .2f));
	entity.Add<MovableComponent>();
	pDraw = entity.Add<DrawComponent>();
	pDraw->SetGeometry(ShapeType::PLANE);
	pDraw->SetTexture(TEXTURE_PATH + "bird.tga", TextureType::RGBA);
	entity.Add<PhysicsComponent>();
	ObserverComponent *pObserver = entity.Add<ObserverComponent>();
	CollisionComponent * pCol2 = entity.Add<CollisionComponent>();
	pCol2->addSphere(1, 0.2f, 0.5f, 1.0f, 0.0f);
	*/




	// Create fade screen entity
	entity = EntityManager::CreateEntity();
	entity.Add<TransformComponent>()->Init(glm::vec3(0, 0, 1));
	pDraw = entity.Add<DrawComponent>();
	pDraw->SetGeometry(ShapeType::PLANE);
	pDraw->SetTexture(PAUSE_BACKGROUND_PATH, TextureType::RGBA);
	entity.Add<MaterialComponent>()->SetOpacity(0.f);
	Action_PauseGame::SetFadeScreen(entity);


	m_Timer.Start();

	return true;
}

void TetradGame::AddSystems()
{
	m_pInputSystem = new EventSystem;
	m_pInputSystem->MakeInputSystem();
	m_pSystems.push_back(m_pInputSystem);

	m_pSystems.push_back(new PhysicsSystem);

	m_pDrawSystem = new DrawSystem;
	m_pSystems.push_back(m_pDrawSystem);

	m_pSoundSystem = new SoundSystem;
	m_pSystems.push_back(m_pSoundSystem);

	m_pCollisionSystem = new CollisionSystem;
	m_pSystems.push_back(m_pCollisionSystem);

	// Create the system observer
	m_pSystemObserver = EntityManager::CreateEntity().Add<ObserverComponent>();
	m_pSystemObserver->Subscribe(*m_pInputSystem);
	m_pSystemObserver->AddEvent(EGE_PAUSE, new Action_PauseGame(m_pWindow));
}

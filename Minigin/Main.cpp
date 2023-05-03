#include <SDL.h>
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include "Achievement.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "TextureRenderer.h"
#include "FontRenderer.h"
#include "FPSCounter.h"
#include "CacheTestComponent.h"
#include "GameActor.h"
#include "TransformEx.h"
#include "GameObjectEx.h"
#include "GameObjectAltEx.h"
#include "InputManager.h"

glm::vec<2, glm::uint> g_WindowSize{ 1366, 720 };

GameObject* CreateWall(const glm::vec2& pos)
{
	const auto scene = SceneManager::GetInstance().GetActiveScene();

	const auto wallObject = new GameObject();

	const auto wallObjectTransformComponent = wallObject->GetComponent<Transform>();
	wallObjectTransformComponent->SetWorldPosition(pos);

	const auto wallTexture = wallObject->AddComponent<TextureRenderer>();
	wallTexture->SetTexture("Wall_Block.png");
	scene->Add(wallObject);

	return wallObject;
}

void CreateWalls()
{
	const auto scene = SceneManager::GetInstance().GetActiveScene();
	constexpr glm::vec<2, glm::uint> wallSize{ 100, 30 };



	//Will Also Render A texture, this texture will be shared over all the childs
	const auto wallParent = new GameObject();
	auto wallTransformP = wallParent->GetComponent<Transform>();
	//Needs to be put at right buttom or top lef?
	wallTransformP->SetWorldPosition({ 10,10 });
	auto wallTexture = wallParent->AddComponent<TextureRenderer>();
	wallTexture->SetTexture("Wall_Block.png");
	scene->Add(wallParent);

	const glm::vec2 length = { wallSize.x * wallTexture->GetSize().x,  wallSize.y * wallTexture->GetSize().y };
	const glm::vec2 startingPosOffset{ (g_WindowSize.x - length.x) / 2.f, (g_WindowSize.y - length.y) / 2.f };

	//Horizontal Walls
	const float yOffset{ wallSize.y * wallTexture->GetSize().y };
	for (size_t i{}; i < wallSize.x; ++i)
	{
		CreateWall({ startingPosOffset.x + (i * wallTexture->GetSize().x),startingPosOffset.y })->SetParent(wallParent, false);
		CreateWall({ startingPosOffset.x + i * wallTexture->GetSize().x,startingPosOffset.y + yOffset })->SetParent(wallParent, false);
	}

	//Vertical Walls
	const float xOffset{ wallSize.x * wallTexture->GetSize().x };
	for (size_t i{}; i < wallSize.y; ++i)
	{
		CreateWall({ startingPosOffset.x,i * wallTexture->GetSize().y + startingPosOffset.y })->SetParent(wallParent, false);
		CreateWall({ startingPosOffset.x + xOffset, i * wallTexture->GetSize().y + startingPosOffset.y })->SetParent(wallParent, false);
	}
}

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//Background Image
	//auto go = new GameObject();
	//const auto textureRendererBackground = go->AddComponent<TextureRenderer>();
	//textureRendererBackground->SetTexture(ResourceManager::GetInstance().LoadTexture("background.tga"));
	//scene.Add(go);

	//DAE Logo
	//auto go = new GameObject();
	//const auto transComponentLogo = go->GetComponent<Transform>();
	//transComponentLogo->SetLocalPosition({ 216, 180 });
	//const auto textureRendererLogo = go->AddComponent<TextureRenderer>();
	//textureRendererLogo->SetTexture("logo.tga");
	//scene.Add(go);

	////Pacman
	//auto pacman = new GameObject();
	//const auto textureRendererPacman{ pacman->AddComponent<TextureRenderer>() };
	//textureRendererPacman->SetTexture(ResourceManager::GetInstance().LoadTexture("Pacman320.png"));
	//const auto transformPacman{ pacman->GetComponent<Transform>() };
	//transformPacman->SetWorldPosition({ 350,50 });
	//scene.Add(pacman);

	////Ghost
	//go = new GameObject();
	//const auto textureRendererGhost{ go->AddComponent<TextureRenderer>() };
	//textureRendererGhost->SetTexture(ResourceManager::GetInstance().LoadTexture("Ghost320.png"));
	//go->SetParent(pacman, false);
	//const auto transformGhost{ go->GetComponent<Transform>() };
	//transformGhost->SetLocalPosition({ -100.f, 0 });
	////transformGhost->SetLocalRotation({ 0.f,0.5f });
	//scene.Add(go);

	//textureRendererGhost->MarkForDeletion();

	//Achievement unlocker
	//const auto achievement = std::make_shared<Achievement>();

	//Player1
	//auto gameac = new GameActor();
	//gameac->AddObeserver(achievement);
	//scene.Add(gameac);

	////Health Counter1
	//auto health = new GameObject();
	//const auto transComponentHealth{ health->GetComponent<Transform>() };
	//transComponentHealth->SetLocalPosition({ 5, 50 });
	//const auto fontRendererHealth = health->AddComponent<FontRenderer>();
	//fontRendererHealth->SetFont("Lingua.otf", 15);
	//fontRendererHealth->SetText(gameac->GetHealthAsString());
	//scene.Add(health);

	////Point Counter1
	//auto points = new GameObject();
	//const auto Transpoints{ points->GetComponent<Transform>() };

	//Transpoints->SetLocalPosition({ 5, 100 });
	//const auto fontRenderPoints = points->AddComponent<FontRenderer>();
	//fontRenderPoints->SetFont("Lingua.otf", 15);
	//fontRenderPoints->SetText(gameac->GetPointsAsString());
	//scene.Add(points);

	////Player2
	//auto ga = new GameActor();
	//scene.Add(ga);
	//ga->SetControllerIndex(0);
	//ga->AddObeserver(achievement);

	////Health Counter2
	//auto health2 = new GameObject();
	//const auto transComponentHealth2{ health2->GetComponent<Transform>() };
	//transComponentHealth2->SetLocalPosition({ 5, 150 });
	//const auto fontRendererHealth2 = health2->AddComponent<FontRenderer>();
	//fontRendererHealth2->SetFont("Lingua.otf", 15);
	//fontRendererHealth2->SetText(ga->GetHealthAsString());
	//scene.Add(health2);

	////Point Counter2
	//auto points2 = new GameObject();
	//const auto Transpoints2{ points2->GetComponent<Transform>() };

	//Transpoints2->SetLocalPosition({ 5, 200 });
	//const auto fontRenderPoints2 = points2->AddComponent<FontRenderer>();
	//fontRenderPoints2->SetFont("Lingua.otf", 15);
	//fontRenderPoints2->SetText(ga->GetPointsAsString());
	//scene.Add(points2);

	////TrashCacheComponent
	//go = new GameObject();
	//const auto transComponentCache = go->GetComponent<Transform>();
	//transComponentLogo->SetLocalPosition({ 216, 180 });

	//const auto transformEx = go->AddComponent<TransformEx>();
	//const auto gameobjectEx = go->AddComponent<GameObjectEx>();
	//const auto gameobjectAltEx = go->AddComponent<GameObjectAltEx>();


	//const auto cacheComponent1 = go->AddComponent<CacheTestComponent>();
	//cacheComponent1->SetComponentToTest<TransformEx>(transformEx.get());

	//const auto cacheComponent2 = go->AddComponent<CacheTestComponent>();
	//cacheComponent2->SetComponentToTest<GameObjectEx>(gameobjectEx.get());

	//const auto cacheComponent3 = go->AddComponent<CacheTestComponent>();
	//cacheComponent3->SetComponentToTest<GameObjectAltEx>(gameobjectAltEx.get());

	//const auto cacheComponent4 = go->AddComponent<Transform>();
	//cacheComponent3->SetComponentToTest<Transform>(transComponentCache.get());
	//scene.Add(go);


	//FPS Counter
	auto go = new GameObject();
	const auto fpsCounter{ go->AddComponent<FPSCounter>() };
	const auto transComponentFPS{ go->GetComponent<Transform>() };
	transComponentFPS->SetLocalPosition({ 5, 5 });
	const auto fontRendererFPS = go->AddComponent<FontRenderer>();
	fontRendererFPS->SetFont("Lingua.otf", 20);
	scene.Add(go);

	CreateWalls();

	//Player1
	auto gameac = new GameActor();
	//gameac->AddObeserver(achievement);
	scene.Add(gameac);


}

int main(int, char* [])
{
	//if (SteamAPI_Init())
	//{
	//	std::cout << "Successfully initialized steam." << std::endl;
	//}
	//else
	//{

	//	std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
	//	return 1;
	//}

	Minigin engine("../Data/", g_WindowSize);
	engine.Run(load);

	//SteamAPI_Shutdown();
	return 0;
}
#include <SDL.h>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>

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

#include "TransformEx.h"
#include "GameObjectEx.h"
#include "GameObjectAltEx.h"

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//Background Image
	//auto go = new GameObject();
	//const auto textureRendererBackground = go->AddComponent<TextureRenderer>();
	//textureRendererBackground->SetTexture(ResourceManager::GetInstance().LoadTexture("background.tga"));
	//scene.Add(go);

	//DAE Logo
	auto go = new GameObject();
	const auto transComponentLogo = go->GetComponent<Transform>();
	transComponentLogo->SetLocalPosition({ 216, 180 });
	const auto textureRendererLogo = go->AddComponent<TextureRenderer>();
	textureRendererLogo->SetTexture("logo.tga");
	scene.Add(go);

	////FPS Counter
	//go = new GameObject();
	//const auto fpsCounter{ go->AddComponent<FPSCounter>() };
	//const auto transComponentFPS{ go->GetComponent<Transform>() };
	//transComponentFPS->SetLocalPosition({ 5, 5 });
	//const auto fontRendererFPS = go->AddComponent<FontRenderer>();
	//fontRendererFPS->SetFont("Lingua.otf", 20);
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


	//TrashCacheComponent
	go = new GameObject();
	const auto transComponentCache = go->GetComponent<Transform>();
	transComponentLogo->SetLocalPosition({ 216, 180 });

	const auto transformEx = go->AddComponent<TransformEx>();
	const auto gameobjectEx = go->AddComponent<GameObjectEx>();
	const auto gameobjectAltEx = go->AddComponent<GameObjectAltEx>();


	const auto cacheComponent1 = go->AddComponent<CacheTestComponent>();
	cacheComponent1->SetComponentToTest<TransformEx>(transformEx.get());

	const auto cacheComponent2 = go->AddComponent<CacheTestComponent>();
	cacheComponent2->SetComponentToTest<GameObjectEx>(gameobjectEx.get());

	const auto cacheComponent3 = go->AddComponent<CacheTestComponent>();
	cacheComponent3->SetComponentToTest<GameObjectAltEx>(gameobjectAltEx.get());
	scene.Add(go);
}

int main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(load);
	return 0; 
}
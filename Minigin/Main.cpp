#include <SDL.h>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include "GameObject.h"
#include "Transform.h"
#include "TextureRenderer.h"
#include "FontRenderer.h"

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	const auto transformComponentBackground = go->AddComponent<Transform>();
	transformComponentBackground->SetPosition({ 0, 0 });
	const auto textureRendererBackground = go->AddComponent<TextureRenderer>();
	textureRendererBackground->SetTexture(ResourceManager::GetInstance().LoadTexture("background.tga"));
	scene.Add(go);



	go = std::make_shared<GameObject>();
	const auto transComponentLogo = go->AddComponent<Transform>();
	transComponentLogo->SetPosition({ 216, 180 });
	const auto textureRendererLogo = go->AddComponent<TextureRenderer>();
	textureRendererLogo->SetTexture(ResourceManager::GetInstance().LoadTexture("logo.tga"));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	const auto transComponentFont{ go->AddComponent<Transform>() };
	transComponentFont->SetPosition({ 80, 20 });

	const auto fontRenderer = go->AddComponent<FontRenderer>();


	//fontRenderer->SetFont("Lingua.otf", 36);
	//fontRenderer->SetText("Programming 4 Assignment TEST");
	//scene.Add(go);
}

int main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
#include "SceneManager.h"
#include "Scene.h"
#include "Time.h"
#include "GameActor.h"

void SceneManager::Update()
{
	for (auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void SceneManager::FixedUpdate(float fixedTimeStep)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTimeStep);
	}
}

void SceneManager::LateUpdate()
{
	for (const auto& scene : m_scenes)
	{
		scene->LateUpdate();
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

std::vector<GameActor*> SceneManager::GetGameActorsOfScene(const std::string& sceneName) const
{
	return  GetSceneByName(sceneName)->GetAllGameActors();
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

Scene* SceneManager::GetSceneByName(const std::string& name) const
{
	for (const auto& scene : m_scenes)
	{
		if (scene->GetName()._Equal(name))
		{
			return scene.get();
		}
	}
	
	//Todo: Throw custom error here
	return nullptr;
}

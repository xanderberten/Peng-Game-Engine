﻿#include "GameActor.h"
#include <iostream>
#include "FontRenderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "TextureRenderer.h"
#include "Time.h"
#include "Transform.h"

GameActor::GameActor()
{
	const auto textureRenderer{ AddComponent<TextureRenderer>() };
	//TODO: Set with function or in constructor?
	textureRenderer->SetTexture("Pengo.png");

	const auto spriteRenderer{ AddComponent<SpriteRenderer>() };

	spriteRenderer->SetSourceRect({ 0,0 }, { 16, 16 });


	InputManager::GetInstance().AddActor(this);
}

GameActor::~GameActor()
{

}

void GameActor::Update()
{
	//if (const auto fontRenderer = GetComponent<FontRenderer>())
	//{
	//	fontRenderer->SetText(std::to_string(m_Health));
	//}
	const auto elapsed = static_cast<int>(Time::GetInstance().GetElapsed() * 4) % 2;

	if (!elapsed)
	{
		GetComponent<SpriteRenderer>()->SetSourceRect({ 16,0 }, { 16,16 });
	}
	else
	{
		GetComponent<SpriteRenderer>()->SetSourceRect({ 0,0 }, { 16,16 });
	}
}

void GameActor::Jump()
{
	//std::cout << "The actor Jumps!\n";
	//glm::vec2 pos = direction * speed * dt;
	//m_pActor->GetComponent<Transform>().get()->SetLocalPosition();
}

void GameActor::Move(const glm::vec2& direction)
{
	const auto transform = GetComponent<Transform>();
	const auto movement{ direction * m_Speed * Time::GetInstance().GetDeltaTime() };

	transform->SetLocalPosition(transform->GetLocalPosition() + movement);
}

void GameActor::Die()
{
	NotifyObserver(GameEvent::ActorDied);

	MarkForDeletion();
}

void GameActor::TakeDammage(const int dammage)
{
	if (!m_Health) return;

	m_Health -= dammage;
	m_HealthString = std::to_string(m_Health);

	if (!m_Health) Die();
}


void GameActor::GainPoints(int ammountOfPoints)
{
	m_Points += ammountOfPoints;
	m_PointString = std::to_string(m_Points);

	if (m_Points >= 100) NotifyObserver(GameEvent::Actor100Points);
}

void GameActor::SetControllerIndex(int index)
{
	m_UsesController = true;
	m_ControllerID = index;
	const auto& controllers = InputManager::GetInstance().GetControllers();

	for (const auto& controller : controllers)
	{
		if (controller->GetControllerID() == index)
		{
			controller->SetActor(this);
		}
	}

}

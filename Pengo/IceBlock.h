﻿#pragma once
#include <glm/vec2.hpp>
#include "GameObject.h"
#include "SpriteRenderer.h"

class IceBlock final : public GameObject
{
public:
	IceBlock();
	virtual ~IceBlock() override;

	IceBlock(const IceBlock& other) = delete;
	IceBlock(IceBlock&& other) = delete;
	IceBlock& operator=(const IceBlock& other) = delete;
	IceBlock& operator=(IceBlock&& other) = delete;


	virtual void Update() override;
	virtual void OnCollision(GameObject* other) override;

	void MoveIceBlock(const MovementDirection fireDirection);
	bool IsMoving() const;

private:
	const size_t m_NrFrames{ 10 };
	const glm::vec2 m_SpriteSize{ 16,16 };
	glm::vec2 m_Velocity{ 0,0 };
	bool m_IsMoving{ false };

	void UpdateMovement();
	void UpdateSpriteLogic();
};

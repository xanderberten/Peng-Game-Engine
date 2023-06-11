﻿#include "MoveComponent.h"

#include "DirectionComponent.h"
#include "TimeM.h"
#include "Transform.h"
#include "VelocityComponent.h"
#include <glm/gtx/fast_square_root.hpp> 

MoveComponent::MoveComponent(GameObject* pOwner) : Component(pOwner)
{
}

void MoveComponent::Update()
{
	if (m_CanMove)
	{
		const auto direction = m_pOwner->GetComponent<DirectionComponent>();
		const auto velocity = m_pOwner->GetComponent<VelocityComponent>();
		const auto transform = m_pOwner->GetComponent<Transform>();

		if (direction && velocity && transform)
		{
			const auto movement{ direction->GetDirection() * velocity->GetVelocity() * TimeM::GetInstance().GetDeltaTimeM() };
			transform->SetWorldPosition(transform->GetWorldPosition() + movement);
		}
	}
}

void MoveComponent::FixedUpdate(float /*fixedTimeMStep*/)
{
}

void MoveComponent::LateUpdate()
{
	m_MoveChanged = false;
}

void MoveComponent::Render()
{
}

void MoveComponent::SetCanMove(bool canMove)
{

	if (canMove != m_CanMove)
	{
		m_MoveChanged = true;
		m_CanMove = canMove;
	}

	if (canMove)
	{
		m_DistanceMoved = 0.f;
		m_StartingPosition = m_pOwner->GetComponent<Transform>()->GetWorldPosition();
	}
	else
	{
		m_EndingPosition = m_pOwner->GetComponent<Transform>()->GetWorldPosition();
		m_DistanceMoved = glm::abs(length(m_EndingPosition - m_StartingPosition));
	}
}

bool MoveComponent::CanMove() const
{
	return m_CanMove;
}

void MoveComponent::ResetMovement()
{
	if (const auto transform = m_pOwner->GetComponent<Transform>())
	{
		if (const auto directionComponent = m_pOwner->GetComponent<DirectionComponent>())
		{
			transform->SetWorldPosition(transform->GetLastWorldPosition() + (-directionComponent->GetDirection() * m_TunnelingMulitplier));
		}
	}
}

void MoveComponent::SetTunnelingMultiplier(float multiplier)
{
	m_TunnelingMulitplier = multiplier;
}

float MoveComponent::GetTunnelingMultiplier() const
{
	return m_TunnelingMulitplier;
}

bool MoveComponent::GetMoveChanged() const
{
	return m_MoveChanged;
}

float MoveComponent::GetDistanceMoved() const
{
	return m_DistanceMoved;
}

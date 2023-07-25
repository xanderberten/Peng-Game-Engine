#include "PacManState.h"
#include "CountdownComponent.h"
#include "GhostComponent.h"
#include "MoveComponent.h"
#include "PacDotComponent.h"
#include "PacManComponent.h"
#include "PowerUpComponent.h"
#include "SpriteRenderer.h"
#include "WallComponent.h"

//MOVE
//
//
PacManMoveState::PacManMoveState(GameObject* object) : State(object)
{
	OnEnter();
}

State* PacManMoveState::HandleInput()
{
	if(m_pActor->GetComponent<CountdownComponent>()->IsTimeUp())
	{
		return new PacManIdleState(m_pActor);
	}

	return nullptr;
}

void PacManMoveState::Update()
{
	const auto timer = m_pActor->GetComponent<CountdownComponent>();

	if(m_pActor->GetComponent<MoveComponent>()->IsMovingThisFrame())
	{
		timer->ResetTime();
		timer->Pause();
	}
	else
	{
		timer->Play();
	}
	
}

void PacManMoveState::OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger)
{

	if(other->GetComponent<PacDotComponent>())
	{
		other->MarkForDeletion();
		// TODO Increase points here
	}


	//The Ghost Trigger is colliding with a wall
	if (other->GetComponent<WallComponent>() && isSenderTrigger)
	{
		m_pActor->GetComponent<MoveComponent>()->ResetMovement();
	}


	//Colliding with a ghost
	if(other->GetComponent<GhostComponent>()&& !isSenderTrigger && !isTrigger)
	{
		m_pActor->GetComponent<PacManComponent>()->Die();
	}

	if(other->GetComponent<PowerUpComponent>() && !isSenderTrigger && !isTrigger)
	{
		//Alert All Ghost to change state
	}
}

void PacManMoveState::OnEnter()
{
	
	if(const auto timer = m_pActor->GetComponent<CountdownComponent>())
	{
		timer->SetTime(0.1f);
		timer->Pause();
	}

	m_pActor->GetComponent<SpriteRenderer>()->Play();
}



//IDLE
//
//
PacManIdleState::PacManIdleState(GameObject* object) : State(object)
{
	OnEnter();
}

State* PacManIdleState::HandleInput()
{
	
	if (m_pActor->GetComponent<MoveComponent>()->IsMovingThisFrame())
	{		
		return new PacManMoveState(m_pActor);
	}

	return nullptr;
}

void PacManIdleState::Update()
{
}

void PacManIdleState::OnCollision(GameObject* /*other*/, bool /*isTrigger*/, bool /*isSenderTrigger*/)
{
}

void PacManIdleState::OnEnter()
{
	m_pActor->GetComponent<SpriteRenderer>()->Pause();
}

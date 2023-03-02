﻿#include "FontRenderer.h"

#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include <stdexcept>
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Transform.h"

FontRenderer::FontRenderer() : Component()
{
}

FontRenderer::~FontRenderer() = default;

void FontRenderer::Update([[maybe_unused]] float deltaT)
{
	//needs: font, color, text
	if (m_needsUpdate && m_font)
	{
		const SDL_Color color = { 255,255,255 }; //TODO only white text is supported now

		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);

		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void FontRenderer::FixedUpdate([[maybe_unused]] float fixedTimeStep)
{
}

void FontRenderer::LateUpdate([[maybe_unused]] float deltaT)
{
}

void FontRenderer::Render() const
{
	//needs: texture, transform
	if (m_textTexture)
	{
		if (const auto transformComponent{ GetComponent<Transform>() })
		{
			const auto& pos = transformComponent->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
		}
		else
		{
			//TODO make own error class
			throw std::runtime_error(std::string("FontRenderer::Render() is dependent on a Transform Component"));
		}
	}
}

void FontRenderer::SetText(const std::string& text)
{
	m_text = text;

	if (m_font)
	{
		m_needsUpdate = true;
	}
}

void FontRenderer::SetFont(const std::string& fontPath, int fontSize)
{
	m_font = { ResourceManager::GetInstance().LoadFont(fontPath, fontSize) };
	m_needsUpdate = true;
}

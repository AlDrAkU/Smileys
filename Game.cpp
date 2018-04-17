#include "stdafx.h"
#include "Game.h"
#include "Smiley.h"

Game::Game(const Window& window)
	: m_Window{ window }
	, m_pSmileyTexture{}
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_pSmileyTexture = std::make_shared<Texture>("Resources/smileys.png");
	CreateSmileys();
}

void Game::Cleanup()
{

}

void Game::Update(float elapsedSec)
{
	UpdateSmileys(elapsedSec, Rectf{ 0,0,m_Window.width, m_Window.height });
	DetermineHighestSmiley();
}

void Game::Draw() const
{
	ClearBackground();
	DrawSmileys();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		IncreaseSmileysSpeed();
		break;
	case SDLK_DOWN:
		DecreaseSmileysSpeed();
		break;
	}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		HitTestSmileys(Point2f{ float(e.x), m_Window.height - float(e.y) });
		break;
	}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ClearBackground() const
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::CreateSmileys()
{
	for (int i{ 0 }; i < m_NumSmileys; ++i)
	{
		m_pSmileys.push_back(std::make_unique<Smiley>(Point2f{ i * (m_Window.width / m_NumSmileys), m_Window.height / 2 }, m_pSmileyTexture));
	}
}

void Game::DrawSmileys() const
{
	for (const std::unique_ptr<Smiley> &pSmiley : m_pSmileys)
	{
		pSmiley->Draw();
	}
}

void Game::UpdateSmileys(float elapsedSec, const Rectf& boundingRect)
{
	for (std::unique_ptr<Smiley> &pSmiley : m_pSmileys)
	{
		pSmiley->Update(elapsedSec, boundingRect);
	}
}


void Game::HitTestSmileys(const Point2f& pos)
{
	for (std::unique_ptr<Smiley> &pSmiley : m_pSmileys)
	{
		pSmiley->HitTest(pos);
	}
}

void Game::DetermineHighestSmiley()
{
	float maxBottom{ -20 };
	int highestIdx{ -1 };

	for (int idx{ 0 }; idx < m_NumSmileys; ++idx)
	{
		m_pSmileys[idx]->SetHighest(false);

		if (!m_pSmileys[idx]->IsSleeping())
		{
			if (m_pSmileys[idx]->GetPosition().y > maxBottom)
			{
				maxBottom = m_pSmileys[idx]->GetPosition().y;
				highestIdx = idx;
			}
		}
	}

	if (highestIdx > -1)
	{
		m_pSmileys[highestIdx]->SetHighest(true);
	}
}

void Game::IncreaseSmileysSpeed()
{
	for (std::unique_ptr<Smiley> &pSmiley : m_pSmileys)
	{
		pSmiley->IncreaseSpeed();
	}
}

void Game::DecreaseSmileysSpeed()
{
	for (std::unique_ptr<Smiley> &pSmiley : m_pSmileys)
	{
		pSmiley->DecreaseSpeed();
	}
}


#include "stdafx.h"
#include "Smiley.h"
#include "Texture.h"
#include "utils.h"


Smiley::Smiley( const Point2f& position, std::shared_ptr<Texture> pSmileyTexture)
	:m_Position{ position }
	,m_pSmileyTexture{pSmileyTexture}
	,m_Velocity{ rand( ) % 121 + 60.0f, rand( ) % 121 + 60.0f } // [60, 180]
	,m_IsHighest{false}
	,m_IsSleeping{false}
	,m_IsInDangerousArea{false}
	,m_ScaredDistance{20.0f}
	,m_NumCols{ 4 }
	,m_HappyFrameNr{ 0 }
	,m_NeutralFrameNr{ 1 }
	,m_ScaredFrameNr{ 2 }
	,m_SleepingFrameNr{ 3 }
{
	if ( m_pSmileyTexture )
	{
		m_Radius = m_pSmileyTexture->GetHeight( ) / 2;
	}

	// Random direction
	if ( rand( ) % 2 == 0 )
		m_Velocity.x *= -1;
	if ( rand( ) % 2 == 0 )
		m_Velocity.y *= -1;
}

void Smiley::Draw( ) const
{
	int frameNr{ m_NeutralFrameNr };
	if ( m_IsSleeping )
	{
		frameNr = m_SleepingFrameNr;
	}
	else if ( m_IsHighest )
	{
		frameNr = m_HappyFrameNr;
	}
	else if ( m_IsInDangerousArea )
	{
		frameNr = m_ScaredFrameNr;
	}
	// Set the source rectangle to be rendered
	float frameWidth{ m_pSmileyTexture->GetWidth( ) / m_NumCols };
	float frameHeight{ m_pSmileyTexture->GetHeight( ) };
	Rectf sourceRect{ frameWidth * frameNr, frameHeight, frameWidth, frameHeight };
	Rectf destRect{ m_Position.x, m_Position.y, frameWidth, frameHeight };

	//Render on the window
	m_pSmileyTexture->Draw( destRect, sourceRect );
}

void Smiley::Update( float elapsedSec, const Rectf& boundaries )
{
	if ( !m_IsSleeping )
	{
		UpDatePosition( elapsedSec );
		CheckBoundaries( boundaries );
		m_IsInDangerousArea = IsInDangerousArea( boundaries );
	}
}

void Smiley::HitTest( const Point2f & pos )
{
	if ( utils::IsPointInCircle( pos, Circlef{ Point2f{m_Position.x + m_Radius, m_Position.y + m_Radius}, m_Radius } ) )
	{
		m_IsSleeping = !m_IsSleeping;
	}
}

bool Smiley::IsSleeping( ) const
{
	return m_IsSleeping;
}

Point2f Smiley::GetPosition( ) const
{
	return m_Position;
}

void Smiley::SetHighest( bool isHighest )
{
	m_IsHighest = isHighest;
}

void Smiley::IncreaseSpeed( )
{
	m_Velocity *= 1.05f;
}

void Smiley::DecreaseSpeed( )
{
	m_Velocity /= 1.05f;
}

bool Smiley::IsInDangerousArea( const Rectf& boundaries ) const
{
	if ( m_Position.x + m_Radius * 2 + m_ScaredDistance > boundaries.width + boundaries.left ||
		m_Position.y + m_Radius * 2 + m_ScaredDistance > boundaries.height + boundaries.bottom ||
		m_Position.x - m_ScaredDistance < boundaries.left ||
		m_Position.y - m_ScaredDistance < boundaries.bottom )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Smiley::UpDatePosition( float elapsedSec )
{
	m_Position.x += ( m_Velocity.x * elapsedSec );
	m_Position.y += ( m_Velocity.y * elapsedSec );
}

void Smiley::CheckBoundaries( const Rectf& boundaries )
{
	if ( m_Velocity.x < 0 && m_Position.x < boundaries.left )
	{
		m_Position.x = boundaries.left;
		m_Velocity.x *= -1; // turn
	}
	if ( m_Velocity.y < 0 && m_Position.y  < boundaries.bottom )
	{
		m_Position.y = boundaries.bottom;
		m_Velocity.y *= -1; // turn
	}
	if ( m_Velocity.x > 0 && m_Position.x + m_Radius * 2 > boundaries.width + boundaries.left )
	{
		m_Position.x = boundaries.width + boundaries.left - m_Radius * 2.0f;
		m_Velocity.x *= -1; // turn
	}
	if ( m_Velocity.y > 0 && m_Position.y + m_Radius * 2 > boundaries.height + boundaries.bottom )
	{
		m_Position.y = boundaries.height + boundaries.bottom - m_Radius * 2.0f;
		m_Velocity.y *= -1; // turn
	}
}

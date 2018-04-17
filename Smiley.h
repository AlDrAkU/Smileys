#pragma once
#include "Vector2f.h"
#include <memory>
class  Texture;

class Smiley
{
public:
	// Aggregation with Texture pointer
	Smiley( const Point2f& position, std::shared_ptr<Texture> pSmileyTexture);
	
	void Draw( ) const;
	void Update( float elapsedSec, const Rectf& boundingRect );
	void HitTest( const Point2f& pos );
	bool IsSleeping( ) const;
	Point2f GetPosition( ) const;
	void SetHighest( bool isHighest );
	void IncreaseSpeed( );
	void DecreaseSpeed( );

private:
	// DATA MEMBERS
	std::shared_ptr<Texture> m_pSmileyTexture;
	float m_Radius;
	const int m_NumCols;
	const int m_HappyFrameNr;
	const int m_NeutralFrameNr;
	const int m_ScaredFrameNr;
	const int m_SleepingFrameNr;

	Point2f m_Position;
	Vector2f m_Velocity;
	bool m_IsHighest;
	bool m_IsSleeping;
	bool m_IsInDangerousArea;
	const float m_ScaredDistance;

	// FUNCTIONS
	bool IsInDangerousArea( const Rectf& boundaries ) const;
	void UpDatePosition( float elapsedSec );
	void CheckBoundaries( const Rectf& boundaries );
};



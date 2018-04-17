#pragma once
#include <vector>
#include "Texture.h"
#include <memory>

class Smiley;
class Game
{
public:
	explicit Game( const Window& window );
	Game( const Game& other ) = delete;
	Game& operator=( const Game& other ) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	Window m_Window;
	static const int m_NumSmileys{ 10 };
	std::vector<std::unique_ptr<Smiley>> m_pSmileys;
	std::shared_ptr<Texture> m_pSmileyTexture;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void CreateSmileys();
	void DeleteSmileys();
	void DrawSmileys() const;
	void UpdateSmileys(float elapsedSec, const Rectf& boundingRect);
	void HitTestSmileys(const Point2f& pos);
	void DetermineHighestSmiley();
	void IncreaseSmileysSpeed();
	void DecreaseSmileysSpeed();
};
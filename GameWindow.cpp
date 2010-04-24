// vim:ts=4

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <boost/lexical_cast.hpp>

#include <list>
#include <cstdio>

#include "Config.h"
#include "GameWindow.h"

GameWindow::GameWindow()
	: Window(510, 510, false, 250), 
		_font(graphics(), Gosu::defaultFontName(), 20),
		_block(graphics(), 30, 30, 30, 30),
		_board(_block, 10, 15),
		_tetramino(_block, 0, 0, sS, cBlue)
{
	setCaption(L"AlTris");

	std::wstring filename = Gosu::sharedResourcePrefix() + L"media/background.png";
	_backgroundImage.reset(new Gosu::Image(graphics(), filename, false));
}

void GameWindow::update()
{
	static bool isLeft = false;
	static bool isRight = false;
	static bool isUp = false;

	if (input().down(Gosu::kbLeft)) {
		if (!isLeft) _tetramino.MoveLeft();
		isLeft = true;
	} else {
		isLeft = false;
	}

	if (input().down(Gosu::kbRight)) {
		if (!isRight) _tetramino.MoveRight();
		isRight = true;
	} else {
		isRight = false;
	}

	//if (input().down(Gosu::kbUp))

	_tetramino.MoveDown();
}

void GameWindow::draw()
{
	_tetramino.Draw();
	_board.Draw();
	_backgroundImage->draw(0, 0, zBackground);
}

void GameWindow::buttonDown(Gosu::Button btn)
{
	if (btn == Gosu::kbEscape)
		close();
}

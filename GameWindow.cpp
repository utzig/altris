// vim:ts=4

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <boost/lexical_cast.hpp>

#include <list>
#include <cstdio>

#include "Config.h"
#include "GameWindow.h"

GameWindow::GameWindow()
	: Window(510, 510, false), 
		_font(graphics(), Gosu::defaultFontName(), 20),
		_block(graphics(), 30, 30),
		_board(_block, 10, 15)
{
	setCaption(L"AlTris");
	time_t seconds = time(NULL);
	std::srand(seconds);

	std::wstring filename = Gosu::sharedResourcePrefix() + L"media/background.png";
	_backgroundImage.reset(new Gosu::Image(graphics(), filename, false));

	_tetramino = new Tetramino(_block,
		30,
		30,
		0,
		0,
		static_cast<Shape>(Gosu::random(sI, sZ+1)),
		static_cast<Color>(Gosu::random(cBlue, cYellow+1)));

	_nextTetramino = new Tetramino(_block,
		360,
		30,
		0,
		0,
		static_cast<Shape>(Gosu::random(sI, sZ+1)),
		static_cast<Color>(Gosu::random(cBlue, cYellow+1)));

	int w = _nextTetramino->GetWidth();
	int h = _nextTetramino->GetHeight();

	// center next piece on preview pane
	_nextTetramino->SetOffsetXY(420 - w*30/2, 75 - h*30/2);
}

void GameWindow::update()
{
	static bool isLeft = false;
	static bool isRight = false;
	static bool isUp = false;

	if (input().down(Gosu::kbLeft)) {
		if (!isLeft && !_tetramino->CheckForLeftCollision(_board))
			_tetramino->MoveLeft();
		isLeft = true;
	} else {
		isLeft = false;
	}

	if (input().down(Gosu::kbRight)) {
		if (!isRight && !_tetramino->CheckForRightCollision(_board))
			_tetramino->MoveRight();
		isRight = true;
	} else {
		isRight = false;
	}

	if (input().down(Gosu::kbUp)) {
		if (!isUp) _tetramino->Rotate();
		isUp = true;
	} else {
		isUp = false;
	}

	if (input().down(Gosu::kbDown)) {
		_tetramino->DownPressed();
	}

	if (_tetramino->CheckForDownCollision(_board)) {
		_board.CopyFromTetramino(_tetramino);
		_board.RemoveCompleteLines();

		delete _tetramino;
		_tetramino = _nextTetramino;
		_tetramino->SetOffsetXY(30, 30);

		_nextTetramino = new Tetramino(_block,
			360,
			30,
			0,
			0,
			static_cast<Shape>(Gosu::random(sI, sZ+1)),
			static_cast<Color>(Gosu::random(cBlue, cYellow+1)));

			int w = _nextTetramino->GetWidth();
			int h = _nextTetramino->GetHeight();

			// center next piece on preview pane
			_nextTetramino->SetOffsetXY(420 - w*30/2, 75 - h*30/2);

	} else {
		_tetramino->MoveDown();
	}
}

void GameWindow::draw()
{
	_tetramino->Draw();
	_nextTetramino->Draw();
	_board.Draw();
	_backgroundImage->draw(0, 0, zBackground);
}

void GameWindow::buttonDown(Gosu::Button btn)
{
	if (btn == Gosu::kbEscape)
		close();
}

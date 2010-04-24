#ifndef _GAMEWINDOW_H_
#define _GAMEWINDOW_H_

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <boost/scoped_ptr.hpp>

#include <cstdlib>
#include <list>
#include <vector>

#include "Config.h"
#include "Block.h"
#include "Board.h"

class GameWindow : public Gosu::Window
{
private:
	boost::scoped_ptr<Gosu::Image> _backgroundImage;
	Gosu::Font _font;
	Block _block;
	Board _board;
	Tetramino _tetramino;

public:
	GameWindow();

	void update();
	void draw();
	void buttonDown(Gosu::Button btn);
};

#endif

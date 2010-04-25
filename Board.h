#ifndef _BOARD_H_
#define _BOARD_H_

#include <Gosu/Gosu.hpp>

#include <boost/array.hpp>
#include <boost/scoped_ptr.hpp>

#include <list>
#include <vector>

#include "Config.h"
#include "Block.h"
//#include "Tetramino.h"

const int BOARD_WIDTH  = 10;
const int BOARD_HEIGHT = 15;

typedef boost::array<Color, BOARD_WIDTH> line;

class Tetramino;

class Board
{
private:
	int _w, _h;
	Block& _block;
	std::list<line> _lines;

public:
	explicit Board(Block& block, int w, int h);
	void Draw();
	Color GetCellColor(int posx, int posy) const;
	void CopyFromTetramino(Tetramino* tetramino);
	int GetWidth() const { return BOARD_WIDTH; }
	int GetHeight() const { return BOARD_HEIGHT; }
};

#endif

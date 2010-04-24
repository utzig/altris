// vim:ts=4

#include <Gosu/Gosu.hpp>

#include <boost/array.hpp>

#include <list>
#include <cstdio>

#include "Block.h"
#include "Board.h"

Board::Board(Block& block, int w, int h)
	: _block(block), _w(w), _h(h)
{
	line l;
	line::iterator lit;
	int i;

	for (lit = l.begin(); lit != l.end(); ++lit)
		*lit = cInvisible;

	for (i = 0; i < BOARD_HEIGHT; i++)
		_lines.push_back(l);
}

void Board::Draw()
{
	std::list<line>::const_iterator it;
	line::const_iterator lit;
	int i, j;

	for (it = _lines.begin(), i = 0; it != _lines.end(); ++it, ++i) {
		for (lit = it->begin(), j = 0; lit != it->end(); ++lit, ++j) {
			_block.Draw(j, i, *lit, zBoard);
		}
	}
}

#if 0
bool Board::CheckColision(Tetramino& t)
{

	return false;
}

void Board::AddTetramino(Tetramino& t)
{

}
#endif

// vim:ts=4

#include <Gosu/Gosu.hpp>

#include <boost/array.hpp>

#include <list>
#include <cstdio>

#include "Block.h"
#include "Board.h"
#include "Tetramino.h"

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
			_block.DrawRel(j, i, *lit, zBoard);
		}
	}
}

Color Board::GetCellColor(int posx, int posy) const
{
	std::list<line>::const_iterator it;

	it = _lines.begin();
	int i = 0;
	while (it != _lines.end() && posy != i) {
		++it;
		++i;
	}

	return (*it)[posx];
}

void Board::CopyFromTetramino(Tetramino* tetramino)
{
	int x = tetramino->GetXPos();
	int y = tetramino->GetYPos();
	int w = tetramino->GetWidth();
	int h = tetramino->GetHeight();

	int i, j;

	std::list<line>::iterator it = _lines.begin();
	i = 0;
	while (it != _lines.end() && y != i) {
		++it;
		++i;
	}

	Color color;

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			color = tetramino->GetCellColor(i, j);
			if (color != cInvisible) {
				(*it)[x+i] = color;
			}
		}
		++it;
	}
}

void Board::RemoveCompleteLines()
{
	std::list<line>::iterator it;
	int i;
	int n = 0;
	bool isComplete = false;

	for (it = _lines.begin(); it != _lines.end(); ) {
		for (i = 0, isComplete = true; i < (*it).size(); ++i) {
			if ((*it)[i] == cInvisible) {
				isComplete = false;
			}
		}

		if (isComplete) {
			it = _lines.erase(it);
			++n;
		} else {
			++it;
		}
	}

	line l;
	line::iterator lit;

	for (lit = l.begin(); lit != l.end(); ++lit)
		*lit = cInvisible;

	for (i = 0; i < n; i++)
		_lines.push_front(l);
}

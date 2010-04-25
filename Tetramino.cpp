// vim:ts=4

#include <Gosu/Gosu.hpp>

#include <cstdio>

#include "Config.h"
#include "Tetramino.h"
#include "Board.h"

Tetramino::Tetramino(Block& block, int x, int y, Shape shape, Color color)
	: _block(block), _absx(x), _absy(y)
{
	switch (shape) {
		case sI:
			_w = 1;
			_h = 4;
			memset(_data, cInvisible, sizeof(_data));
			_data[0][0] = color;
			_data[0][1] = color;
			_data[0][2] = color;
			_data[0][3] = color;
			break;
		case sL:
			_w = 2;
			_h = 3;
			memset(_data, cInvisible, sizeof(_data));
			_data[0][0] = color;
			_data[0][1] = color;
			_data[0][2] = color;
			_data[1][2] = color;
			break;
		case sJ:
			_w = 2;
			_h = 3;
			memset(_data, cInvisible, sizeof(_data));
			_data[1][0] = color;
			_data[1][1] = color;
			_data[1][2] = color;
			_data[0][2] = color;
			break;
		case sT:
			_w = 3;
			_h = 2;
			memset(_data, cInvisible, sizeof(_data));
			_data[0][0] = color;
			_data[1][0] = color;
			_data[2][0] = color;
			_data[1][1] = color;
			break;
		case sO:
			_w = 2;
			_h = 2;
			memset(_data, cInvisible, sizeof(_data));
			_data[0][0] = color;
			_data[1][0] = color;
			_data[0][1] = color;
			_data[1][1] = color;
			break;
		case sS:
			_w = 3;
			_h = 2;
			memset(_data, cInvisible, sizeof(_data));
			_data[1][0] = color;
			_data[2][0] = color;
			_data[0][1] = color;
			_data[1][1] = color;
			break;
		case sZ:
			_w = 3;
			_h = 2;
			memset(_data, cInvisible, sizeof(_data));
			_data[0][0] = color;
			_data[1][0] = color;
			_data[1][1] = color;
			_data[2][1] = color;
			break;
	}
}

void Tetramino::Draw()
{
	int i, j;
	int w = _block.GetWidth();
	int h = _block.GetHeight();

	for (i = 0; i < _w; i++) {
		for (j = 0; j < _h; j++) {
			_block.DrawAbs(_absx + (i*w), _absy + (j*h), _data[i][j], zTetramino);
		}
	}
}

void Tetramino::MoveLeft()
{
	int w = _block.GetWidth();

	if (_absx > 0) _absx -= w;
}

void Tetramino::MoveRight()
{
	int w = _block.GetWidth();

	if ((_absx + (_w*w)) < (w * 10)) _absx += w;
}

void Tetramino::MoveDown()
{
	int h = _block.GetHeight();

	if ((_absy + (_h*h))  < (h * 15)) ++_absy;
}

void Tetramino::Rotate()
{
	Color t;

	t = _data[1][1];
	_data[1][1] = _data[1][2];
	_data[1][2] = _data[2][2];
	_data[2][2] = _data[2][1];
	_data[2][1] = t;

	t = _data[0][0];
	_data[0][0] = _data[0][3];
	_data[0][3] = _data[3][3];
	_data[3][3] = _data[3][0];
	_data[3][0] = t;

	t = _data[1][0];
	_data[1][0] = _data[0][2];
	_data[0][2] = _data[2][3];
	_data[2][3] = _data[3][1];
	_data[3][1] = t;

	t = _data[2][0];
	_data[2][0] = _data[0][1];
	_data[0][1] = _data[1][3];
	_data[1][3] = _data[3][2];
	_data[3][2] = t;

	int w = _h;
	int h = _w;

	int first_x = 0, first_y = 0;
	bool found = false;

	// fix position
	for (int i = 0, found = false; i < 4; i++) {
		for (int j = 0; j < 4 && !found; j++) {
			if (_data[i][j] != cInvisible) {
				found = true;
				first_x = i;
				break;
			}
		}
	}

	for (int i = 0, found = false; i < 4 && !found; i++) {
		for (int j = 0; j < 4; j++) {
			if (_data[j][i] != cInvisible) {
				found = true;
				first_y = i;
				break;
			}
		}
	}

	if (first_x != 0) {
		for (int i = first_x; i < (first_x + w); i++) {
			for (int j = 0; j < 4; j++) {
				_data[i - first_x][j] = _data[i][j];
			}
		}

		for (int i = w; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				_data[i][j] = cInvisible;
			}
		}

		for (int i = h; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				_data[j][i] = cInvisible;
			}
		}
	}

	if (first_y != 0) {
		for (int i = first_y; i < (first_y + h); i++) {
			for (int j = 0; j < 4; j++) {
				_data[j][i - first_y] = _data[j][i];
			}
		}

		for (int i = w; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				_data[i][j] = cInvisible;
			}
		}

		for (int i = h; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				_data[j][i] = cInvisible;
			}
		}
	}

	_w = w;
	_h = h;
}

bool Tetramino::CheckCollisionWithBoard(Board& board)
{
	int posx = 0, posy = 0;
	int x, y;

	// not arrived at block boundary yet
	if (_absy % 30) return false;

	// initial cell position of the tetramino
	posx = _absx / 30;
	posy = _absy / 30;

	for (x = posx; x < (posx + _w); ++x) {
		for (y = (posy + _h); y >= posy; --y) {
			if (_data[x - posx][y - posy] == cInvisible) continue;
			else {
				if ((y == 15) || (board.GetCellColor(x, y+1) != cInvisible))
					return true;
				else
					break;
			}
		}
	}

	return false;
}

Color Tetramino::GetCellColor(int posx, int posy) const
{
	return _data[posx][posy];
}


// vim:ts=4

#include <Gosu/Gosu.hpp>

#include "Config.h"
#include "Tetramino.h"

Tetramino::Tetramino(Block& block, int x, int y, Shape shape, Color color)
	: _block(block), _posx(x), _posy(y)
{
	switch (shape) {
		case sI:
			_w = 1;
			_h = 4;
			memset(_data, cInvisible, sizeof(_data));
			_data[0][0] = color;
			_data[1][0] = color;
			_data[2][0] = color;
			_data[3][0] = color;
			break;
		case sL:
			_w = 2;
			_h = 3;
			memset(_data, cInvisible, sizeof(_data));
			_data[0][0] = color;
			_data[1][0] = color;
			_data[2][0] = color;
			_data[0][1] = color;
			break;
		case sJ:
			_w = 2;
			_h = 3;
			memset(_data, cInvisible, sizeof(_data));
			_data[0][1] = color;
			_data[1][1] = color;
			_data[2][1] = color;
			_data[2][0] = color;
			break;
		case sT:
			_w = 3;
			_h = 2;
			memset(_data, cInvisible, sizeof(_data));
			_data[0][0] = color;
			_data[0][1] = color;
			_data[0][2] = color;
			_data[1][2] = color;
			break;
		case sO:
			_w = 2;
			_h = 2;
			memset(_data, cInvisible, sizeof(_data));
			_data[0][0] = color;
			_data[0][1] = color;
			_data[1][0] = color;
			_data[1][1] = color;
			break;
		case sS:
			_w = 3;
			_h = 2;
			memset(_data, cInvisible, sizeof(_data));
			_data[0][1] = color;
			_data[0][2] = color;
			_data[1][0] = color;
			_data[1][1] = color;
			break;
		case sZ:
			_w = 3;
			_h = 2;
			memset(_data, cInvisible, sizeof(_data));
			_data[0][0] = color;
			_data[0][1] = color;
			_data[1][1] = color;
			_data[1][2] = color;
			break;
	}
}

void Tetramino::Draw()
{
	int i, j;

	for (i = 0; i < _h; i++) {
		for (j = 0; j < _w; j++) {
			_block.Draw(_posx + j, _posy + i, _data[i][j], zTetramino);
		}
	}
}

void Tetramino::MoveLeft()
{
	if (_posx > 0) --_posx;
}

void Tetramino::MoveRight()
{
	if ((_posx + _w) < 10) ++_posx;
}

void Tetramino::MoveDown()
{
	if ((_posy + _h) < 15) ++_posy;
}

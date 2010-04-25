#ifndef _TETRAMINO_H_
#define _TETRAMINO_H_

#include <Gosu/Gosu.hpp>

#include "Config.h"
#include "Board.h"
#include "Block.h"

class Tetramino {
private:
	int _offx, _offy;
	int _absx, _absy;
	int _w, _h;
	Color _data[4][4];
	Block& _block;
	bool downPressed;

public:
	explicit Tetramino(Block& block, int offx, int offy, int x, int y, Shape shape, Color color);
	void Draw();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();
	int GetWidth() const { return _w; }
	int GetHeight() const { return _h; }
	int GetXPos() const { return _absx / 30; }
	int GetYPos() const { return _absy / 30; }
	void SetOffsetXY(int x, int y) { _offx = x; _offy = y; }
	bool CheckForLeftCollision(Board& board);
	bool CheckForRightCollision(Board& board);
	bool CheckForDownCollision(Board& board);
	void DownPressed() { downPressed = true; }
	Color GetCellColor(int posx, int posy) const;
};

#endif

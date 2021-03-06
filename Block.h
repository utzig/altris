// vim:ts=4

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <Gosu/Gosu.hpp>

#include <boost/scoped_ptr.hpp>

#include "Config.h"

class Block
{
private:
	int _w, _h;
	boost::scoped_ptr<Gosu::Image> _BlueImage;
	boost::scoped_ptr<Gosu::Image> _GreenImage;
	boost::scoped_ptr<Gosu::Image> _PinkImage;
	boost::scoped_ptr<Gosu::Image> _RedImage;
	boost::scoped_ptr<Gosu::Image> _YellowImage;

public:
	Block(Gosu::Graphics& g, int w, int h);
	int GetWidth() const { return _w; }
	int GetHeight() const { return _h; }
	void Draw(int xabs, int yabs, Color color, ZOrder z);
};

#endif

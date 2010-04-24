#include <Gosu/Gosu.hpp>

#include <boost/scoped_ptr.hpp>

#include "Config.h"
#include "Block.h"

Block::Block(Gosu::Graphics& g, int x, int y, int w, int h)
	: _x(x), _y(y), _w(w), _h(h)
{
	std::wstring filename = Gosu::sharedResourcePrefix() + L"media/blue.png";
	_BlueImage.reset(new Gosu::Image(g, filename));

	filename = Gosu::sharedResourcePrefix() + L"media/green.png";
	_GreenImage.reset(new Gosu::Image(g, filename));

	filename = Gosu::sharedResourcePrefix() + L"media/pink.png";
	_PinkImage.reset(new Gosu::Image(g, filename));

	filename = Gosu::sharedResourcePrefix() + L"media/red.png";
	_RedImage.reset(new Gosu::Image(g, filename));

	filename = Gosu::sharedResourcePrefix() + L"media/yellow.png";
	_YellowImage.reset(new Gosu::Image(g, filename));
}

void Block::Draw(int xpos, int ypos, Color color, ZOrder z)
{
	int x = _x + (xpos * 30);
	int y = _y + (ypos * 30);
	switch (color) {
		case cBlue:
			_BlueImage->draw(x, y, z);
			break;
		case cGreen:
			_GreenImage->draw(x, y, z);
			break;
		case cPink:
			_PinkImage->draw(x, y, z);
			break;
		case cRed:
			_RedImage->draw(x, y, z);
			break;
		case cYellow:
			_YellowImage->draw(x, y, z);
			break;
	}
}

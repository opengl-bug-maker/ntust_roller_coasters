#include "SupportStructure.h"

void SupportStructure::GLDraw()
{
}

SupportStructure::SupportStructure(const Pnt3f& pos, const Pnt3f& size, const Pnt3f& front, const Pnt3f& top, GLubyte* color)
{
	Children.push_back(new Cuboid(
		Pnt3f(0, 0, 0),
		Pnt3f(1, 1, 1),
		Pnt3f(1, 0, 0),
		Pnt3f(0, 1, 0),
		color
	)
	);
}

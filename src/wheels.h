#include "Obj/Obj.h"
class Wheel : public Obj {
private:
	void GLDraw() override;
public:
	Wheel(const Pnt3f& pos, const Pnt3f& size, const Pnt3f& front, const Pnt3f& top, GLubyte* color);
};

#include "Obj/Obj.h"
#include "Obj/Cuboid.h"
class SupportStructure : public Obj {
private:
	void GLDraw() override;
public:
	SupportStructure(const Pnt3f& pos, const Pnt3f& size, const Pnt3f& front, const Pnt3f& top, GLubyte* color);
};

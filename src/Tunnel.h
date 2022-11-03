#include "Obj/Obj.h"
class Tunnel : public Obj {
private:
	void GLDraw() override;
public:
	Tunnel(const Pnt3f& pos, float w, float h);
};

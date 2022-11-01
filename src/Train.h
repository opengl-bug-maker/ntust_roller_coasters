#include "Obj/Obj.h"
class Train : public Obj {
public:
	Train();
	Train(GLubyte* color);
private:
	void GLDraw() override;
};

class Car : public Obj {
public:
	Car();
	Car(GLubyte* color);
private:
	void GLDraw() override;
};
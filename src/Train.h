#include "Obj/Obj.h"
class Train : public Obj {
public:
	Train();
	Train(GLubyte* color);
    void setWheels(float length);
private:
	void GLDraw() override;
};

class Car : public Obj {
public:
	Car();
	Car(GLubyte* color);
    void setWheels(float length);
private:
	void GLDraw() override {};
};
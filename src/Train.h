#include "Obj/Obj.h"
class Train : public Obj {
public:
	Train();
	Train(GLubyte* color);
    void setWheels(float length);
private:
	void GLDraw() override;

    void setWheels();
};

class Car : public Obj {
public:
	Car();
	Car(GLubyte* color);
private:
	void GLDraw() override {};
};
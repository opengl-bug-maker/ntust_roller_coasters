#include "Obj/Obj.h"
class Train : public Obj {
public:
	Train();
	Train(GLubyte* color);
    void setWheels(float length);

    void init() override;

private:
	void GLDraw() override;
    GLubyte wheels_color[3] = {200, 200, 10};
    GLubyte body_color[3] = {233, 29, 45};
    GLubyte cockpit_color[3] = {117, 206, 219};
    GLubyte ceil_color[3] = { 233, 29, 45 };
    GLubyte chimney_color[3] = { 233, 29, 45 };

};

class Car : public Obj {
public:
	Car();
	Car(GLubyte* color);
    void setWheels(float length);
private:
	void GLDraw() override {};
    GLubyte wheels_color[3] = {200,200,10};
};
};
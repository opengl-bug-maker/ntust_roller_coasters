#include "Obj/Obj.h"
class Smoke : public Obj {
public:
    float startTick;
	Smoke();

    explicit Smoke(float startTick);

    float getStartTick() const;

    void init() override;

private:
	void GLDraw() override;
};

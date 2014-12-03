#ifndef  CC_JUMP_BY_3D_H
#define  CC_JUMP_BY_3D_H 
#include "cocos2d.h"
namespace cocos2d{


/** @brief Moves a Node object simulating a parabolic jump movement by modifying it's position attribute.
*/
class  JumpBy3D : public ActionInterval
{
public:
    /** creates the action */
    static JumpBy3D* create(float duration, const Vec3& position, float height, int jumps);

    //
    // Overrides
    //
    virtual JumpBy3D* clone() const override;
    virtual JumpBy3D* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
    JumpBy3D() {}
    virtual ~JumpBy3D() {}

    /** initializes the action */
    bool initWithDuration(float duration, const Vec3& position, float height, int jumps);

protected:
    Vec3           _startPosition;
    Vec3           _delta;
    float           _height;
    int             _jumps;
    Vec3           _previousPos;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(JumpBy3D);
};

}

#endif // ! CC_JUMP_BY_3D_H

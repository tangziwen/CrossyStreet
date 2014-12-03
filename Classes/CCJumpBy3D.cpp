#include "CCJumpBy3D.h"

namespace cocos2d {


    JumpBy3D* JumpBy3D::create(float duration, const Vec3& position, float height, int jumps)
    {
        JumpBy3D *jumpBy = new (std::nothrow) JumpBy3D();
        jumpBy->initWithDuration(duration, position, height, jumps);
        jumpBy->autorelease();

        return jumpBy;
    }

    JumpBy3D* JumpBy3D::clone() const 
    {
        // no copy constructor
        auto a = new (std::nothrow) JumpBy3D();
        a->initWithDuration(_duration, _delta, _height, _jumps);
        a->autorelease();
        return a;
    }

    JumpBy3D* JumpBy3D::reverse(void) const 
    {
        return JumpBy3D::create(_duration, Vec3(-_delta.x, -_delta.y,-_delta.z),
            _height, _jumps);
    }

    void JumpBy3D::startWithTarget(Node *target)
    {
        ActionInterval::startWithTarget(target);
        _previousPos = _startPosition = target->getPosition3D();
    }

    void JumpBy3D::update(float t)
    {
        // parabolic jump (since v0.8.2)
        if (_target)
        {
            float frac = fmodf( t * _jumps, 1.0f );
            float y = _height * 4 * frac * (1 - frac);
            y += _delta.y * t;

            float x = _delta.x * t;
            float z = _delta.z * t;
#if CC_ENABLE_STACKABLE_ACTIONS
            Vec3 currentPos = _target->getPosition3D();

            Vec3 diff = currentPos - _previousPos;
            _startPosition = diff + _startPosition;

            Vec3 newPos = _startPosition + Vec3(x,y,z);
            _target->setPosition3D(newPos);

            _previousPos = newPos;
#else
            _target->setPosition(_startPosition + Vec3(x,y,z));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
        }
    }

    bool JumpBy3D::initWithDuration(float duration, const Vec3& position, float height, int jumps)
    {
        CCASSERT(jumps>=0, "Number of jumps must be >= 0");

        if (ActionInterval::initWithDuration(duration) && jumps>=0)
        {
            _delta = position;
            _height = height;
            _jumps = jumps;

            return true;
        }

        return false;
    }
}
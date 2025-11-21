// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#include "objects/object.h"

#include "universe.h"
#include "vector.h"
#include <string>

[[nodiscard]] double Object::getMass() const noexcept
{
    return mass;
}

[[nodiscard]] std::string Object::getName() const noexcept
{
    return name;
}

[[nodiscard]] Vector2 Object::getPosition() const noexcept
{
    return position;
}

[[nodiscard]] Vector2 Object::getVelocity() const noexcept
{
    return velocity;
}

[[nodiscard]] Vector2 Object::getForce(const Object& rhs) const noexcept
{
    if (rhs.getPosition() == position) {
        return Vector2();
    }
    Vector2 distanceVec = rhs.position - position;
    double disSq = distanceVec.normSq();
    auto force = Universe::G * mass * rhs.mass / disSq;
    auto direct = distanceVec.normalize();
    return force * direct;
}

void Object::setPosition(const Vector2& pos)
{
    position = pos;
}

void Object::setVelocity(const Vector2& vel)
{
    velocity = vel;
}

bool Object::operator==(const Object& rhs) const
{
    if (name == rhs.name && mass == rhs.mass && position == rhs.position
        && velocity == rhs.velocity)
        return true;
    return false;
}

bool Object::operator!=(const Object& rhs) const
{
    return !(*this == rhs);
}

Object::Object(const std::string& name, double mass, const Vector2& pos, const Vector2& vel)
    : name(name)
    , mass(mass)
    , position(pos)
    , velocity(vel)
{
}

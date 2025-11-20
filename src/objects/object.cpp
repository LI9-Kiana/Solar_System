#include "objects/object.h"

#include "universe.h"
#include "vector.h"
#include <string>
// Default destructor

// Copy and assignment not allowed

/**
 * An entry point for visitors
 * @param visitor - visitor to be accepted
 */
// void accept(Visitor& visitor) = 0;

/**
 * Returns a dynamically allocated deep copy of this object
 * @return deep copy of the object
 */
//[[nodiscard]] virtual Object* clone() const = 0;

/**
 * Returns the mass
 * @return mass of the object
 */
[[nodiscard]] double Object::getMass() const noexcept
{
    return mass;
}

/**
 * Returns the name
 * @return name of the object
 */
[[nodiscard]] std::string Object::getName() const noexcept
{
    return name;
}

/**
 * Returns the position vector
 * @return position of the object
 */
[[nodiscard]] Vector2 Object::getPosition() const noexcept
{
    return position;
}

/**
 * Returns the velocity vector
 * @return velocity of the object
 */
[[nodiscard]] Vector2 Object::getVelocity() const noexcept
{
    return velocity;
}

/**
 * Calculates the force vector between lhs and rhs. The direction of the
 * result is as experienced by lhs. Negate the result to obtain force
 * experienced by rhs
 * @param rhs - other object to have force calculated against
 * @return force vector between objects
 */
[[nodiscard]] Vector2 Object::getForce(const Object& rhs) const noexcept
{
    Vector2 distanceVec = rhs.position - position;
    double disSq = distanceVec.normSq();
    auto force = Universe::G * mass * rhs.mass / disSq;
    auto direct = distanceVec.normalize();
    return force * direct;
}

/**
 * Sets the position vector
 * @param pos - new position
 */
void Object::setPosition(const Vector2& pos)
{
    position = pos;
}

/**
 * Sets the velocity vector
 * @param vel - new velocity
 */
void Object::setVelocity(const Vector2& vel)
{
    velocity = vel;
}

/**
 * Returns true if this object is member-wise equal to rhs
 * @param rhs - object to compare against
 * @return true if objects are equivalent (name, mass, pos, vel)
 */
bool Object::operator==(const Object& rhs) const
{
    if (name == rhs.name && mass == rhs.mass && position == rhs.position
        && velocity == rhs.velocity)
        return true;
    return false;
}

/**
 * Returns !(*this == rhs).
 */
bool Object::operator!=(const Object& rhs) const
{
    return !(*this == rhs);
}

/**
 * Initializes an object with the provided properties - really only called by
 * derived classes
 * @param name - name of the object
 * @param mass - mass of the object
 * @param pos - position vector
 * @param vel - velocity vector
 */
Object::Object(const std::string& name, double mass, const Vector2& pos, const Vector2& vel)
    : name(name)
    , mass(mass)
    , position(pos)
    , velocity(vel)
{
}

// std::string name; // Name of the object.
// double mass; // Mass of the object in kilograms.
// Vector2 position; // Position vector of the object in meters.
// Vector2 velocity; // Velocity vector of the object in meters/second.

// @author G. Hemingway, copyright 2025 - All rights reserved

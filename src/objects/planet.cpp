// @author G. Hemingway, copyright 2025 - All rights reserved
#include "objects/planet.h"
#include "visitors/print.h"

/**
 * Represents a free-floating object in the universe
 */

/**
 * An entry point for visitors
 * @param visitor - visitor to be accepted
 */
void Planet::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

/**
 * Returns a dynamically allocated deep copy of this object
 * @return deep copy of the object
 */
[[nodiscard]] Planet* Planet::clone() const
{
    Planet* temp = new Planet(name, mass, position, velocity);
    return temp;
}

/**
 * Initializes a planet with the provided properties - really only called by
 * the ObjectFactory
 * @param name - name of the object
 * @param mass - mass of the object
 * @param pos - position vector
 * @param vel - velocity vector
 */
Planet::Planet(const std::string& name, double mass, const Vector2& pos, const Vector2& vel)
    : Object::Object(name, mass, pos, vel)
{
}
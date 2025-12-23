// @author G. Hemingway, copyright 2025 - All rights reserved
#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"
#include <string>

class Visitor;
class ObjectFactory;

/**
 *  Representation of objects suitable for use in the simulated universe
 */
class Object {
public:
    // Default destructor
    virtual ~Object() = default;
    // Copy and assignment not allowed
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

    /**
     * An entry point for visitors
     * @param visitor - visitor to be accepted
     */
    virtual void accept(Visitor& visitor) = 0;

    /**
     * Returns a dynamically allocated deep copy of this object
     * @return deep copy of the object
     */
    [[nodiscard]] virtual Object* clone() const = 0;

    /**
     * Returns the mass
     * @return mass of the object
     */
    [[nodiscard]] virtual double getMass() const noexcept;

    /**
     * Returns the name
     * @return name of the object
     */
    [[nodiscard]] virtual std::string getName() const noexcept;

    /**
     * Returns the position vector
     * @return position of the object
     */
    [[nodiscard]] virtual Vector2 getPosition() const noexcept;

    /**
     * Returns the velocity vector
     * @return velocity of the object
     */
    [[nodiscard]] virtual Vector2 getVelocity() const noexcept;

    /**
     * Calculates the force vector between lhs and rhs. The direction of the
     * result is as experienced by lhs. Negate the result to obtain force
     * experienced by rhs
     * @param rhs - other object to have force calculated against
     * @return force vector between objects
     */
    [[nodiscard]] virtual Vector2 getForce(const Object& rhs) const noexcept;

    /**
     * Sets the position vector
     * @param pos - new position
     */
    virtual void setPosition(const Vector2& pos);

    /**
     * Sets the velocity vector
     * @param vel - new velocity
     */
    virtual void setVelocity(const Vector2& vel);

    /**
     * Returns true if this object is member-wise equal to rhs
     * @param rhs - object to compare against
     * @return true if objects are equivalent (name, mass, pos, vel)
     */
    virtual bool operator==(const Object& rhs) const;

    /**
     * Returns !(*this == rhs).
     */
    virtual bool operator!=(const Object& rhs) const;

protected:
    /**
     * Initializes an object with the provided properties - really only called by
     * derived classes
     * @param name - name of the object
     * @param mass - mass of the object
     * @param pos - position vector
     * @param vel - velocity vector
     */
    Object(const std::string& name, double mass, const Vector2& pos, const Vector2& vel);

    std::string name; // Name of the object.
    double mass; // Mass of the object in kilograms.
    Vector2 position; // Position vector of the object in meters.
    Vector2 velocity; // Velocity vector of the object in meters/second.
};

#endif // OBJECT_H

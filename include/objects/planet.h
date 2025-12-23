// @author G. Hemingway, copyright 2025 - All rights reserved
#ifndef PLANET_H
#define PLANET_H

#include "./object.h"

/**
 * Represents a free-floating object in the universe
 */
class Planet : public Object {
public:
    // Default destructor
    ~Planet() override = default;
    // Copy and assignment not allowed
    Planet(const Planet&) = delete;
    Planet& operator=(const Planet&) = delete;

    /**
     * An entry point for visitors
     * @param visitor - visitor to be accepted
     */
    void accept(Visitor& visitor) override;

    /**
     * Returns a dynamically allocated deep copy of this object
     * @return deep copy of the object
     */
    [[nodiscard]] Planet* clone() const override;

private:
    friend class ObjectFactory;

    /**
     * Initializes a planet with the provided properties - really only called by
     * the ObjectFactory
     * @param name - name of the object
     * @param mass - mass of the object
     * @param pos - position vector
     * @param vel - velocity vector
     */
    Planet(const std::string& name, double mass, const Vector2& pos, const Vector2& vel);
};

#endif // PLANET_H

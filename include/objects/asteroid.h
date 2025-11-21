//
// Created by zhuct on 11/20/2025.
//
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#ifndef ASSIGNMENT6_ASTEROID_H
#define ASSIGNMENT6_ASTEROID_H
#include "./object.h"

/**
 * Represents a free-floating object in the universe
 */
class Asteroid : public Object {
public:
    // Default destructor
    ~Asteroid() override = default;
    // Copy and assignment not allowed
    Asteroid(const Asteroid&) = delete;
    Asteroid& operator=(const Asteroid&) = delete;

    /**
     * An entry point for visitors
     * @param visitor - visitor to be accepted
     */
    void accept(Visitor& visitor) override;

    /**
     * Returns a dynamically allocated deep copy of this object
     * @return deep copy of the object
     */
    [[nodiscard]] Asteroid* clone() const override;

private:
    friend class ObjectFactory;

    /**
     * Initializes an asteroid with the provided properties - really only called by
     * the ObjectFactory
     * @param name - name of the object
     * @param mass - mass of the object
     * @param pos - position vector
     * @param vel - velocity vector
     */
    Asteroid(const std::string& name, double mass, const Vector2& pos, const Vector2& vel);
};

#endif // ASSIGNMENT6_ASTEROID_H

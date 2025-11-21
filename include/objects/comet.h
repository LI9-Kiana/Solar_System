//
// Created by zhuct on 11/20/2025.
//
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#ifndef ASSIGNMENT6_COMET_H
#define ASSIGNMENT6_COMET_H

#include "./object.h"

/**
 * Represents a free-floating object in the universe
 */
class Comet : public Object {
public:
    // Default destructor
    ~Comet() override = default;
    // Copy and assignment not allowed
    Comet(const Comet&) = delete;
    Comet& operator=(const Comet&) = delete;

    /**
     * An entry point for visitors
     * @param visitor - visitor to be accepted
     */
    void accept(Visitor& visitor) override;

    /**
     * Returns a dynamically allocated deep copy of this object
     * @return deep copy of the object
     */
    [[nodiscard]] Comet* clone() const override;

    /**
     * Return the composition of the comet
     */
    [[nodiscard]] std::string getComposition() const noexcept;

private:
    friend class ObjectFactory;

    /**
     * Initializes a planet with the provided properties - really only called by
     * the ObjectFactory
     * @param name - name of the object
     * @param mass - mass of the object
     * @param pos - position vector
     * @param vel - velocity vector
     * @param comp - comet composition
     */
    Comet(const std::string& name, double mass, const Vector2& pos, const Vector2& vel,
        const std::string& comp);
    /**
     * Check whether string is valid as composition input
     * @param comp - string to be checked
     */
    std::string validateComposition(const std::string& comp);

    std::string composition;
};

#endif // ASSIGNMENT6_COMET_H

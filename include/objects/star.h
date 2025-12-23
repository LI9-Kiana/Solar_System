// @author G. Hemingway, copyright 2025 - All rights reserved
#ifndef STAR_H
#define STAR_H

#include "./object.h"

/**
 * Represents an object that is anchored at the center of the universe
 */
class Star : public Object {
public:
    // Default destructor
    ~Star() override = default;
    // Copy and assignment not allowed
    Star(const Star&) = delete;
    Star& operator=(const Star&) = delete;

    /**
     * An entry point for visitors
     * @param visitor - visitor to be accepted
     */
    void accept(Visitor& visitor) override;

    /**
     * Returns a dynamically allocated deep copy of this object
     * @return deep copy of the object
     */
    [[nodiscard]] Star* clone() const override;

private:
    friend class ObjectFactory;

    /**
     * Initializes a star with the provided properties - really only called by
     * the ObjectFactory
     * @param name - name of the object
     * @param mass - mass of the object
     */
    Star(const std::string& name, double mass);
};

#endif // STAR_H

// @author G. Hemingway, copyright 2025 - All rights reserved
#ifndef VISITOR_H
#define VISITOR_H

class Planet;
class Star;

/**
 *  Abstract base class for the Visitor pattern.
 */
class Visitor {
public:
    // Default constructor
    Visitor() = default;

    /**
     * Pure virtual destructor. A necessary no-op since this is a base class.
     */
    virtual ~Visitor() = default;

    /**
     * Prints the planet's name
     * @param planet - to be printed
     */
    virtual void visit(const Planet& planet) const = 0;

    /**
     * Prints the star's name
     * @param star - to be printed
     */
    virtual void visit(const Star& star) const = 0;
};

#endif // VISITOR_H

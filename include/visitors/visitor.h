// @author G. Hemingway, copyright 2025 - All rights reserved
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#ifndef VISITOR_H
#define VISITOR_H

class Planet;
class Star;
class Asteroid;
class Comet;

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

    /**
     * Prints the star's name
     * @param ast - to be printed
     */
    virtual void visit(const Asteroid& ast) const = 0;
    /**
     * Prints the star's name
     * @param comet - to be printed
     */
    virtual void visit(const Comet& comet) const = 0;
};

#endif // VISITOR_H

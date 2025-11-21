// @author G. Hemingway, copyright 2025 - All rights reserved
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#ifndef PRINT_H
#define PRINT_H

#include "objects/asteroid.h"
#include "objects/comet.h"
#include "visitor.h"

#include <ostream>

/**
 *  A visitor that accepts an ostream reference during construction. Its visit
 *  method simply prints out the object's name.
 */
class PrintVisitor : public Visitor {
public:
    /**
     * Construct a visitor that prints to the provided ostream
     * @param os - stream to print to
     */
    explicit PrintVisitor(std::ostream& os);

    /**
     * Prints the planet's name
     * @param planet - to be printed
     */
    void visit(const Planet& planet) const override;

    /**
     * Prints the star's name
     * @param star - to be printed
     */
    void visit(const Star& star) const override;

    /**
     * Prints the asteroid's name
     * @param asteroid - to be printed
     */
    void visit(const Asteroid& asteroid) const override;
    /**
     * Prints the comet's name
     * @param comet - to be printed
     */
    void visit(const Comet& comet) const override;

private:
    std::ostream& os; // Reference to the ostream for printing
};

#endif // PRINT_H

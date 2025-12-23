// @author G. Hemingway, copyright 2025 - All rights reserved
#ifndef PRINT_H
#define PRINT_H

#include "visitor.h"
#include <ostream>

/**
 *  A visitor that accepts an ostream reference during construction. Its visit
 *  method simply prints out the object's name.
 */
class PrintVisitor final : public Visitor {
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

private:
    std::ostream& os; // Reference to the ostream for printing
};

#endif // PRINT_H

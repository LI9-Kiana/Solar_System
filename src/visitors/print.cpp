// @author G. Hemingway, copyright 2025 - All rights reserved
#include "visitors/print.h"

#include "objects/planet.h"
#include "objects/star.h"

/**
 *  A visitor that accepts an ostream reference during construction. Its visit
 *  method simply prints out the object's name.
 */



    /**
     * Construct a visitor that prints to the provided ostream
     * @param os - stream to print to
     */
    PrintVisitor::PrintVisitor(std::ostream& os):os(os)
    {}


    /**
     * Prints the planet's name
     * @param planet - to be printed
     */
    void PrintVisitor::visit(const Planet& planet) const
    {
        const auto& pos = planet.getPosition();
        const auto& vel = planet.getVelocity();

        os << "Planet: "
           << planet.getName() << ' '
           << planet.getMass() << "kg "
           << '[' << pos[0] << ' ' << pos[1] << ']'
           << '[' << vel[0] << ' ' << vel[1] << ']'
           << '\n';
    }

    /**
     * Prints the star's name
     * @param star - to be printed
     */
    void PrintVisitor::visit(const Star& star) const
    {
        os << "Star: "
        << star.getName() << ' '
        << star.getMass() << "kg\n";
    }



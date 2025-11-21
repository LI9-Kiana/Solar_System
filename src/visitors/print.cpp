// @author G. Hemingway, copyright 2025 - All rights reserved
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#include "visitors/print.h"

#include "objects/asteroid.h"
#include "objects/comet.h"
#include "objects/planet.h"
#include "objects/star.h"

PrintVisitor::PrintVisitor(std::ostream& os)
    : os(os)
{
}

void PrintVisitor::visit(const Planet& planet) const
{
    const auto& pos = planet.getPosition();
    const auto& vel = planet.getVelocity();

    os << "Planet: " << planet.getName() << ' ' << planet.getMass() << "kg " << '[' << pos[0] << ' '
       << pos[1] << ']' << '[' << vel[0] << ' ' << vel[1] << ']' << '\n';
}

void PrintVisitor::visit(const Star& star) const
{
    os << "Star: " << star.getName() << ' ' << star.getMass() << "kg\n";
}

void PrintVisitor::visit(const Asteroid& ast) const
{
    const auto& pos = ast.getPosition();
    const auto& vel = ast.getVelocity();

    os << "Asteroid: " << ast.getName() << ' ' << ast.getMass() << "kg " << '[' << pos[0] << ' '
       << pos[1] << ']' << '[' << vel[0] << ' ' << vel[1] << ']' << '\n';
}

void PrintVisitor::visit(const Comet& comet) const
{
    const auto& pos = comet.getPosition();
    const auto& vel = comet.getVelocity();

    os << "Comet: " << comet.getName() << ' ' << comet.getMass() << "kg " << '[' << pos[0] << ' '
       << pos[1] << ']' << '[' << vel[0] << ' ' << vel[1] << ']' << ' ' << comet.getComposition()
       << '\n';
}
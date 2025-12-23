// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#include "objects/planet.h"
#include "visitors/print.h"

void Planet::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

[[nodiscard]] Planet* Planet::clone() const
{
    Planet* temp = new Planet(name, mass, position, velocity);
    return temp;
}

Planet::Planet(const std::string& name, double mass, const Vector2& pos, const Vector2& vel)
    : Object::Object(name, mass, pos, vel)
{
}
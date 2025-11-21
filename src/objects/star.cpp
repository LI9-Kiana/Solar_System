// @author G. Hemingway, copyright 2025 - All rights reserved
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
/**
 * An entry point for visitors
 * @param visitor - visitor to be accepted
 */
#include "objects/star.h"
#include "visitors/print.h"

void Star::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

[[nodiscard]] Star* Star::clone() const
{
    Star* temp = new Star(name, mass);
    return temp;
}

Star::Star(const std::string& name, double mass)
    : Object::Object(name, mass, Vector2(), Vector2())
{
}
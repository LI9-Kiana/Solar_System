//
// Created by zhuct on 11/20/2025.
//
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#include "objects/asteroid.h"
#include "visitors/print.h"

void Asteroid::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

[[nodiscard]] Asteroid* Asteroid::clone() const
{
    Asteroid* temp = new Asteroid(name, mass, position, velocity);
    return temp;
}

Asteroid::Asteroid(const std::string& name, double mass, const Vector2& pos, const Vector2& vel)
    : Object::Object(name, mass, pos, vel)
{
}
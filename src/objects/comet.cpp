// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#include "objects/comet.h"
#include "visitors/print.h"

void Comet::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

[[nodiscard]] Comet* Comet::clone() const
{
    Comet* temp = new Comet(name, mass, position, velocity, composition);
    return temp;
}

[[nodiscard]] std::string Comet::getComposition() const noexcept
{
    return composition;
}

Comet::Comet(const std::string& name, double mass, const Vector2& pos, const Vector2& vel,
    const std::string& comp)
    : Object(name, mass, pos, vel)
    , composition(validateComposition(comp))
{
}

std::string Comet::validateComposition(const std::string& comp)
{
    if (comp == "ice" || comp == "dust" || comp == "rock") {
        return comp;
    }
    throw std::logic_error("Invalid composition: " + comp);
}

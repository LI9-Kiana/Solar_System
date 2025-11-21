// @author G. Hemingway, copyright 2025 - All rights reserved
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#include "objects/object_factory.h"
#include "vector.h"

#include "objects/asteroid.h"
#include "objects/comet.h"
#include "objects/planet.h"
#include "objects/star.h"
#include "universe.h"

#include <memory>

class Object;
class Planet;
class Star;

Planet* ObjectFactory::makePlanet(
    const std::string& name, double mass, const Vector2& pos, const Vector2& vel)
{
    checkMass(mass, 1e21);

    Planet* raw = new Planet(name, mass, pos, vel);
    std::unique_ptr<Planet> guard(raw);

    Universe::inst->addObject(raw);

    guard.release();
    return raw;
}

Star* ObjectFactory::makeStar(const std::string& name, double mass)
{
    checkMass(mass, 1e30);
    Star* raw = new Star(name, mass);
    std::unique_ptr<Star> guard(raw);

    Universe::inst->addObject(raw);

    guard.release();
    return raw;
}

Asteroid* ObjectFactory::makeAsteroid(
    const std::string& name, double mass, const Vector2& pos, const Vector2& vel)
{
    checkMassUpper(mass, 1e21);
    Asteroid* raw = new Asteroid(name, mass, pos, vel);
    std::unique_ptr<Asteroid> guard(raw);

    Universe::inst->addObject(raw);

    guard.release();
    return raw;
}

Comet* ObjectFactory::makeComet(const std::string& name, double mass, const Vector2& pos,
    const Vector2& vel, const std::string& comp)
{
    checkMass(mass);
    Comet* raw = new Comet(name, mass, pos, vel, comp);
    std::unique_ptr<Comet> guard(raw);

    Universe::inst->addObject(raw);

    guard.release();
    return raw;
}

// Quick helpers for our solar system
Star* ObjectFactory::makeSun()
{
    return makeStar("sun", 1.98892e30);
}
Planet* ObjectFactory::makeMercury()
{
    double pos[] = { 60000000000, 0 };
    double vel[] = { 0, 47360.00 };
    return makePlanet("mercury", 3.3011e23, Vector2(pos), Vector2(vel));
}
Planet* ObjectFactory::makeVenus()
{
    double pos[] = { 108000000000, 0 };
    double vel[] = { 0, 35020.00 };
    return makePlanet("venus", 4.8675e24, Vector2(pos), Vector2(vel));
}
Planet* ObjectFactory::makeEarth()
{
    double pos[] = { 149597870700, 0 };
    double vel[] = { 0, 29788.4676 };
    return makePlanet("earth", 5.9742e24, Vector2(pos), Vector2(vel));
}
Planet* ObjectFactory::makeMars()
{
    double pos[] = { 228000000000, 0 };
    double vel[] = { 0, 24070.00 };
    return makePlanet("mars", 6.417e23, Vector2(pos), Vector2(vel));
}
Planet* ObjectFactory::makeJupiter()
{
    double pos[] = { 780000000000, 0 };
    double vel[] = { 0, 13070.00 };
    return makePlanet("jupiter", 1.8982e27, Vector2(pos), Vector2(vel));
}
Planet* ObjectFactory::makeSaturn()
{
    double pos[] = { 1450000000000, 0 };
    double vel[] = { 0, 9680.00 };
    return makePlanet("saturn", 5.6834e26, Vector2(pos), Vector2(vel));
}
Planet* ObjectFactory::makeUranus()
{
    double pos[] = { 2850000000000, 0 };
    double vel[] = { 0, 6800.00 };
    return makePlanet("uranus", 8.6810e25, Vector2(pos), Vector2(vel));
}
Planet* ObjectFactory::makeNeptune()
{
    double pos[] = { 4500000000000, 0 };
    double vel[] = { 0, 5430.00 };
    return makePlanet("neptune", 1.02409e26, Vector2(pos), Vector2(vel));
}

Asteroid* ObjectFactory::make1Ceres()
{
    double pos[] = { 4.14e11, 0 };
    double vel[] = { 0, 17900 };
    return makeAsteroid("1 ceres", 9.3839e20, Vector2(pos), Vector2(vel));
}
Asteroid* ObjectFactory::make4Vesta()
{
    double pos[] = { 3.53e11, 0 };
    double vel[] = { 0, 19340 };
    return makeAsteroid("4 vesta", 2.590271e20, Vector2(pos), Vector2(vel));
}
Asteroid* ObjectFactory::make2Pallas()
{
    double pos[] = { 4.14e11, 0 };
    double vel[] = { 0, 17900 };
    return makeAsteroid("2 pallas", 2.04e20, Vector2(pos), Vector2(vel));
}
Asteroid* ObjectFactory::make10Hygiea()
{
    double pos[] = { 4.7e11, 0 };
    double vel[] = { 0, 16800 };
    return makeAsteroid("10 hygiea", 8.74e19, Vector2(pos), Vector2(vel));
}
Asteroid* ObjectFactory::make704Interamnia()
{
    double pos[] = { 4.57e11, 0 };
    double vel[] = { 0, 16920 };
    return makeAsteroid("704 interamnia", 3.5e19, Vector2(pos), Vector2(vel));
}

Comet* ObjectFactory::makeHalley()
{
    double pos[] = { 2.6534e12, 0 };
    double vel[] = { 0, 7040 };
    return makeComet("halley's", 2.2e14, Vector2(pos), Vector2(vel), "ice");
}

Comet* ObjectFactory::makeHaleBopp()
{
    double pos[] = { 2.65e13, 0 };
    double vel[] = { 0, 2240 };
    return makeComet("hale–bopp", 1.9e14, Vector2(pos), Vector2(vel), "ice");
}

void ObjectFactory::checkMass(const double& mass, double limit)
{
    if (mass < limit)
        throw std::logic_error("Mass must be greater than " + std::to_string(limit));
}

void ObjectFactory::checkMassUpper(const double& mass, double limit)
{
    if (mass >= limit)
        throw std::logic_error("Mass must be smaller than " + std::to_string(limit));
}

// @author G. Hemingway, copyright 2025 - All rights reserved
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include "asteroid.h"
#include "comet.h"
#include "vector.h"

class Object;
class Planet;
class Star;

/**
 *  A factory class used to make Object creation easier.
 */
class ObjectFactory {
public:
    /**
     * Deny access to the default constructor - must be used as static factory
     */
    ObjectFactory() = delete;

    /**
     * Creates a planet with the provided parameters. Adds the object to
     * the singleton Universe
     * @param name - name of the object
     * @param mass - mass of the object - must be greater than 1e21 for planets
     * @param pos - position vector
     * @param vel - velocity vector
     * @return planet object
     */
    static Planet* makePlanet(
        const std::string& name, double mass, const Vector2& pos, const Vector2& vel);

    /**
     * Creates a star at the center of the universe
     * @param name
     * @param mass - must be greater than 1e30 for stars
     * @return star objects
     */
    static Star* makeStar(const std::string& name, double mass);

    /**
     * Creates an asteroid with the provided parameters. Adds the object to
     * the singleton Universe
     * @param name - name of the object
     * @param mass - mass of the object - must be smaller than 1e21
     * @param pos - position vector
     * @param vel - velocity vector
     * @return asteroid object
     */
    static Asteroid* makeAsteroid(
        const std::string& name, double mass, const Vector2& pos, const Vector2& vel);

    /**
     * Creates a comet with the provided parameters. Adds the object to
     * the singleton Universe
     * @param name - name of the object
     * @param mass - mass of the object
     * @param pos - position vector
     * @param vel - velocity vector
     * @param comp - composition
     * @return comet object
     */
    static Comet* makeComet(const std::string& name, double mass, const Vector2& pos,
        const Vector2& vel, const std::string& comp);

    // Quick helpers for our solar system
    static Star* makeSun();
    static Planet* makeMercury();
    static Planet* makeVenus();
    static Planet* makeEarth();
    static Planet* makeMars();
    static Planet* makeJupiter();
    static Planet* makeSaturn();
    static Planet* makeUranus();
    static Planet* makeNeptune();
    // Quick helpers for 5 biggest asteroids
    static Asteroid* make1Ceres();
    static Asteroid* make4Vesta();
    static Asteroid* make2Pallas();
    static Asteroid* make10Hygiea();
    static Asteroid* make704Interamnia();
    // Quick helpers for famous comets
    static Comet* makeHalley();
    static Comet* makeHaleBopp();

private:
    /**
     * Helper function to verify given mass is at or above a limit value
     * @param mass mass to be checked
     * @param limit value to be checked against
     */
    static void checkMass(const double& mass, double limit = 0);
    /**
     * Helper function to verify given mass is below a limit value
     * @param mass mass to be checked
     * @param limit value to be checked against
     */
    static void checkMassUpper(const double& mass, double limit);
};

#endif // OBJECT_FACTORY_H

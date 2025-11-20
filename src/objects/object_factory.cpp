// @author G. Hemingway, copyright 2025 - All rights reserved
#include "vector.h"
#include "objects/object_factory.h"

#include "objects/planet.h"
#include "objects/star.h"
#include "universe.h"

class Object;
class Planet;
class Star;

/**
 *  A factory class used to make Object creation easier.
 */


    /**
     * Creates a planet with the provided parameters. Adds the object to
     * the singleton Universe
     * @param name - name of the object
     * @param mass - mass of the object - must be greater than 1e21 for planets
     * @param pos - position vector
     * @param vel - velocity vector
     * @return planet object
     */
    Planet* ObjectFactory::makePlanet(
        const std::string& name, double mass, const Vector2& pos, const Vector2& vel)
    {
        checkMass(mass,1e21);
        Planet* temp = new Planet(name,mass,pos,vel);
        Universe::inst->addObject(temp);
        return temp;
    }

    /**
     * Creates a star at the center of the universe
     * @param name
     * @param mass - must be greater than 1e30 for stars
     * @return star objects
     */
    Star* ObjectFactory::makeStar(const std::string& name, double mass)
    {
        checkMass(mass,1e30);
        Star* temp = new Star(name,mass);
        Universe::inst->addObject(temp);
        return temp;
    }

    // Quick helpers for our solar system
    Star* ObjectFactory::makeSun()
    {
        return makeStar("sun",1.98892e30);
    }
    Planet* ObjectFactory::makeMercury()
    {
        double pos[]={60000000000, 0};
        double vel[]={0, 47360.00};
        return makePlanet("mercury",3.3011e23,Vector2(pos),Vector2(vel));
    }
    Planet* ObjectFactory::makeVenus()
    {
        double pos[]={108000000000, 0};
        double vel[]={0, 35020.00};
        return makePlanet("venus",4.8675e24,Vector2(pos),Vector2(vel));
    }
    Planet* ObjectFactory::makeEarth(){
        double pos[]={149597870700, 0};
        double vel[]={0, 29788.4676};
        return makePlanet("earth",5.9742e24,Vector2(pos),Vector2(vel));
    }
Planet* ObjectFactory::makeMars(){
        double pos[]={228000000000, 0};
        double vel[]={0, 24070.00};
        return makePlanet("mars",6.417e23,Vector2(pos),Vector2(vel));
    }
    Planet* ObjectFactory::makeJupiter()
    {
        double pos[]={780000000000, 0};
        double vel[]={0, 13070.00};
        return makePlanet("jupiter",1.8982e27,Vector2(pos),Vector2(vel));
    }
    Planet* ObjectFactory::makeSaturn()
    {
        double pos[]={1450000000000, 0};
        double vel[]={0, 9680.00};
        return makePlanet("saturn",5.6834e26,Vector2(pos),Vector2(vel));
    }
    Planet* ObjectFactory::makeUranus()
    {
        double pos[]={2850000000000, 0};
        double vel[]={0, 6800.00};
        return makePlanet("uranus",8.6810e25,Vector2(pos),Vector2(vel));
    }
    Planet* ObjectFactory::makeNeptune()
    {
        double pos[]={4500000000000, 0};
        double vel[]={0, 5430.00};
        return makePlanet("neptune",1.02409e26,Vector2(pos),Vector2(vel));
    }


    /**
     * Helper function to verify given mass is at or above a limit value
     * @param mass mass to be checked
     * @param limit value to be checked against
     */
    void ObjectFactory::checkMass(const double& mass, double limit)//why return is void???
    {
        if (mass<limit) throw std::logic_error("Mass must be greater than " + std::to_string(limit));
    }
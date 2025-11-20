// @author G. Hemingway, copyright 2025 - All rights reserved
// Iterator typedefs
#include "universe.h"
#include "./vector.h"
#include "objects/object.h"
#include "objects/object_factory.h"
#include "objects/planet.h"
#include "objects/star.h"
#include <vector>
class Object;
class ObjectFactory;


typedef std::vector<Object*>::iterator iterator;
typedef std::vector<Object*>::const_iterator const_iterator;

Universe* Universe::inst = nullptr;

/**
 * Returns the only instance of the Universe
 */
Universe* Universe::instance()
{
    if (!inst) {
        inst = new Universe();
    }
    return inst;

}

/**
 * Releases all the dynamic objects still registered with the Universe.
 */

Universe::~Universe()
{
    release(objects);
    inst = nullptr;
}

/**
 * Returns the begin iterator to the actual Objects. The order of iteration
 * will be the same as that over getSnapshot()'s result as long as no new
 * objects are added to either of the containers.
 */
Universe::iterator Universe::begin()
{
    return objects.begin();
}

/**
 * Returns the begin iterator to the actual Objects. The order of iteration
 * will be the same as that over getSnapshot()'s result as long as no new
 * objects are added to either of the containers.
 */
[[nodiscard]] const_iterator Universe::begin() const
{
    return objects.begin();
}

/**
 * Returns the end iterator to the actual Objects. The order of iteration
 * will be the same as that over getSnapshot()'s result as long as no new
 * objects are added to either of the containers.
 */
[[nodiscard]] iterator Universe::end()
{
    return objects.end();
}

/**
 * Returns the end iterator to the actual Objects. The order of iteration
 * will be the same as that over getSnapshot()'s result as long as no new
 * objects are added to either of the containers.
 */
[[nodiscard]] const_iterator Universe::end() const
{
    return objects.end();
}

/**
 * Returns a container of copies of all the Objects registered with the
 * Universe. This should be used as the source of data for computing the
 * next step in the simulation
 */
[[nodiscard]] std::vector<Object*> Universe::getSnapshot() const
{
    std::vector<Object*> temp;
    for (auto iter = this->begin();iter!=this->end();++iter) {
        if (iter == this->begin()) temp.push_back(ObjectFactory::makeStar((*iter)->getName(),(*iter)->getMass()));
        else temp.push_back(ObjectFactory::makePlanet((*iter)->getName(),(*iter)->getMass(),(*iter)->getPosition(),(*iter)->getVelocity()));
    }
    return temp;

}

/**
 * Advances the simulation by the provided time step. For this assignment,
 * you must assume that the first registered object is a "sun" and its
 * position should not be affected by any of the other objects
 * @param timeSec - number of seconds to step the simulation forward
 */
void Universe::stepSimulation(const double& timeSec)
{
    for (auto iter = ++this->begin();iter!=this->end();++iter) {

        Vector2 vel = (*iter)->getVelocity();
        Vector2 newPos = (*iter)->getPosition()+timeSec*vel;
        Vector2 acc = ((*this).sumForce(*iter))/(*iter)->getMass();
        Vector2 newVel = (*iter)->getVelocity()+timeSec*acc;


        (*iter)->setPosition(newPos);
        (*iter)->setVelocity(newVel);

    }
}

/**
 * Swaps the contents of the provided container with the Universe's Object
 * store and releases the old Objects
 * @param snapshot - vector of objects to swap
 */
void Universe::swap(std::vector<Object*>& snapshot)
{
    auto temp  = objects;
    objects = snapshot;
    release(temp);

}




/**
 * Registers an Object with the universe. The Universe will clean up this
 * object when it deems necessary
 * @param ptr - object to add to the universe
 * @return pointer to added object (for chaining)
 */
Object* Universe::addObject(Object* ptr)
{
    objects.push_back(ptr);
    return ptr;
}


/**
 * Calculate the total force for the ith object in the universe
 * @param obj object pointer within the Universe's vector of objects
 * @return Vector2 total force on object
 */
[[nodiscard]] Vector2 Universe::sumForce(const Object* obj) const
{
    Vector2 sum;
    for (auto & object : objects) {
        if (object!=obj) sum+=obj->getForce(*object);
    }
    return sum;
}



// /**
//  * Calls delete on each pointer and removes it from the container
//  * @param objects - vector of objects to be destroyed
//  */
void Universe::release(std::vector<Object*>& objects)
{
    for (auto & object : objects) {
        delete object;

    }
}


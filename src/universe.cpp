// @author G. Hemingway, copyright 2025 - All rights reserved
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
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

Universe* Universe::instance()
{
    if (!inst) {
        inst = new Universe();
    }
    return inst;
}

Universe::~Universe()
{
    release(objects);
    inst = nullptr;
}

Universe::iterator Universe::begin()
{
    return objects.begin();
}

[[nodiscard]] const_iterator Universe::begin() const
{
    return objects.begin();
}

[[nodiscard]] iterator Universe::end()
{
    return objects.end();
}

[[nodiscard]] const_iterator Universe::end() const
{
    return objects.end();
}

[[nodiscard]] std::vector<Object*> Universe::getSnapshot() const
{
    std::vector<Object*> snapshot;
    snapshot.reserve(objects.size());

    for (const auto* obj : objects) {

        snapshot.push_back(obj->clone());
    }

    return snapshot;
}

void Universe::stepSimulation(const double& timeSec)
{
    for (auto iter = ++this->begin(); iter != this->end(); ++iter) {

        Vector2 vel = (*iter)->getVelocity();
        Vector2 newPos = (*iter)->getPosition() + timeSec * vel;
        Vector2 acc = ((*this).sumForce(*iter)) / (*iter)->getMass();
        Vector2 newVel = (*iter)->getVelocity() + timeSec * acc;

        (*iter)->setPosition(newPos);
        (*iter)->setVelocity(newVel);
    }
}

void Universe::swap(std::vector<Object*>& snapshot)
{
    auto temp = objects;
    objects = snapshot;
    release(temp);
}

Object* Universe::addObject(Object* ptr)
{
    objects.push_back(ptr);
    return ptr;
}

[[nodiscard]] Vector2 Universe::sumForce(const Object* obj) const
{
    Vector2 sum;
    for (auto& object : objects) {
        if (object != obj)
            sum += obj->getForce(*object);
    }
    return sum;
}

void Universe::release(std::vector<Object*>& objects)
{
    for (auto& object : objects) {
        delete object;
    }
}

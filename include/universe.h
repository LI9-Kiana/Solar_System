// @author G. Hemingway, copyright 2025 - All rights reserved
#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "./vector.h"
#include <vector>

class Object;
class ObjectFactory;

/**
 * A singleton class representing the Universe. For this assignment, the first
 * object added to the Universe will be considered unmovable and so its
 * position should not be changed.
 */
class Universe {
public:
    // Iterator typedefs
    typedef std::vector<Object*>::iterator iterator;
    typedef std::vector<Object*>::const_iterator const_iterator;

    static constexpr double G = 6.67428e-11;

    /**
     * Returns the only instance of the Universe
     */
    static Universe* instance();

    /**
     * Releases all the dynamic objects still registered with the Universe.
     */
    ~Universe();

    /**
     * Returns the begin iterator to the actual Objects. The order of iteration
     * will be the same as that over getSnapshot()'s result as long as no new
     * objects are added to either of the containers.
     */
    iterator begin();

    /**
     * Returns the begin iterator to the actual Objects. The order of iteration
     * will be the same as that over getSnapshot()'s result as long as no new
     * objects are added to either of the containers.
     */
    [[nodiscard]] const_iterator begin() const;

    /**
     * Returns the end iterator to the actual Objects. The order of iteration
     * will be the same as that over getSnapshot()'s result as long as no new
     * objects are added to either of the containers.
     */
    [[nodiscard]] iterator end();

    /**
     * Returns the end iterator to the actual Objects. The order of iteration
     * will be the same as that over getSnapshot()'s result as long as no new
     * objects are added to either of the containers.
     */
    [[nodiscard]] const_iterator end() const;

    /**
     * Returns a container of copies of all the Objects registered with the
     * Universe. This should be used as the source of data for computing the
     * next step in the simulation
     */
    [[nodiscard]] std::vector<Object*> getSnapshot() const;

    /**
     * Advances the simulation by the provided time step. For this assignment,
     * you must assume that the first registered object is a "sun" and its
     * position should not be affected by any of the other objects
     * @param timeSec - number of seconds to step the simulation forward
     */
    void stepSimulation(const double& timeSec);

    /**
     * Swaps the contents of the provided container with the Universe's Object
     * store and releases the old Objects
     * @param snapshot - vector of objects to swap
     */
    void swap(std::vector<Object*>& snapshot);

private:
    /**
     * Private constructor. Ensures access control via singleton
     */
    Universe() = default;

    /**
     * Registers an Object with the universe. The Universe will clean up this
     * object when it deems necessary
     * @param ptr - object to add to the universe
     * @return pointer to added object (for chaining)
     */
    Object* addObject(Object* ptr);

    /**
     * Calculate the total force for the ith object in the universe
     * @param obj object pointer within the Universe's vector of objects
     * @return Vector2 total force on object
     */
    [[nodiscard]] Vector2 sumForce(const Object* obj) const;

    friend class ObjectFactory; // Needed for object construction
    friend class InertiaTest_TotalForce_Test; // Needed for automated testing

    /**
     * Calls delete on each pointer and removes it from the container
     * @param objects - vector of objects to be destroyed
     */
    static void release(std::vector<Object*>& objects);

    std::vector<Object*> objects; // Container for pointers to the registered Objects
    static Universe* inst; // Static singleton pointer
};

#endif // UNIVERSE_H

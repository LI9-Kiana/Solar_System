// @author G. Hemingway, copyright 2025 - All rights reserved
#include "./test_helper.h"
#include "objects/object.h"
#include "objects/object_factory.h"
#include "objects/planet.h"
#include "universe.h"
#include <gtest/gtest.h>
#include <memory>

// The fixture for testing the Inertia math.
class InertiaTest : public ::testing::Test { };

TEST_F(InertiaTest, TotalForce)
{
    const std::unique_ptr<Universe> univ(Universe::instance());

    ObjectFactory::makeSun();
    const Object* mercury = ObjectFactory::makeMercury();
    const Object* venus = ObjectFactory::makeVenus();
    const Object* earth = ObjectFactory::makeEarth();
    const Object* mars = ObjectFactory::makeMars();

    const auto forceMercury = univ->sumForce(mercury);
    EXPECT_EQ(forceMercury.toString(), "[-1.21724e+22 0]");

    const auto forceVenus = univ->sumForce(venus);
    EXPECT_EQ(forceVenus.toString(), "[-5.53951e+22 0]");

    const auto forceEarth = univ->sumForce(earth);
    EXPECT_EQ(forceEarth.toString(), "[-3.54376e+22 0]");

    const auto forceMars = univ->sumForce(mars);
    EXPECT_EQ(forceMars.toString(), "[-1.6387e+21 0]");
}

TEST_F(InertiaTest, FreeBodyTest)
{
    const std::unique_ptr<Universe> univ(Universe::instance());
    // Create a sun with mass, stationary at origin
    ObjectFactory::makeStar("sun", 1e30);
    // Make an object with mass=1e22 with some initial pos and vel
    const Vector2 velocity = makeVector2(1e6, 0);
    const Vector2 position = makeVector2(1e10, 1e10);
    ObjectFactory::makePlanet("obj", 1e22, position, velocity);

    std::vector<Vector2> result(10);
    result[0] = makeVector2(1e+10, 1e+10);
    result[1] = makeVector2(1.0001e+10, 1e+10);
    result[2] = makeVector2(10001999999.764029, 9999999999.7640285);
    result[3] = makeVector2(10002999999.292097, 9999999999.2921219);
    result[4] = makeVector2(10003999998.584219, 9999999998.5843143);
    result[5] = makeVector2(10004999997.640404, 9999999997.6406402);
    result[6] = makeVector2(10005999996.460665, 9999999996.4611377);
    result[7] = makeVector2(10006999995.045013, 9999999995.0458393);
    result[8] = makeVector2(10007999993.393461, 9999999993.394783);
    result[9] = makeVector2(10008999991.50602, 9999999991.5080013);

    // Let's run the simulation forward 10 time steps
    for (uint64_t step = 0; step < 10; ++step) {
        const Object& obj = **(++(univ->begin()));
        const auto pos = obj.getPosition();
        assertVector(pos, result[step]);
        univ->stepSimulation(1);
    }
}

// @author G. Hemingway, copyright 2025 - All rights reserved
#include "./test_helper.h"
#include "objects/object.h"
#include "objects/object_factory.h"
#include "objects/planet.h"
#include "objects/star.h"
#include "universe.h"
#include <gtest/gtest.h>
#include <memory>

// The fixture for testing the Gravitation math.
class GravitationTest : public ::testing::Test { };

TEST_F(GravitationTest, Simple)
{
    const std::unique_ptr<Universe> univ(Universe::instance());

    // Create two simple bodies
    const Vector2 vel = makeVector2(0, 0);
    const auto objA = ObjectFactory::makeStar("A", 1e52);
    const Vector2 p2 = makeVector2(100, 100);
    const auto objB = ObjectFactory::makePlanet("B", 1e23, p2, vel);

    // Is the gravitational pull between them correct
    const auto force1 = objA->getForce(*objB);
    EXPECT_EQ(force1.toString(), "[2.35971e+60 2.35971e+60]");
    const auto force2 = objB->getForce(*objA);
    EXPECT_EQ(force2.toString(), "[-2.35971e+60 -2.35971e+60]");
}

TEST_F(GravitationTest, TwoBodies)
{
    const std::unique_ptr<Universe> univ(Universe::instance());

    // Create a sun with real mass
    const auto sun = ObjectFactory::makeStar("sun", 1.98892e30);

    // Make an earth with real properties
    const Vector2 velocity = makeVector2(0, 0);
    const Vector2 position = makeVector2(-8.1519460488671951e+010 - 1.2543598125392383e+011);
    const auto earth = ObjectFactory::makePlanet("earth", 5.9742e24, position, velocity);

    // Is the gravitational pull between them correct
    const auto force1 = earth->getForce(*sun);
    EXPECT_EQ(force1.toString(), "[1.8516e+22 0]");
    const auto force2 = sun->getForce(*earth);
    EXPECT_EQ(force2.toString(), "[-1.8516e+22 0]");
}

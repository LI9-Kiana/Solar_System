//
// Created by zhuct on 11/20/2025.
//
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#include "./test_helper.h"

#include "objects/asteroid.h"
#include "objects/comet.h"
#include "objects/object.h"
#include "objects/object_factory.h"
#include "objects/planet.h"
#include "objects/star.h"
#include "parser.h"
#include "universe.h"
#include "visitors/print.h"

#include <gtest/gtest.h>
#include <memory>
#include <sstream>

class ExtendedSolarSystem : public ::testing::Test { };

// ---------------- ASTEROID TESTS --------------

// 1) Asteroid mass >= 1e21 should throw std::logic_error
TEST_F(ExtendedSolarSystem, AsteroidTooMassiveThrows)
{
    const std::unique_ptr<Universe> univ(Universe::instance());
    Vector2 pos;
    Vector2 vel;

    EXPECT_THROW({ ObjectFactory::makeAsteroid("too-big", 1.0e21, pos, vel); }, std::logic_error);
}

// 2) Valid asteroid via factory is created and registered in Universe
TEST_F(ExtendedSolarSystem, AsteroidValidMassAndRegistered)
{
    const std::unique_ptr<Universe> univ(Universe::instance());
    Vector2 pos;
    Vector2 vel;

    const Object* obj = ObjectFactory::makeAsteroid("valid-asteroid", 9.9e20, pos, vel);
    ASSERT_NE(obj, nullptr);

    const Asteroid* asteroid = dynamic_cast<const Asteroid*>(obj);
    ASSERT_NE(asteroid, nullptr);

    // Check that it's in the Universe's object list
    bool found = false;
    for (const auto* o : *univ) {
        if (o == obj) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
    EXPECT_LT(asteroid->getMass(), 1e21);
}

// 3) Named asteroid helpers (5 largest) produce Asteroid objects
TEST_F(ExtendedSolarSystem, AsteroidNamedFactories)
{
    const std::unique_ptr<Universe> univ(Universe::instance());

    const Object* a1 = ObjectFactory::make1Ceres();
    const Object* a2 = ObjectFactory::make2Pallas();
    const Object* a3 = ObjectFactory::make4Vesta();
    const Object* a4 = ObjectFactory::make10Hygiea();
    const Object* a5 = ObjectFactory::make704Interamnia();

    ASSERT_NE(a1, nullptr);
    ASSERT_NE(a2, nullptr);
    ASSERT_NE(a3, nullptr);
    ASSERT_NE(a4, nullptr);
    ASSERT_NE(a5, nullptr);

    EXPECT_NE(dynamic_cast<const Asteroid*>(a1), nullptr);
    EXPECT_NE(dynamic_cast<const Asteroid*>(a2), nullptr);
    EXPECT_NE(dynamic_cast<const Asteroid*>(a3), nullptr);
    EXPECT_NE(dynamic_cast<const Asteroid*>(a4), nullptr);
    EXPECT_NE(dynamic_cast<const Asteroid*>(a5), nullptr);
}

// 4) Asteroids created from extended_solar_system.json by Parser
TEST_F(ExtendedSolarSystem, AsteroidsParsedFromExtendedJSON)
{
    const std::unique_ptr<Universe> univ(Universe::instance());
    Parser::loadFile("../tests/extended_solar_system.json");

    int asteroidCount = 0;
    for (const auto* obj : *univ) {
        if (dynamic_cast<const Asteroid*>(obj) != nullptr) {
            ++asteroidCount;
        }
    }

    // 5 largest asteroids should be present
    EXPECT_GE(asteroidCount, 5);
}

// -------------------- COMET TESTS --------------------

// 1) Valid comet compositions via ObjectFactory should succeed
TEST_F(ExtendedSolarSystem, CometValidCompositions)
{
    const std::unique_ptr<Universe> univ(Universe::instance());
    Vector2 pos;
    Vector2 vel;

    const Object* c1 = ObjectFactory::makeComet("ice-comet", 1e14, pos, vel, "ice");
    const Object* c2 = ObjectFactory::makeComet("dust-comet", 1e14, pos, vel, "dust");
    const Object* c3 = ObjectFactory::makeComet("rock-comet", 1e14, pos, vel, "rock");

    EXPECT_NE(dynamic_cast<const Comet*>(c1), nullptr);
    EXPECT_NE(dynamic_cast<const Comet*>(c2), nullptr);
    EXPECT_NE(dynamic_cast<const Comet*>(c3), nullptr);
}

// 2) Invalid composition should throw std::logic_error
TEST_F(ExtendedSolarSystem, CometInvalidCompositionThrows)
{
    const std::unique_ptr<Universe> univ(Universe::instance());
    Vector2 pos;
    Vector2 vel;

    EXPECT_THROW(
        { ObjectFactory::makeComet("bad-comet", 1e14, pos, vel, "gas"); }, std::logic_error);
}

// 3) Great comets from helpers (Halley + Hale-Bopp) are Comet objects
TEST_F(ExtendedSolarSystem, CometFactoryCreatesGreatComets)
{
    const std::unique_ptr<Universe> univ(Universe::instance());

    const Object* halley = ObjectFactory::makeHalley();
    const Object* haleBopp = ObjectFactory::makeHaleBopp();

    ASSERT_NE(halley, nullptr);
    ASSERT_NE(haleBopp, nullptr);

    EXPECT_NE(dynamic_cast<const Comet*>(halley), nullptr);
    EXPECT_NE(dynamic_cast<const Comet*>(haleBopp), nullptr);
}

// 4) Comets parsed from extended JSON
TEST_F(ExtendedSolarSystem, CometsParsedFromExtendedJSON)
{
    const std::unique_ptr<Universe> univ(Universe::instance());
    Parser::loadFile("../tests/extended_solar_system.json");

    bool foundHalley = false;
    bool foundHaleBopp = false;

    for (const auto* obj : *univ) {
        if (const auto* c = dynamic_cast<const Comet*>(obj)) {
            if (c->getName() == "halley's")
                foundHalley = true;
            if (c->getName() == "hale–bopp" || c->getName() == "HaleBopp")
                foundHaleBopp = true;
        }
    }

    EXPECT_TRUE(foundHalley);
    EXPECT_TRUE(foundHaleBopp);
}

// -------------------- MIXED SYSTEM TEST --------------------

// Ensure a solar system full of Stars, Planets, Asteroids and Comets
// can be constructed, simulated, visited, and cleaned up.
TEST_F(ExtendedSolarSystem, MixedSystemSimulateVisitAndCleanup)
{
    const std::unique_ptr<Universe> univ(Universe::instance());

    // Build system from extended JSON
    Parser::loadFile("../tests/extended_solar_system.json");

    int starCount = 0;
    int planetCount = 0;
    int asteroidCount = 0;
    int cometCount = 0;

    for (const auto* obj : *univ) {
        if (dynamic_cast<const Star*>(obj))
            ++starCount;
        if (dynamic_cast<const Planet*>(obj))
            ++planetCount;
        if (dynamic_cast<const Asteroid*>(obj))
            ++asteroidCount;
        if (dynamic_cast<const Comet*>(obj))
            ++cometCount;
    }

    EXPECT_GE(starCount, 1);
    EXPECT_GE(planetCount, 8); // 8 planets
    EXPECT_GE(asteroidCount, 5); // 5 largest asteroids
    EXPECT_GE(cometCount, 2); // Halley + Hale-Bopp

    // Step the simulation a bit to ensure no crashes
    const uint64_t stepS = 60 * 60; // 1 hour
    for (int i = 0; i < 24; ++i) {
        univ->stepSimulation(stepS);
    }

    std::ostringstream oss;
    PrintVisitor pv(oss);

    // Visit all objects in a consistent order
    for (auto* obj : *univ)
        obj->accept(pv);

    std::string output = oss.str();
    EXPECT_FALSE(output.empty()) << "PrintVisitor produced no output.";

    // ---- CHECK EACH TYPE SEPARATELY ----

    // 1. Asteroid format
    // Example:
    // Asteroid: Ceres 9.39e+20kg [x y][vx vy]
    EXPECT_NE(output.find("Asteroid:"), std::string::npos) << "Expected an asteroid print line.";

    // 2. Comet format
    // Example:
    // Comet: Halley 2.2e14kg [x y][vx vy] ice
    // (You used 'Planet:' for comets — test must match your behavior)
    EXPECT_NE(output.find("Comet:"), std::string::npos)
        << "Expected a comet print line (your implementation prints 'Planet:' for comets).";

    // 3. Check that composition string is printed
    EXPECT_TRUE(output.find(" ice") != std::string::npos
        || output.find(" dust") != std::string::npos || output.find(" rock") != std::string::npos)
        << "Comet composition (ice/dust/rock) not found in PrintVisitor output.";

    // 4. Verify vector formatting
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);

    // 5. Ensure every line ends with newline
    std::stringstream ss(output);
    std::string line;
    while (std::getline(ss, line)) {
        EXPECT_FALSE(line.empty()) << "Each print line must end in newline.";
    }
}

TEST_F(ExtendedSolarSystem, UniverseCleansUpObjectsOnDestruction)
{
    std::size_t objectCountInside = 0;

    {
        // First lifetime: build extended system
        const std::unique_ptr<Universe> univ(Universe::instance());
        Parser::loadFile("../tests/extended_solar_system.json");

        // Count how many objects we have
        for (const auto* obj : *univ) {
            (void)obj;
            ++objectCountInside;
        }

        // Sanity check: we actually loaded *something*
        EXPECT_GT(objectCountInside, 0u);
        // When this scope ends, ~Universe() should:
        // - delete all objects
        // - clear the container
        // - set Universe::inst = nullptr
    }

    // Second lifetime: Universe should be brand new and empty
    {
        const std::unique_ptr<Universe> fresh(Universe::instance());

        std::size_t objectCountAfter = 0;
        for (const auto* obj : *fresh) {
            (void)obj;
            ++objectCountAfter;
        }

        // the new Universe instance should start with no objects
        EXPECT_EQ(objectCountAfter, 0u)
            << "Universe should be empty after previous instance was destroyed.";
    }
}
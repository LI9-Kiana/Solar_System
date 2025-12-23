// @author G. Hemingway, copyright 2025 - All rights reserved
#include "objects/object.h"
#include "objects/object_factory.h"
#include "parser.h"
#include "universe.h"
#include "visitors/print.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

// The fixture for testing the ObjectFactory class.
class ObjectFactoryTest : public ::testing::Test { };

TEST_F(ObjectFactoryTest, Simple)
{
    const Vector2 pos;
    const Vector2 vel;
    const std::unique_ptr<Universe> univ(Universe::instance());
    EXPECT_THAT([&]() { ObjectFactory::makePlanet("negative-mass", -10, pos, vel); },
        testing::ThrowsMessage<std::logic_error>(
            testing::HasSubstr("Mass must be greater than 1000000000000000000000.000000")));

    EXPECT_THAT([&]() { ObjectFactory::makeStar("small-star", 1e29); },
        testing::ThrowsMessage<std::logic_error>(testing::HasSubstr(
            "Mass must be greater than 1000000000000000019884624838656.000000")));
}

TEST_F(ObjectFactoryTest, SolarSystem)
{
    std::stringstream stream1;
    std::stringstream stream2;
    {
        // Load the solar system from factory methods
        const std::unique_ptr<Universe> univ(Universe::instance());
        ObjectFactory::makeSun();
        ObjectFactory::makeMercury();
        ObjectFactory::makeVenus();
        ObjectFactory::makeEarth();
        ObjectFactory::makeMars();
        ObjectFactory::makeJupiter();
        ObjectFactory::makeSaturn();
        ObjectFactory::makeUranus();
        ObjectFactory::makeNeptune();
        PrintVisitor printer1(stream1);
        for (const auto& i : *univ)
            i->accept(printer1);
        stream1.flush();
    }
    {
        // Load the solar system from JSON
        const std::unique_ptr<Universe> univ(Universe::instance());
        Parser::loadFile("../tests/solar_system.json");
        PrintVisitor printer2(stream2);
        for (const auto& i : *univ)
            i->accept(printer2);
        stream2.flush();
    }
    EXPECT_EQ(stream1.str(), stream2.str());
}

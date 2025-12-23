// @author G. Hemingway, copyright 2025 - All rights reserved
#include "./test_helper.h"
#include "objects/object.h"
#include "objects/object_factory.h"
#include "universe.h"
#include "visitors/print.h"
#include <gtest/gtest.h>
#include <memory>

const auto expectedOutput = "Star: V 1e+55kg\n"
                            "Planet: a 1e+22kg [0 0][0 0]\n"
                            "Star: n 1e+56kg\n"
                            "Planet: d 1e+23kg [0 0][0 0]\n"
                            "Star: y 1e+57kg\n";

// The fixture for testing the PrintVisitor class.
class PrintVisitorTest : public ::testing::Test { };

TEST_F(PrintVisitorTest, SimpleVisitor)
{
    std::stringstream stream;
    const std::unique_ptr<Universe> univ(Universe::instance());

    const Vector2 pos;
    const Vector2 vel;
    ObjectFactory::makeStar("V", 1e55);
    ObjectFactory::makePlanet("a", 1e22, pos, vel);
    ObjectFactory::makeStar("n", 1e56);
    ObjectFactory::makePlanet("d", 1e23, pos, vel);
    ObjectFactory::makeStar("y", 1e57);

    PrintVisitor printer(stream);
    for (const auto& i : *univ)
        i->accept(printer);

    stream.flush();
    EXPECT_EQ(stream.str(), expectedOutput);
}

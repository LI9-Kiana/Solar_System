// @author G. Hemingway, copyright 2025 - All rights reserved
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#include "./test_helper.h"
#include "objects/object.h"
#include "parser.h"
#include "universe.h"
#include "visitors/visitor.h"
#include "visitors/visualizer.h"
#include <fstream>
#include <gtest/gtest.h>
#include <memory>

// The fixture for testing multi-body motion
class SolarSystem : public ::testing::Test { };

TEST_F(SolarSystem, AllPlanets)
{
    std::ifstream file("../tests/solar_system.data", std::ifstream::in);
    if (file.fail()) {
        std::cout << "Error: " << strerror(errno) << std::endl;
        std::cout << "SolarSystem not able to open data file: ../tests/solar_system.data."
                  << std::endl;
        exit(-1);
    }
    std::cout << "SolarSystem data file opened." << std::endl;
    FileCloser closer(file); // Closer will automatically close our file

    const uint64_t stepS = 60 * 60; // Step is one hour (in seconds)
    const uint64_t yearS = 31554195;

    // Load the simulation setup
    const std::unique_ptr<Universe> univ(Universe::instance());
    Parser::loadFile("../tests/solar_system.json");

    for (uint64_t timeS = 0; timeS <= yearS; timeS += stepS) {
        // Check all elements against expected position
        for (const auto& obj : *univ) {
            if (obj->getName() != "sun") {
                Vector2 pos = obj->getPosition();
                Vector2 check = getNextVector(file);
                // Object must be within 1 million meters of expected
                assertVector(pos, check, 1000000.0);
            }
        }
        univ->stepSimulation(stepS);
    }

    /** Uncomment these lines if you submit the extra credit - you will also need
     * to #include your visitor's header file  **/
    VisualVisitor vizVis;
    for (const auto& i : *univ)
        i->accept(vizVis);
    vizVis->visualize(std::cout);
}

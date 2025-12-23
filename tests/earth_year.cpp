// @author G. Hemingway, copyright 2025 - All rights reserved
#include "./test_helper.h"
#include "objects/object.h"
#include "parser.h"
#include "universe.h"
#include <fstream>
#include <gtest/gtest.h>
#include <memory>

// The fixture for testing Uniform Circular Motion math.
class EarthYear : public ::testing::Test { };

TEST_F(EarthYear, YearlongTest)
{
    std::ifstream file("../tests/earth_year.data", std::ifstream::in);
    if (file.fail()) {
        std::cout << "Error: " << strerror(errno) << std::endl;
        std::cout << "EarthYear not able to open file: ../tests/earth_year.data." << std::endl;
        exit(-1);
    }
    std::cout << "EarthYear opened file." << std::endl;
    FileCloser closer(file); // Closer will automatically close our file

    const uint64_t stepS = 1; // One second time step
    const uint64_t yearS = 31554195; // 31.5 million time steps!!!
    const uint64_t checkEvery = 100; // Validate position every 100 steps
    uint64_t stepCount = 0;

    // Load the simulation setup
    std::unique_ptr<Universe> univ(Universe::instance());
    Parser::loadFile("../tests/earth_year.json");

    for (uint64_t timeS = 0; timeS < yearS; timeS += stepS) {
        // Only compare against file data every 100 steps
        if (stepCount == checkEvery) {
            // Go to second object (Earth) - why is ** necessary?
            const Object& object = **(++(univ->begin()));
            const Vector2 pos = object.getPosition();
            const Vector2 check = getNextVector(file);
            assertVector(pos, check, 1000000.0);
            stepCount = 0;
        }
        ++stepCount;
        univ->stepSimulation(stepS);
    }

    /** Uncomment these lines if you submit the extra credit - you will also need
     * to #include your visitor's header file  **/
    // VisualVisitor vizVis;
    // for (const auto& i : *univ)
    //     i->accept(vizVis);
    // vizVis->visualize(std::cout);
}

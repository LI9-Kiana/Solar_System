// @author G. Hemingway, copyright 2025 - All rights reserved
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#include "parser.h"
#include "objects/object_factory.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

void Parser::loadFile(const std::string& filename)
{
    std::ifstream config(filename);
    if (config.fail()) {
        std::cout << "Parser not able to open file: " << filename << std::endl;
        exit(-1);
    }

    const auto json = nlohmann::json::parse(config);
    for (const auto& el : json) {
        // Name
        const std::string name = el["name"];
        // Mass
        const double mass = el["mass"];

        // Is this a star or a planet
        if (el.contains("pos")) {

            // Pos
            const auto& pos = el["pos"];
            Vector2 posVec;
            posVec[0] = pos[0];
            posVec[1] = pos[1];
            // Vel
            const auto& vel = el["vel"];
            Vector2 velVec;
            velVec[0] = vel[0];
            velVec[1] = vel[1];
            if (el.contains("comp")) {
                const std::string composi = el["comp"];
                ObjectFactory::makeComet(name, mass, posVec, velVec, composi);
            } else {
                if (mass >= 1e21)
                    ObjectFactory::makePlanet(name, mass, posVec, velVec);
                else
                    ObjectFactory::makeAsteroid(name, mass, posVec, velVec);
            }

        }

        else {
            // Create the star object - rooted at zero, zero with no velocity
            ObjectFactory::makeStar(name, mass);
        }
        // Close the input file
        config.close();
    }
}

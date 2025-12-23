//
// Created by zhuct on 11/21/2025.
//
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#ifndef ASSIGNMENT6_VISUALIZER_H
#define ASSIGNMENT6_VISUALIZER_H

#include "visitors/visitor.h"
#include <ostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Object;
class Star;
class Planet;
class Asteroid;
class Comet;

/**
 * ASCII visualizer visitor for the Universe.
 * Collects Object pointers via visit(), then renders them with visualize().
 */
class VisualVisitor final : public Visitor {
public:
    VisualVisitor() = default;

    // Make vizVis->visualize work
    VisualVisitor* operator->()
    {
        return this;
    }
    const VisualVisitor* operator->() const
    {
        return this;
    }

    // Visitor overrides collect pointers to the live objects
    void visit(const Star& star) const override;
    void visit(const Planet& planet) const override;
    void visit(const Asteroid& ast) const override;
    void visit(const Comet& comet) const override;

    /**
     * Render current Universe snapshot as 64x16 ASCII art.
     */
    void visualize(std::ostream& os) const;


    // We mutate this inside const visit() and visualize()
    mutable std::vector<const Object*> objects;
private:
    /**
     * Choose a single-character marker for an object, using:
     * - first letter of its name
     * - if already used, the first unique letter in its name
     */
    char chooseMarker(const Object* obj, std::unordered_map<const Object*, char>& mapping,
        std::unordered_set<char>& used) const;
};
#endif // ASSIGNMENT6_VISUALIZER_H

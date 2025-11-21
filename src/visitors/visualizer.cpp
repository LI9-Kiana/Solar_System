//
// Created by zhuct on 11/21/2025.
//
// Name: Chengtong Zhu; vunetid: zhuc13; email address: chengtong.zhu@vanderbil.edu; honor code: I
// pledge on my honor that I have neither given nor received unauthorized aid on this assignment.
#include "visitors/visualizer.h"

#include "objects/asteroid.h"
#include "objects/comet.h"
#include "objects/object.h"
#include "objects/planet.h"
#include "objects/star.h"
#include "vector.h" // for Vector2

#include <algorithm>
#include <cctype>
#include <cmath>

// Collect pointers to all visited objects

void VisualVisitor::visit(const Star& star) const
{
    objects.push_back(&star);
}

void VisualVisitor::visit(const Planet& planet) const
{
    objects.push_back(&planet);
}

void VisualVisitor::visit(const Asteroid& ast) const
{
    objects.push_back(&ast);
}

void VisualVisitor::visit(const Comet& comet) const
{
    objects.push_back(&comet);
}

char VisualVisitor::chooseMarker(const Object* obj,
    std::unordered_map<const Object*, char>& mapping, std::unordered_set<char>& used) const
{
    // If we already computed its marker, reuse it
    auto it = mapping.find(obj);
    if (it != mapping.end())
        return it->second;

    const std::string& name = obj->getName();
    char marker = '?';

    // Uppercase safe
    auto up = [](char c) { return static_cast<char>(std::toupper(static_cast<unsigned char>(c))); };

    if (!name.empty()) {
        // Try first letter
        char first = up(name[0]);
        if (!used.contains(first)) {
            marker = first;
        } else {
            // Try letter in the rest of the name
            for (std::size_t i = 1; i < name.size(); ++i) {
                char c = name[i];
                if (c == ' ')
                    continue;
                char uc = up(c);
                if (!used.contains(uc)) {
                    marker = uc;
                    break;
                }
            }
        }
    }

    used.insert(marker);
    mapping[obj] = marker;
    return marker;
}

void VisualVisitor::visualize(std::ostream& os) const
{
    // Total frame
    constexpr int TOTAL_W = 64;
    constexpr int TOTAL_H = 16;
    // Interior area
    constexpr int INNER_W = TOTAL_W - 2; // 62
    constexpr int INNER_H = TOTAL_H - 2; // 14

    if (objects.empty()) {
        return; // nothing to visualize
    }

    // Choose center object: first object
    const Object* centerObj = nullptr;
    centerObj = objects[0];

    const Vector2 centerPos = centerObj->getPosition();

    // Compute max distance from center used to compute scaling
    double maxDist = 0.0;
    for (const auto* obj : objects) {
        Vector2 rel = obj->getPosition() - centerPos;
        double d = rel.norm();
        if (d > maxDist)
            maxDist = d;
    }
    if (maxDist == 0.0) {
        maxDist = 1.0; // avoid division by zero
    }

    // Interior "radius" in cells
    const double radiusX = INNER_W / 2.0;
    const double radiusY = INNER_H / 2.0;

    // Use a single scale so we keep aspect ratio reasonable (the height 14 makes everything
    // horizontally small though...)
    double scaleX = maxDist / radiusX;
    double scaleY = maxDist / radiusY;
    double scale = std::max(scaleX, scaleY);
    if (scale == 0.0)
        scale = 1.0;

    // Prepare blank interior grid
    std::vector<std::string> grid(INNER_H, std::string(INNER_W, ' '));

    // Center cell (in interior coordinates)
    const int cx = INNER_W / 2;
    const int cy = INNER_H / 2;

    // Marker mapping / used letters
    std::unordered_map<const Object*, char> markerMap;
    std::unordered_set<char> usedLetters;

    // Plot each object
    for (const auto* obj : objects) {
        Vector2 rel = obj->getPosition() - centerPos;

        // Convert to "grid units"
        double gx = rel[0] / scale;
        double gy = rel[1] / scale;

        // Map to grid
        int col = cx + static_cast<int>(std::round(gx));
        int row = cy - static_cast<int>(std::round(gy)); // invert y for screen

        if (row < 0 || row >= INNER_H || col < 0 || col >= INNER_W) {
            continue;
        }

        char marker = chooseMarker(obj, markerMap, usedLetters);
        while (grid[row][col] != ' ')
            ++col; // make sure no objects overlap
        grid[row][col] = marker;
    }

    // Plot everything
    // Top border
    os << std::string(TOTAL_W, '*') << '\n';

    // Interior with side borders
    for (int r = 0; r < INNER_H; ++r) {
        os << '*' << grid[r] << "*\n";
    }

    // Bottom border
    os << std::string(TOTAL_W, '*') << '\n';
}
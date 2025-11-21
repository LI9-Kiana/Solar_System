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
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <unordered_set>

// ---------- color helper state (cpp-only, not in header) ----------
namespace {
// Remember which color each object pointer got
std::unordered_map<const Object*, int> objectColor;
// Remember which color codes are already in use
std::unordered_set<int> usedColors;

int getColorFor(const Object* obj)
{
    // If we already assigned a color, reuse it
    auto it = objectColor.find(obj);
    if (it != objectColor.end())
        return it->second;

    // Seed RNG once lazily
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }

    int color;
    do {
        color = std::rand() % 256; // ANSI 256-color index
    } while (usedColors.contains(color));

    usedColors.insert(color);
    objectColor[obj] = color;
    return color;
}
} // anonymous namespace

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

    // Choose center object: first object (you can switch to first Star if you want)
    const Object* centerObj = objects[0];
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

    // Use a single scale so we keep aspect ratio reasonable
    double scaleX = maxDist / radiusX;
    double scaleY = maxDist / radiusY;
    double scale = std::max(scaleX, scaleY);
    if (scale == 0.0)
        scale = 1.0;

    // Instead of chars, store which object is in each cell (for per-object color)
    std::vector<std::vector<const Object*>> grid(
        INNER_H, std::vector<const Object*>(INNER_W, nullptr));

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

        // Find a free column on this row to avoid overlap, like you did before
        while (col < INNER_W && grid[row][col] != nullptr) {
            ++col;
        }
        if (col >= INNER_W) {
            continue; // no space on this row
        }

        grid[row][col] = obj;
    }

    // Plot everything
    // Top border
    os << std::string(TOTAL_W, '*') << '\n';

    // Interior with side borders
    for (int r = 0; r < INNER_H; ++r) {
        os << '*';
        for (int c = 0; c < INNER_W; ++c) {
            const Object* obj = grid[r][c];
            if (!obj) {
                os << ' ';
            } else {
                char marker = chooseMarker(obj, markerMap, usedLetters);
                int color = getColorFor(obj);
                // ANSI 256-color: set foreground color, print marker, reset
                os << "\033[38;5;" << color << "m" << marker << "\033[0m";
            }
        }
        os << "*\n";
    }

    // Bottom border
    os << std::string(TOTAL_W, '*') << '\n';
}

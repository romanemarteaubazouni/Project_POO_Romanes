#pragma once
#include <iostream>
#include <vector>
#include <array>

class Frame3D {
    private:
        std::vector<std::array<double, 3>> vectors;

    public:
        void addVector(double x, double y, double z);

        void display() const;
};
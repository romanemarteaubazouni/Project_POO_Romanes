#include "Frame3D.hpp"

void Frame3D::addVector(double x, double y, double z) {
    vectors.push_back({x, y, z});
}

void Frame3D::display() const {
    for (const auto& v : vectors) {
        std::cout << "(" << v[0] << ", "
            << v[1] << ", "
            << v[2] << ")" << std::endl;
    }
}


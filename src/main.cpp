#include <iostream>
#include <vector>
#include <cmath>
#include "Frame3D.hpp"

int main() {
    double s = 1.0 / std::sqrt(3.0);

    // On construit la frame F1
    Frame3D F_1 {};
    std::vector<double> v1 = {1, 0, 0};
    std::vector<double> v2 = {-1, 0, 0};
    std::vector<double> v3 = {0, 1, 0};
    std::vector<double> v4 = {0, -1, 0};
    std::vector<double> v5 = {0, 0, 1};
    std::vector<double> v6 = {0, 0, -1};
    F_1.add(v1);
    F_1.add(v2);
    F_1.add(v3);
    F_1.add(v4);
    F_1.add(v5);
    F_1.add(v6);

    // On construction la frame F2
    Frame3D F_2 {};
    std::vector<double> v7 = {1, 0, 0};
    std::vector<double> v8 = {0, 1, 0};
    std::vector<double> v9 = {0, 0, 1};
    std::vector<double> v10 = {-s, s, -s};
    F_2.add(v7);
    F_2.add(v8);
    F_2.add(v9);
    F_2.add(v10);

    // On construit la frame F3
    Frame3D F_3 = F_1 + F_2;

    // Quality mesure pour {s, s, s}
    std::cout << "La quality_measure pour F1 est : " << F_1.quality_measure({s, s, s}) << " et en normalized : " << F_1.quality_measure_normalized({s, s, s}) << std::endl;
    std::cout << "La quality_measure pour F2 est : " << F_2.quality_measure({s, s, s}) << " et en normalized : " << F_2.quality_measure_normalized({s, s, s}) << std::endl;
    std::cout << "La quality_measure pour F3 est : " << F_3.quality_measure({s, s, s}) << " et en normalized : " << F_3.quality_measure_normalized({s, s, s}) << std::endl;
    std::cout << std::endl;
    // Quality mesure pour {1 - s, -s, -s}
    std::cout << "La quality_measure pour F1 est : " << F_1.quality_measure({1.0 - s, -s, -s}) << " et en normalized : " << F_1.quality_measure_normalized({1.0 - s, -s, -s}) << std::endl;
    std::cout << "La quality_measure pour F2 est : " << F_2.quality_measure({1.0 - s, -s, -s}) << " et en normalized : " << F_2.quality_measure_normalized({1.0 - s, -s, -s}) << std::endl;
    std::cout << "La quality_measure pour F3 est : " << F_3.quality_measure({1.0 - s, -s, -s}) << " et en normalized : " << F_3.quality_measure_normalized({1.0 - s, -s, -s}) << std::endl;
    
    return 0;
}
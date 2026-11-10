#include "Frame3D.hpp"
#include <cmath>
#include <vector>
#include <cassert>

void Frame3D::display() const {
    for (const auto& v : vectors) {
        std::cout << "(" << v[0] << ", "
            << v[1] << ", "
            << v[2] << ")" << std::endl;
    }
}

// Constructeur par copie : copie les vectors
Frame3D::Frame3D(const Frame3D &f) : vectors(f.vectors) {
}

// Affectation operator
Frame3D &Frame3D::operator=(const Frame3D &f){
	if(&f == this) return *this;

	vectors = f.vectors;
	return *this;
}

size_t Frame3D::size() const{
    return vectors.size();
}

void Frame3D::add(std::vector<double> &v) {
    assert(v.size() > 0.0);

    vectors.push_back(v);
}

Frame3D Frame3D::operator+(const Frame3D &f) const {
    Frame3D result;
    result.vectors = vectors;
    for (const auto &v : f.vectors) {
        result.vectors.push_back(v);
    }
    return result;
}

double Frame3D::quality_measure(const std::vector<double> &v) {
    double max{};
    for (const auto &d : vectors) {
        double prod_scalaire{};
        double norm_v{};
        double norm_d{};
        double quality{};

        for (size_t i{}; i < d.size(); i++) {
            prod_scalaire += v[i]*d[i];
            norm_v += v[i]*v[i];
            norm_d += d[i]*d[i];
        }
        norm_d = sqrt(norm_d);
        norm_v = sqrt(norm_v);
        
        assert(norm_v > 0.0);
        
        quality = prod_scalaire / (norm_d * norm_v);

        if (quality > max) {
            max = quality;
        }
    }
    return max;
}

double Frame3D::quality_measure_normalized(const std::vector<double> &v) {
    assert(vectors.size() > 0);
    
    double q = quality_measure(v);
    q /= static_cast<double>(vectors.size());

    return q;
}
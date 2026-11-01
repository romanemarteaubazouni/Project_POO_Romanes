#include "Frame3D.hpp"

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
    vectors.push_back(v);
}
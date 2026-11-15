#pragma once
#include <iostream>
#include <vector>

template <typename T, int n>
class Frame {
    private:

        std::vector<std::vector<T>> vectors;

    public:
        // A modifier :
        // void display() const {
        //     for (const auto& v : vectors) {
        //         std::cout << "(" << v[0] << ", "
        //             << v[1] << ", "
        //             << v[2] << ")" << std::endl;
        //     }
        // }

        Frame() = default;

        // Constructeur par copie : copie les vectors
        Frame(const Frame &f) : vectors(f.vectors) {
        }

        // Affectation operator
        Frame &operator=(const Frame &f){
            if(&f == this) return *this;

            vectors = f.vectors;
            return *this;
        }

        size_t size() const{
            return vectors.size();
        }

        void add(std::vector<double> &v) {
            assert(v.size() == n);

            vectors.push_back(v);
        }
        // A modifier :
        // Frame operator+(const Frame &f) const {
        //     Frame result;
        //     result.vectors = vectors;
        //     for (const auto &v : f.vectors) {
        //         result.vectors.push_back(v);
        //     }
        //     return result;
        // }

        // double quality_measure(const std::vector<double> &v) {
        //     double max{};
        //     for (const auto &d : vectors) {
        //         double prod_scalaire{};
        //         double norm_v{};
        //         double norm_d{};
        //         double quality{};

        //         for (size_t i{}; i < d.size(); i++) {
        //             prod_scalaire += v[i]*d[i];
        //             norm_v += v[i]*v[i];
        //             norm_d += d[i]*d[i];
        //         }
        //         norm_d = sqrt(norm_d);
        //         norm_v = sqrt(norm_v);
                
        //         assert(norm_v > 0.0);
                
        //         quality = prod_scalaire / (norm_d * norm_v);

        //         if (quality > max) {
        //             max = quality;
        //         }
        //     }
        //     return max;
        // }

        // double quality_measure_normalized(const std::vector<double> &v) {
        //     assert(vectors.size() > 0);
            
        //     double q = quality_measure(v);
        //     q /= static_cast<double>(vectors.size());

        //     return q;
        // }
};
#pragma once
#include <iostream>
#include <vector>

template <typename T, int n>
class Frame {
    private:
        std::vector<std::vector<T>> vectors;

    public:
        Frame() = default;

        ~Frame() = default;
        // Constructeur par copie : copie les vectors
        Frame(const Frame &f) : vectors(f.vectors) {
        }

        void display() const {
            for (const auto& v : vectors) {
                std::cout << "(";
                for (size_t i{} ; i < n; ++i) {
                    std::cout << v[i] << (i + 1 < n ? ", " : "");
                }
                std::cout << ")" << std::endl;
            }
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

        void add(const std::vector<T> &v) {
            assert(v.size() == n);

            T norm_squared{};
            for (const auto &x : v) {
                norm_squared += x * x;
            }

            assert(norm_squared > 0);

            vectors.push_back(v);
        }

        //addition de 2 frames 
        Frame operator+(const Frame &f) const {
            Frame result;
            result.vectors = vectors;
            for (const auto &v : f.vectors) {
                result.vectors.push_back(v);
            }
            return result;
        }

        // Calcul qualitée
        double quality_measure(const std::vector<T> &v) const {
            assert(v.size() == n);
            assert(!vectors.empty());

            double max =-1.0;

            for (const auto &d : vectors) {
                double norm_v{};
                double quality{};
                double prod_scalaire{};
                double norm_d{};

                for (int i{} ; i < n ; i++) {
                    prod_scalaire +=static_cast<double>(v[i]) * d[i];
                    norm_d +=static_cast<double>(d[i])*d[i];
                    norm_v +=static_cast<double>(v[i])*v[i];
                }
                norm_d = std::sqrt(norm_d);
                norm_v =std::sqrt(norm_v);

                assert(norm_v > 0.0);

                quality = prod_scalaire /(norm_d * norm_v);

                if (quality > max) {
                    max = quality;
                }
            }
            return max;
        }

        // Calcul qualitée normalisée
        double quality_measure_normalized(const std::vector<T> &v) const {
            assert(!vectors.empty());

            double q = quality_measure(v);
            q /= static_cast<double>(vectors.size());

            return q;
        }
};
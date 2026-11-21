#pragma once
#include <iostream>
#include <vector>
#include <exception>
#include <string>
#include <cassert>
#include <algorithm>
#include <numeric>

// Part 3, Q a
void turn_primitive(std::vector<int>& v) {
    if (!v.empty()) {
        // On cherche le PGCD global
        int gcd{};
        for (int x : v) {
            gcd = std::gcd(gcd, x);
        }
        // Une fois qu'on a le PGCD, on divise tous les nombres par la PGCD
        if (gcd > 1) {
            for (int &x : v) {
                x /= gcd;
            }
        }
    }
    return;
}

class AddPrimitiveFrameException : public std::exception {
    public:
        virtual const char* what() const noexcept {
            return "Erreur : Une des valeurs du vecteur est trop grand";
        }
};

template <typename T, int n>
class PrimitiveFrame : public Frame<int,n> { // ":public... to inherit"
    private:
        int val_max{};
    public:
        // Constructeur par défaut
        PrimitiveFrame() = default;
        // Constructeur avec val_max (part 3 q d)
        PrimitiveFrame(int max_val) : val_max(max_val) {
        }

        PrimitiveFrame(const Frame<int,n> &frame) {
            for (auto f : frame) {
                turn_primitive(f);
                this->add(f);
            }
        }

        void add(std::vector<int> v) {
            for (int &i : v) {
                if (std::abs(i) > val_max) {
                    throw AddPrimitiveFrameException();
                }
            }

            turn_primitive(v);
            Frame<int, n>::add(v);
        }
};

class AddFrameException : public std::exception {
    public:
        virtual const char* what() const noexcept {
            return "Erreur : La taille du vecteur ne correspond pas à la dimension n";
        }
};

template <typename T, int n>
class MinimalFrame : public Frame<T,n> { // ":public... to inherit"
    public:
        // Constructeur par défaut
        MinimalFrame() = default;

        MinimalFrame(const Frame<T,n> &f) {
            // On parcourt les vecteurs de la frame
            for (const auto &f_v : f.get_vectors()) {
                bool already_here = false;
                // On regarde si il existe dans notre frame (this)
                for (const auto &this_v : this->get_vectors()) {
                    // Si oui, on l'ajoute pas
                    if (this_v == f_v) {
                        already_here = true;
                        break;
                    }
                }
                // Si non, on l'ajoute
                if (!already_here)
                    this->add(f_v);
            }
        }
};

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

        // Getter pour permettre à minimalFrame de lire les vecteurs
        std::vector<std::vector<T>>& get_vectors() const {
            return vectors;
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
            if (v.size() != n) {
                throw AddFrameException();
            }

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
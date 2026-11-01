#pragma once
#include <iostream>
#include <vector>
#include <array>

class Frame3D {
    private:
    // Définition d'une frame
    // A la base : std::vector<std::array<double, 3>> mais pb avec méthode add et push_back
        std::vector<std::vector<double>> vectors;

    public:
        // Constructeur par défaut (exo 1, Q e)
        Frame3D() = default;
        // Pour faciliter l'affichage
        void display() const;

        // Exo 1, Q b (cf struct VectorD)
        // Constructeur par copie
        Frame3D(const Frame3D &f);
        // Destructeur
        ~Frame3D() = default;
        // Overloaded affectation operator
        Frame3D &operator=(const Frame3D &f);

        // Exo 1, Q c
        size_t size() const;

        // Exo 1, Q d
        void add(std::vector<double> &v);

        //Exo 1, Q e
        // Overloaded + operator
        Frame3D operator+(const Frame3D &f) const;

        // Exo 1, Q f
        double quality_measure(const std::vector<double> &v);
};
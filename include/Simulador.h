#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Esfera.h"
#include <cmath>
#include <vector>
#include <utility>

class Simulador {
private:
    double mu; // Coeficiente de fricción cinética
    double g;  // aceleracion de gravedad

    // Metodos internos
    double distMaxNoColision(Esfera a);
    double tiempoYPosColision(Esfera a, Esfera b);
    double DistanciaEntre(Esfera a, Esfera b);



public:

    // Constructores
    Simulador(double mu, double g);


    // Getters
    double getMu() const { return mu; }
    double getG() const { return g; }

    // Setters
    void setMu(double mu) { this->mu = mu; }
    void setG(double g) { this->g = g; }


    // Metodos
    bool colisiona(Esfera a, Esfera b);

    double tiempo_colision(Esfera a, Esfera b);

    double posicion_colision(Esfera a, Esfera b);

    std::pair<double, double>velocidades_post(Esfera a, Esfera b);

    double distancia_final(Esfera e);





};



#endif
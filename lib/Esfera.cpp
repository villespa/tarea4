#include "../include/Esfera.h"
#include <stdexcept>

Esfera::Esfera(double masa, double x0, double v0) {
    if (masa <= 0) {
        throw std::invalid_argument("La masa debe ser positiva.");
    }


    this->masa = masa;
    this->x0 = x0;
    this->v0 = v0;
}


// Getters
double Esfera::getMasa() { return this->masa; }
double Esfera::getPosicionX() { return this->x0; }
double Esfera:: getVelocidad() { return this->v0; }

// Setters
void Esfera::setMasa(double masa) { this->masa = masa; }
void Esfera::setPosicionX(double x0) { this->x0 = x0; }
void Esfera::setVelocidad(double v0) { this->v0 = v0; }


// Metodos

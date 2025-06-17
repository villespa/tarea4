#include "../include/Simulador.h"
#include <cmath>

Simulador::Simulador(double mu, double g) : mu(mu), g(g) {}

//metodos internos
    double Simulador::distMaxNoColision(Esfera a) {
        double va = a.getVelocidad();
        double arriba = va * va;
        double abajo = 2 * mu * g;

        if (abajo == 0) {
            return -1;
        }
        return arriba / abajo;
    }

    double Simulador::DistanciaEntre(Esfera a, Esfera b) {
        double xa = a.getPosicionX();
        double xb = b.getPosicionX();
        return std::abs(xa - xb);
    }

    double Simulador::tiempoColision(Esfera a, Esfera b) {
        double xa = a.getPosicionX();
        double xb = b.getPosicionX();
        double va = a.getVelocidad();
        double vb = b.getVelocidad();

        // Verificar que se mueven una hacia la otra
        double arriba1 = xb - xa;
        double abajo1 = va - vb;
        if (abajo1 <= 0) {
            return -1; 
        }

        double tc = arriba1 / abajo1; 

        // Tiempo que tarda cada esfera en detenerse por fricción
        double tfa = std::abs(va) / (this->mu * this->g);
        double tfb = std::abs(vb) / (this->mu * this->g);

        double tf_min = (tfa < tfb) ? tfa : tfb;
        
        // La colisión sólo ocurre si tc ≤ mín(tf,A, tf,B)
        if (tc > tf_min) {
            return -1; 
        }

        return tc;
    }

    double Simulador::posColicion(Esfera a, Esfera b) {
        double xa = a.getPosicionX();
        double va = a.getVelocidad();

        double tc = this->tiempoColision(a, b);
        if (tc < 0) {
            return -1;
        }
        
        // xc = xA0 + vA0*tc - 0.5*μk*g*tc²
        double xc = xa + va * tc - (0.5 * this->mu * this->g * tc * tc);
        return xc;
    }

    bool Simulador::verificacionDeColicion(Esfera a, Esfera b) {
        double da_max = this->distMaxNoColision(a);
        double db_max = this->distMaxNoColision(b);
        double sumaDistancias = da_max + db_max;
        double distanciaInicial = this->DistanciaEntre(a, b);
        return (sumaDistancias >= distanciaInicial);
    }

    std::pair<double,double> Simulador::velocidadesDespuesChoque(Esfera a, Esfera b) {
        double ma = a.getMasa();
        double mb = b.getMasa();
        double va0 = a.getVelocidad();
        double vb0 = b.getVelocidad();

        if (ma + mb == 0) {
            return std::make_pair(0,0);
        }

        double tc = this->tiempoColision(a, b);
        if (tc < 0) {
            return std::make_pair(0,0);
        }

        // Usar las fórmulas del enunciado con velocidades iniciales
        double vPrimaA = (ma - mb) / (ma + mb) * va0 + (2 * mb) / (ma + mb) * vb0;
        double vPrimaB = (2 * ma) / (ma + mb) * va0 + (mb - ma) / (ma + mb) * vb0;
        
        return std::make_pair(vPrimaA, vPrimaB);
    }

    double Simulador::distanciaPostColicion(Esfera e) {
        double vPrima = e.getVelocidad();
        if (vPrima == 0) {
            return 0;
        }
        double arriba = vPrima * vPrima;
        double abajo = 2 * this->mu * this->g;
        if (abajo == 0) {
            return -1; 
        }
        return arriba / abajo; 
    }

// Metodos publicos
    bool Simulador::colisiona(Esfera a, Esfera b){
        // Solo verificar si colisionan antes de detenerse
        double tc = this->tiempoColision(a, b);
        return (tc >= 0);
    }

    double Simulador::tiempo_colision(Esfera a, Esfera b){
        return this->tiempoColision(a, b);
    }

    double Simulador::posicion_colision(Esfera a, Esfera b){
        return this->posColicion(a, b);
    }

    std::pair<double, double> Simulador::velocidades_post(Esfera a, Esfera b){
        return this->velocidadesDespuesChoque(a, b);
    }

    double Simulador::distancia_final(Esfera e){
        return this->distanciaPostColicion(e);
    }
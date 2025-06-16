#include "../include/Simulador.h"
#include <cmath>

Simulador::Simulador(double mu, double g) : mu(mu), g(g) {}

//metodos internos
    //Distancia máxima sin colisión
    double Simulador::distMaxNoColision(Esfera a) {
        double va = a.getVelocidad();
        double x0a = a.getPosicionX();


        double arriba = va * va;
        double abajo = 2 * mu * g;


        if (abajo == 0) {
            return -1;
        }
        return arriba / abajo;
    }

    // Distancia entre dos esferas
    double Simulador::DistanciaEntre(Esfera a, Esfera b) {
        double xa = a.getPosicionX();
        double xb = b.getPosicionX();
        return std::abs(xa - xb);
    }

    //iempo y posición de colisión (si ocurre): Sean vA0 y vB0 las velocidades iniciales
    //(incluyendo el signo) de las esferas A y B, respectivamente, si asumimos que ambas se mueven
    //el tiempo que tarda cada esfera en detenerse por fricción es: tf,i = vi0/(μₖg)
    double Simulador::tiempoYPosColision(Esfera a, Esfera b) {
        double xa = a.getPosicionX();
        double xb = b.getPosicionX();
        double va = a.getVelocidad();
        double vb = b.getVelocidad();

        double arriba1 = xb - xa;
        double abajo1 = va - vb;
        if (abajo1 <= 0 || va == 0 || vb == 0) {
            return -1; 
        }

        double tc = arriba1 / abajo1; 

        double tfa = std::abs(va) / (this->mu * this->g);
        double tfb = std::abs(vb) / (this->mu * this->g);

        double* tf_min = (tfa < tfb) ? &tfa : &tfb;
        
        //la colisión sólo ocurre si tc ≤ mín(tf,A, tf,B ).
        if (tc > *tf_min) {
            return -1; 
        }

        //a posición de colisión xc se logra calcular con: xc = xA0 + vA0tc − 12 μkgt2c
        double xc = xa + va * tc - (0.5 * this->mu * this->g * tc * tc);
        return xc;

    }

    //Velocidades después del choque: Sea mA y mB la masa de las esferas A y B. Luego del
    //choque elástico, las velocidades finales v′
    //A y v′
    //B se obtienen con:
    //v′
    //A = mA − mB
    //mA + mB
    //vA0 + 2mB
    //mA + mB
    //vB0 , v′
    //B = 2mA
    //mA + mB
    //vA0 + mB − mA
    //mA + mB
    //vB0



    // Distancia recorrida post-colisión: FInalmente, considerando que si una esfera queda con
    //velocidad v′ después del choque, su distancia final antes de detenerse se calcula tal que:
    //d = (v′)2
    //2μkg
    //donde d es la distancia adicional recorrida tras el choque, bajo fricción, hasta detenerse.

// Metodos publicos
    bool Simulador::colisiona(Esfera a, Esfera b){
        double va = a.getVelocidad();
        double vb = b.getVelocidad();

        if (va < 0 && vb < 0) {
            return false;
        }
        if (va > 0 && vb > 0) {
            return false; 
        }

        double da = this->distMaxNoColision(a);
        double db = this->distMaxNoColision(b);

        double xa = a.getPosicionX();
        double xb = b.getPosicionX();

        double distancia = Simulador::DistanciaEntre(a, b);


    }

    double tiempo_colision(Esfera a, Esfera b){

    }

    double posicion_colision(Esfera a, Esfera b){

    }

    std::pair<double, double>velocidades_post(Esfera a, Esfera b){

    }

    double distancia_final(Esfera e){

    }

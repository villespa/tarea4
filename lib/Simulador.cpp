#include "../include/Simulador.h"
#include <cmath>

Simulador::Simulador(double mu, double g) : mu(mu), g(g) {}

//metodos internos
    //Distancia máxima sin colisión
    double Simulador::distMaxNoColision(Esfera a) {
        double va = a.getVelocidad();
        //double x0a = a.getPosicionX();


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
    double Simulador::tiempoColision(Esfera a, Esfera b) {
        double xa = a.getPosicionX();
        double xb = b.getPosicionX();
        double va = a.getVelocidad();
        double vb = b.getVelocidad();

        double arriba1 = xb - xa;
        double abajo1 = va - vb;
        if (abajo1 <= 0) {
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

        return tc; //tiempo de colicion

    }

    double Simulador::posColicion(Esfera a, Esfera b) {
        double xa = a.getPosicionX();
        //double xb = b.getPosicionX();
        double va = a.getVelocidad();
        //double vb = b.getVelocidad();

        double tc = this->tiempoColision(a, b);
        //la posición de colisión xc se logra calcular con: xc = xA0 + vA0tc − 12 μkgt2c
        double xc = xa + va * tc - (0.5 * this->mu * this->g * tc * tc);
        return xc;
    }


    //Verificación de colisión: Sean xA0 y xB0 las posiciones iniciales de las esferas A y B,
    //respectivamente. Definimos la distancia entre ellas al inicio como:
    //D = |xB0 − xA0|
    //Entonces, sea dA,máx la distancia máxima que puede recorrer la esfera A, y dB,máx la corres-
    //pondiente para B. Si la suma de esas distancias es mayor o igual a D, entonces eventualmente
    //colisionarán:
    //dA,máx + dB,máx ≥ D

    bool Simulador::verificacionDeColicion(Esfera a, Esfera b) {
    double xa = a.getPosicionX();
    double xb = b.getPosicionX();
    double va = a.getVelocidad();
    double vb = b.getVelocidad();
    
    // Primero verificar que se muevan una hacia la otra
    if (va - vb <= 0) {
        return false; // No se acercan
    }
    
    // Calcular distancias máximas en la dirección correcta
    double da_max = this->distMaxNoColision(a);
    double db_max = this->distMaxNoColision(b);
    
    // Verificar si pueden cubrirse la distancia inicial
    double distanciaInicial = std::abs(xb - xa);
    return (da_max + db_max >= distanciaInicial);
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
    std::pair<double,double> Simulador::velocidadesDespuesChoque(Esfera a, Esfera b) {
        double ma = a.getMasa();
        double mb = b.getMasa();
        double va0 = a.getVelocidad();
        double vb0 = b.getVelocidad();

        if (ma + mb == 0) {
            return std::make_pair(0,0); // Evitar división por cero
        }

        double tc = this -> tiempoColision(a, b);
        if (tc < 0) {
            return std::make_pair(0,0); // No hay colisión
        }

        double vPrimaA = (ma - mb) / (ma + mb) * va0 + (2 * mb) / (ma + mb) * vb0;
        double vPrimaB = (2 * ma) / (ma + mb) * va0 + (mb - ma) / (ma + mb) * vb0;
        return std::make_pair(vPrimaA, vPrimaB);

    }




    // Distancia recorrida post-colisión: FInalmente, considerando que si una esfera queda con
    //velocidad v′ después del choque, su distancia final antes de detenerse se calcula tal que:
    //d = (v′)2
    //2μkg
    //donde d es la distancia adicional recorrida tras el choque, bajo fricción, hasta detenerse.

    double Simulador::distanciaPostColicion(Esfera e) {
        // usar despues de actualizar atributo de velocidad de la esfera
        double vPrima = e.getVelocidad();
        if (vPrima == 0) {
            return 0; // Si la velocidad es cero, no hay distancia que recorrer
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
        //if (this->verificacionDeColicion(a, b)) {
        double tc = this->tiempoColision(a, b);
        if (tc >= 0) {
            return true;
        }
        //}
        return false;
    }

    double Simulador::tiempo_colision(Esfera a, Esfera b){
        return this->tiempoColision(a, b);
    }

    double Simulador::posicion_colision(Esfera a, Esfera b){
        return this->posColicion(a, b);
    }

    std::pair<double, double> Simulador::velocidades_post(Esfera a, Esfera b){
        std::pair<double, double> velocidades = this->velocidadesDespuesChoque(a, b);
        a.setVelocidad(velocidades.first);
        b.setVelocidad(velocidades.second);
        return std::make_pair(velocidades.first, velocidades.second);
    }

    double Simulador::distancia_final(Esfera e){
        double distancia = this->distanciaPostColicion(e);
        if (distancia < 0) {
            return -1; 
        }
        return distancia;
    }

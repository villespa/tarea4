#ifndef ESFERA_H
#define ESFERA_H

class Esfera {
    double velocidadDeEsfera = 0;
    double acceleracionDeEsfera = 0;
    double radioDeEsfera = 0.0f;
    double masaDeEsfera = 0.0f;
    double coeficienteFriccionCinetica = 0.0f;
    double posicionX = 0;
    double posicionY = 0;
    
    
    // Helper: Calcular distancia máxima que puede recorrer una esfera
    double calcular_distancia_maxima(double velocidad_inicial);
    
    // Helper: Calcular tiempo que tarda en detenerse por fricción
    double calcular_tiempo_frenado(double velocidad_inicial);
    
    // Helper: Verificar si las esferas se mueven en direcciones opuestas
    bool se_mueven_hacia_la_otra(Esfera a, Esfera b);
    
    // Helper: Calcular velocidad en un tiempo dado (con fricción)
    double velocidad_en_tiempo(double v0, double tiempo);
    
    
public:

    // Getters
    double getVelocidad() const { return velocidadDeEsfera; }
    double getAceleracion() const { return acceleracionDeEsfera; }
    double getRadio() const { return radioDeEsfera; }
    double getMasa() const { return masaDeEsfera; }
    double getCoeficienteFriccion() const { return coeficienteFriccionCinetica; }
    double getPosicionX() const { return posicionX; }
    double getPosicionY() const { return posicionY; }

    // Setters
    void setVelocidad(double velocidad) { velocidadDeEsfera = velocidad; }
    void setAceleracion(double aceleracion) { acceleracionDeEsfera = aceleracion; }
    void setRadio(double radio) { radioDeEsfera = radio; }
    void setMasa(double masa) { masaDeEsfera = masa; }
    void setCoeficienteFriccion(double coeficiente) { coeficienteFriccionCinetica = coeficiente; }
    void setPosicion(double x, double y) { posicionX = x; posicionY = y; }


    // Constructores    
    Esfera(double masa = 0.0, double posicionX = 0.0, double velocidad = 0.0, double radio = 0.0);


    // Metodos




};

#endif
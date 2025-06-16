#ifndef ESFERA_H
#define ESFERA_H

class Esfera {
    double v0 = 0;
    double masa = 0.0f;
    double x0 = 0;
    
public:

    // Getters
    double getMasa();  
    double getPosicionX();
    double getVelocidad();

    // Setters
    void setMasa(double masa);
    void setPosicionX(double x0);
    void setVelocidad(double v0);
    


    // Constructores    
    Esfera(double masa = 0.0, double posicionX = 0.0, double velocidad = 0.0);


    // Metodos




};

#endif
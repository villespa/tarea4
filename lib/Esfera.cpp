#include "../include/Esfera.h"

Esfera::Esfera(double masa, double posicionX, double velocidad, double radio) :
    velocidadDeEsfera(velocidad),       
    acceleracionDeEsfera(0),            
    radioDeEsfera(radio),               
    masaDeEsfera(masa),                 
    coeficienteFriccionCinetica(0),     
    posicionX(posicionX),               
    posicionY(0)                        
{}


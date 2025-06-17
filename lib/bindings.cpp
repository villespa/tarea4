#include <pybind11/pybind11.h>
#include "../include/Esfera.h"
#include "../include/Simulador.h"

namespace py = pybind11;

PYBIND11_MODULE(colisiones, m) {
    m.doc() = "Tarea 4";
    
    // Clase Esfera - SOLO exportar el método getRadio()
    py::class_<Esfera>(m, "Esfera")
        .def(py::init<double, double, double>(),  // Constructor básico
            "Constructor:  Esfera(double masa, double x0, double v0)",
            py::arg("masa"), py::arg("x0"), py::arg("v0"))
        .def("getMasa", &Esfera::getMasa,
            "Devuelve el radio de la esfera")
        .def("getPosicionX", &Esfera::getPosicionX,
            "Devuelve la posicion X de la esfera")
        .def("getVelocidad", &Esfera::getVelocidad,
            "Devuelve la velocidad de la esfera")
        .def("setVelocidad", &Esfera::setVelocidad,
            "Establece la velocidad de la esfera",
            py::arg("velocidad"));
          
    
    // Clase Simulador - SOLO exportar el método getG()
    py::class_<Simulador>(m, "Simulador")
        .def(py::init<double, double>(),  // Constructor básico
            "Constructor: Simulador(mu, g)",
            py::arg("mu"), py::arg("g"))
        .def("getG", &Simulador::getG,
            "Devuelve la gravedad de la simulacion")
        .def("getMu", &Simulador::getMu,
            "Devuelve el coeficiente de fricción cinética de la simulacion")
        .def("colisiona", &Simulador::colisiona,
            "Verifica si dos esferas colisionan",
            py::arg("esferaA"), py::arg("esferaB"))
        .def("tiempo_colision", &Simulador::tiempo_colision,
            "Calcula el tiempo de colision entre dos esferas",
            py::arg("esferaA"), py::arg("esferaB"))
        .def("posicion_colision", &Simulador::posicion_colision,
            "Calcula la posicion de colision entre dos esferas",
            py::arg("esferaA"), py::arg("esferaB"))
        .def("velocidades_post", &Simulador::velocidades_post,
            "Calcula las velocidades post colision entre dos esferas",
            py::arg("esferaA"), py::arg("esferaB"))
        .def("distancia_final", &Simulador::distancia_final,
            "Calcula la distancia final de una esfera despues de una colision",
            py::arg("esfera"));
        
}
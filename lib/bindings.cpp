#include <pybind11/pybind11.h>
#include "../include/Esfera.h"
#include "../include/Simulador.h"

namespace py = pybind11;

PYBIND11_MODULE(colisiones, m) {
    m.doc() = "Tarea 4";
    
    // Clase Esfera - SOLO exportar el método getRadio()
    py::class_<Esfera>(m, "Esfera")
        .def(py::init<double, double, double, double>(),  // Constructor básico
             "Constructor:  Esfera(double masa, double posicionX, double velocidad, double radio)",
             py::arg("masa"), py::arg("posicionX"), py::arg("velocidad"), py::arg("radio"))
        .def("getRadio", &Esfera::getRadio,
             "Devuelve el radio de la esfera");
    
    // Clase Simulador - SOLO exportar el método getG()
    py::class_<Simulador>(m, "Simulador")
        .def(py::init<double, double>(),  // Constructor básico
             "Constructor: Simulador(mu, g)",
             py::arg("mu"), py::arg("g"))
        .def("getG", &Simulador::getG,
             "Devuelve la gravedad de la simulacion");
}
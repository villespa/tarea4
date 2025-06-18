#!/usr/bin/env python3


try:
    from colisiones import Esfera, Simulador
    print("Import funciona")
except Exception as e:
    print(f"Error: {e}")
    exit(1)

s = Simulador(0.2, 9.81)
a = Esfera(2, 0, 5)
b = Esfera(1, 10, -3)
if s.colisiona(a, b):
    print("Colisión!")
    print("Ocurre en t =", s.tiempo_colision(a, b), "s")
    print("Posición:", s.posicion_colision(a, b), "m")
    va, vb = s.velocidades_post(a, b)
    print("Velocidades luego del choque:")
    print("A:", va, "m/s")
    print("B:", vb, "m/s")
    print("Distancias finales:")
    print("A:", s.distancia_final(Esfera(2, 0, va)), "m")
    print("B:", s.distancia_final(Esfera(1, 10, vb)), "m")
else:
    print("No colisionan")
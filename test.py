#!/usr/bin/env python3

print("Test PyBind11 - Colisiones")
print("-" * 30)

# Test 1: Importar
try:
    from colisiones import Esfera, Simulador
    print("✓ Importación OK")
except Exception as e:
    print(f"❌ Error: {e}")
    exit(1)

# Test 2: Crear objetos
esfera = Esfera(2.0, 0.0, 5.0)
simulador = Simulador(0.2, 9.81)
print("✓ Objetos creados")

# Test 3: Llamar métodos
radio = esfera.getRadio()
gravedad = simulador.getG()
print(f"✓ Radio: {radio}")
print(f"✓ Gravedad: {gravedad}")

print("\n🎉 ¡Todo funciona!")
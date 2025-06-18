#!/usr/bin/env python3

import time
import random
from colisiones import Esfera, Simulador

def benchmark_original():
    """Tu script original como benchmark"""
    print("🧪 Ejecutando ejemplo original...")
    
    start = time.perf_counter()
    
    s = Simulador(0.2, 9.81)
    a = Esfera(2, 0, 5)
    b = Esfera(1, 10, -3)
    
    if s.colisiona(a, b):
        tc = s.tiempo_colision(a, b)
        xc = s.posicion_colision(a, b)
        va, vb = s.velocidades_post(a, b)
        dist_a = s.distancia_final(Esfera(2, 0, va))
        dist_b = s.distancia_final(Esfera(1, 10, vb))
        resultado = (tc, xc, va, vb, dist_a, dist_b)
    else:
        resultado = None
    
    end = time.perf_counter()
    
    print(f"✅ Tiempo: {(end-start)*1000:.3f}ms")
    return resultado, end-start

def benchmark_repetitivo(n=10000):
    """Benchmark repetitivo del ejemplo"""
    print(f"⚡ Benchmark repetitivo ({n:,} iteraciones)...")
    
    s = Simulador(0.2, 9.81)
    
    start = time.perf_counter()
    
    for i in range(n):
        a = Esfera(2, 0, 5)
        b = Esfera(1, 10, -3)
        
        if s.colisiona(a, b):
            tc = s.tiempo_colision(a, b)
            if i == 0:  # Solo calcular todo en la primera iteración
                xc = s.posicion_colision(a, b)
                va, vb = s.velocidades_post(a, b)
                dist_a = s.distancia_final(Esfera(2, 0, va))
                dist_b = s.distancia_final(Esfera(1, 10, vb))
    
    end = time.perf_counter()
    tiempo_total = end - start
    
    print(f"✅ Total: {tiempo_total:.3f}s")
    print(f"   Promedio: {tiempo_total/n*1000:.3f}ms/iter")
    print(f"   Velocidad: {n/tiempo_total:,.0f} sims/segundo")
    
    return tiempo_total

def benchmark_escenarios():
    """Benchmark de diferentes escenarios físicos"""
    print("📊 Benchmark por escenarios...")
    
    escenarios = [
        ("Ejemplo original", (2, 0, 5), (1, 10, -3)),
        ("Masas iguales", (5, 0, 8), (5, 12, -6)),
        ("Velocidades altas", (1, 0, 20), (1, 15, -15)),
        ("Velocidades bajas", (2, 0, 1), (3, 5, -0.5)),
        ("Masa gigante vs pequeña", (1000, 0, 3), (0.1, 8, -2)),
        ("Fricción alta", (1, 0, 10), (1, 20, -8)),  # μ=0.5
        ("Sin fricción", (1, 0, 5), (1, 10, -3)),     # μ=0.0
        ("Distancia grande", (1, 0, 15), (1, 50, -10)),
        ("Casi no colisionan", (1, 0, 2), (1, 12, -1.5)),
    ]
    
    n_iter = 5000
    
    for nombre, (ma, xa, va), (mb, xb, vb) in escenarios:
        # Ajustar μ para algunos casos
        mu = 0.5 if "alta" in nombre else (0.0 if "Sin fricción" in nombre else 0.2)
        s = Simulador(mu, 9.81)
        
        start = time.perf_counter()
        colisiones = 0
        
        for _ in range(n_iter):
            a = Esfera(ma, xa, va)
            b = Esfera(mb, xb, vb)
            if s.colisiona(a, b):
                colisiones += 1
        
        end = time.perf_counter()
        tiempo = end - start
        
        print(f"  {nombre:25}: {tiempo/n_iter*1000:6.3f}ms/iter, {colisiones:4d}/{n_iter} colisiones ({colisiones/n_iter*100:5.1f}%)")

def benchmark_precision():
    """Benchmark de precisión numérica"""
    print("🎯 Test de precisión...")
    
    s = Simulador(0.2, 9.81)
    
    # Test con el ejemplo conocido
    a = Esfera(2, 0, 5)
    b = Esfera(1, 10, -3)
    
    # Valores esperados (aproximados)
    tc_esperado = 1.25
    xc_esperado = 4.717
    
    start = time.perf_counter()
    
    tc = s.tiempo_colision(a, b)
    xc = s.posicion_colision(a, b)
    va, vb = s.velocidades_post(a, b)
    
    # Verificar conservación de momento
    momento_inicial = 2*5 + 1*(-3)  # = 7
    momento_final = 2*va + 1*vb
    
    end = time.perf_counter()
    
    print(f"  Tiempo de cálculo: {(end-start)*1000:.3f}ms")
    print(f"  tc calculado: {tc:.6f} (esperado: ~{tc_esperado})")
    print(f"  xc calculado: {xc:.6f} (esperado: ~{xc_esperado})")
    print(f"  Error en tc: {abs(tc - tc_esperado):.6f}")
    print(f"  Error en xc: {abs(xc - xc_esperado):.6f}")
    print(f"  Momento inicial: {momento_inicial:.6f}")
    print(f"  Momento final: {momento_final:.6f}")
    print(f"  Conservación: {abs(momento_inicial - momento_final):.6f} (debería ser ~0)")

def main():
    print("🚀 Suite de Benchmark Completa")
    print("=" * 50)
    
    # Test inicial
    resultado, tiempo = benchmark_original()
    if resultado:
        tc, xc, va, vb, dist_a, dist_b = resultado
        print(f"Resultado: tc={tc:.3f}s, xc={xc:.3f}m, va={va:.3f}, vb={vb:.3f}")
        print(f"Distancias: A={dist_a:.4f}m, B={dist_b:.3f}m")
    
    print()
    
    # Benchmarks
    benchmark_repetitivo(10000)
    print()
    
    benchmark_escenarios()
    print()
    
    benchmark_precision()
    
    print("\n🎉 Suite de benchmark completada!")

if __name__ == "__main__":
    main()
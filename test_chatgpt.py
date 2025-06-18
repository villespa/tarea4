#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
from colisiones import Esfera, Simulador

def graficar_simulacion():
    """Crear gráfico de posición vs tiempo"""
    s = Simulador(0.2, 9.81)
    a = Esfera(2, 0, 5)
    b = Esfera(1, 10, -3)
    
    if not s.colisiona(a, b):
        print("No hay colisión para graficar")
        return
    
    tc = s.tiempo_colision(a, b)
    xc = s.posicion_colision(a, b)
    
    # Tiempo antes de la colisión
    t_antes = np.linspace(0, tc, 100)
    
    # Posiciones antes de la colisión
    mu, g = s.getMu(), s.getG()
    xa_antes = 0 + 5*t_antes - 0.5*mu*g*t_antes**2
    xb_antes = 10 + (-3)*t_antes - 0.5*mu*g*t_antes**2
    
    # Velocidades post-colisión
    va_post, vb_post = s.velocidades_post(a, b)
    
    # Tiempo después de la colisión
    t_despues = np.linspace(0, 2, 100)
    xa_despues = xc + va_post*t_despues - 0.5*mu*g*t_despues**2
    xb_despues = xc + vb_post*t_despues - 0.5*mu*g*t_despues**2
    
    # Gráfico
    plt.figure(figsize=(12, 8))
    
    plt.subplot(2, 1, 1)
    plt.plot(t_antes, xa_antes, 'b-', label='Esfera A (antes)', linewidth=2)
    plt.plot(t_antes, xb_antes, 'r-', label='Esfera B (antes)', linewidth=2)
    plt.plot(tc + t_despues, xa_despues, 'b--', label='Esfera A (después)', linewidth=2)
    plt.plot(tc + t_despues, xb_despues, 'r--', label='Esfera B (después)', linewidth=2)
    plt.axvline(x=tc, color='g', linestyle=':', label=f'Colisión (t={tc:.2f}s)')
    plt.axhline(y=xc, color='g', linestyle=':', alpha=0.5)
    plt.xlabel('Tiempo (s)')
    plt.ylabel('Posición (m)')
    plt.title('Simulación de Colisión con Fricción')
    plt.legend()
    plt.grid(True, alpha=0.3)
    
    # Velocidades
    plt.subplot(2, 1, 2)
    va_antes_vel = 5 - mu*g*t_antes
    vb_antes_vel = -3 + mu*g*t_antes
    va_despues_vel = va_post - mu*g*t_despues
    vb_despues_vel = vb_post - mu*g*t_despues
    
    plt.plot(t_antes, va_antes_vel, 'b-', label='Velocidad A (antes)', linewidth=2)
    plt.plot(t_antes, vb_antes_vel, 'r-', label='Velocidad B (antes)', linewidth=2)
    plt.plot(tc + t_despues, va_despues_vel, 'b--', label='Velocidad A (después)', linewidth=2)
    plt.plot(tc + t_despues, vb_despues_vel, 'r--', label='Velocidad B (después)', linewidth=2)
    plt.axvline(x=tc, color='g', linestyle=':', label=f'Colisión')
    plt.xlabel('Tiempo (s)')
    plt.ylabel('Velocidad (m/s)')
    plt.title('Velocidades vs Tiempo')
    plt.legend()
    plt.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    graficar_simulacion()
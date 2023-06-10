/* 
 * File:   VNS.h
 * Author: carlos
 *
 * Created on 5 de junio de 2023, 12:51
 */

#include <vector>

#ifndef VNS_H
#define VNS_H

class VNS {
private:
    std::vector<int> solucion;
    int costeActual;
    const int MAX_ITER = 25;
    
    const int KMAX = 5;
    
    /**
     * @brief Operador de mutación. Implementa la mutación por sublista aleatoria
     * de tamaño fijo.
     * @return Un vector con la solución resultante de aplicar la mutación.
     */
    std::vector<int> mutar();
    
public:
    /**
     * @brief Constructor de la clase. Inicializa todos los parámetros y calcula
     * la solución final. Usa BLP3 con vecindario variable como método de búsqueda.
     * @param flujos Matriz de flujos.
     * @param distancias Matriz de distancias.
     * @param seed Semilla para el motor de números aleatorios.
     */
    VNS(const std::vector<std::vector<int>> & flujos, 
            const std::vector<std::vector<int>> & distancias, int seed);
    
    inline std::vector<int> getSolucion(){return solucion;}
};

#endif /* VNS_H */


/* 
 * File:   BMB.h
 * Author: carlos
 *
 * Created on 29 de mayo de 2023, 19:19
 */

#include <vector>
#include "BLP3.h"

#ifndef BMB_H
#define BMB_H

class BMB {
private:
    const int N = 25;
    int best;
    std::vector<BLP3> soluciones;
    
public:
    /**
     * @brief Constructor de la clase. Inicializa los parámetros y calcula la 
     * solución final. Usa BLP3 como método de búsqueda sobre N soluciones aleatorias.
     * @param flujos Matriz de flujos
     * @param distancias Matriz de distancias
     * @param seed Semilla del motor de números aleatorios.
     */
    BMB(const std::vector<std::vector<int>> & flujos, const std::vector<std::vector<int>> & distancias,
            int seed);
    inline std::vector<int> getSolucion(){return soluciones[best].getSolucion();}
};

#endif /* BMB_H */


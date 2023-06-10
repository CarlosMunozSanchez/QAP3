/* 
 * File:   ILS_ES.h
 * Author: carlos
 *
 * Created on 5 de junio de 2023, 15:09
 */

#include <vector>

#ifndef ILS_ES_H
#define ILS_ES_H

class ILS_ES {
private:
    std::vector<int> solucion;
    int costeActual;
    const int MAX_ITER = 25;
    
    /**
     * @brief Operador de mutación. Implementa la mutación por sublista aleatoria
     * de tamaño fijo.
     * @return Un vector con la solución resultante de aplicar la mutación.
     */
    std::vector<int> mutar();
    
public:
    /**
     * @brief Constructor de la clase. Inicializa todos los parámetros y calcula
     * la solución final. Usa ES como método de búsqueda.
     * @param flujos Matriz de flujos.
     * @param distancias Matriz de distancias.
     * @param seed Semilla para el motor de números aleatorios.
     */
    ILS_ES(const std::vector<std::vector<int>> & flujos, 
            const std::vector<std::vector<int>> & distancias, int seed);
    
    inline std::vector<int> getSolucion(){return solucion;}
    
};
#endif /* ILS_ES_H */




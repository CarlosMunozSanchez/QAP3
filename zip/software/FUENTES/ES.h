/* 
 * File:   ES.h
 * Author: carlos
 *
 * Created on 29 de mayo de 2023, 12:22
 */

#include <vector>

#ifndef ES_H
#define ES_H

class ES {
private:
    //Temperatura
    float TINICIAL;
    const float TFINAL = 0.0001;
    float T;
    float B;
    
    //control
    int MAX_VECINOS;
    int MAX_EXITOS;
    int MAX_ITER;
    
    //solucion
    std::vector<int> solucion;
    
    /**
     * @brief Actualiza el valor de la temperatura siguiendo el esquema de 
     * Cauchy modificado
     */
    void enfriar();
    
    /**
     * @brief Implementa los bucles de control del algoritmo
     * @param flujos Matriz de flujos
     * @param distancias Matriz de distancias
     */
    void simularEnfriamiento(const std::vector<std::vector<int>> & flujos, 
            const std::vector<std::vector<int>> & distancias);
    
    /**
     * @brief Calcula la diferencia entre dos soluciones mediante la factorización
     * de las soluciones al intercambial i por j
     * @param i Indice i
     * @param j Indice j
     * @param flujos Matriz de flujos
     * @param distancias Matriz de distancias
     * @return La diferenia de coste entre la solución original y la resultante 
     * tras la permutación de i y j
     */
    int comprobarMovimiento(int i, int j, const std::vector<std::vector<int>> & flujos, 
        const std::vector<std::vector<int>> & distancias);
    
    /**
     * @brief Modifica la solución para aplicar la permutación entre los indices
     * i y j
     * @param i Indice i
     * @param j Indice j
     */
    void aplicarMovimiento(int i, int j);

public:
    /**
     * @brief Constructor de la clase. Inicializa los parámetros y llama al método
     * simular_enfriamiento para obtener la solución final. Parte desde una 
     * solución aleatoria.
     * @param flujos Matriz de flujos.
     * @param distancias Matriz de distancias.
     * @param seed Semilla para el motor de números aleatorios.
     * @param MAX_EVAL Máximo número de evaluaciones permitido.
     */
    ES(const std::vector<std::vector<int>> & flujos, const std::vector<std::vector<int>> & distancias,
            int seed, int MAX_EVAL = 50000);
    
    /**
     * @brief Constructor de la clase. Inicializa los parámetros y llama al método
     * simular_enfriamiento para obtener la solución final. Parte desde una 
     * solución determinada.
     * @param inicial La solución incial desde la que partir.
     * @param flujos Matriz de flujos.
     * @param distancias Matriz de distancias.
     * @param seed Semilla para el motor de números aleatorios.
     * @param MAX_EVAL Máximo número de evaluaciones permitido.
     */
    ES(const std::vector<int> & inicial, const std::vector<std::vector<int>> & flujos, 
    const std::vector<std::vector<int>> & distancias, int seed, int MAX_EVAL = 50000);
    
    inline std::vector<int> getSolucion(){return solucion;}
    
    
};

#endif /* ES_H */


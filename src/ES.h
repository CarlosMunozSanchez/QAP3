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
    
    
    void enfriar();
    void simularEnfriamiento(const std::vector<std::vector<int>> & flujos, 
            const std::vector<std::vector<int>> & distancias);
    int comprobarMovimiento(int i, int j, const std::vector<std::vector<int>> & flujos, 
        const std::vector<std::vector<int>> & distancias);
    void aplicarMovimiento(int i, int j);

public:
    ES(const std::vector<std::vector<int>> & flujos, const std::vector<std::vector<int>> & distancias,
            int seed);
    
    inline std::vector<int> getSolucion(){return solucion;}
    
    
};

#endif /* ES_H */


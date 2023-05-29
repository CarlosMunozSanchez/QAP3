/* 
 * File:   ES.h
 * Author: carlos
 *
 * Created on 29 de mayo de 2023, 12:22
 */

#ifndef ES_H
#define ES_H

class ES {
private:
    //Temperatura
    const float TFINAL = 0.0001;
    float T;
    float B;
    
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
    
};

#endif /* ES_H */


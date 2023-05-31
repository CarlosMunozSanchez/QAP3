/* 
 * File:   ILS.h
 * Author: carlos
 *
 * Created on 31 de mayo de 2023, 18:15
 */
#include <vector>

#ifndef ILS_H
#define ILS_H

class ILS {
private:
    std::vector<int> solucion;
    int costeActual;
    const int MAX_ITER = 25;
    
    std::vector<int> mutar();
    
public:
    ILS(const std::vector<std::vector<int>> & flujos, 
            const std::vector<std::vector<int>> & distancias, int seed);
    
    inline std::vector<int> getSolucion(){return solucion;}
    
};

#endif /* ILS_H */


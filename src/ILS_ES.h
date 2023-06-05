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
    
    std::vector<int> mutar();
    
public:
    ILS_ES(const std::vector<std::vector<int>> & flujos, 
            const std::vector<std::vector<int>> & distancias, int seed);
    
    inline std::vector<int> getSolucion(){return solucion;}
    
};
#endif /* ILS_ES_H */




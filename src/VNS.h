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
    
    std::vector<int> mutar();
    
public:
    VNS(const std::vector<std::vector<int>> & flujos, 
            const std::vector<std::vector<int>> & distancias, int seed);
    
    inline std::vector<int> getSolucion(){return solucion;}
};

#endif /* VNS_H */


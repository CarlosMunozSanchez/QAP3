/* 
 * File:   BMB.h
 * Author: carlos
 *
 * Created on 29 de mayo de 2023, 19:19
 */

#ifndef BMB_H
#define BMB_H

#include <vector>
#include "QAPBL.h"

class BMB {
private:
    const int N = 25;
    std::vector<int> best;
    std::vector<QAPBL> soluciones;
    
public:
    BMB(const std::vector<std::vector<int>> & flujos, const std::vector<std::vector<int>> & distancias,
            int seed);
    inline std::vector<int> getSolucion(){return best;}
};

#endif /* BMB_H */


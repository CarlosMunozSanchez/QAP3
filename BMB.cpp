/* 
 * File:   BMB.cpp
 * Author: carlos
 * 
 * Created on 29 de mayo de 2023, 19:19
 */

#include "BMB.h"

BMB::BMB(const vector<vector<int>> & flujos, const vector<vector<int>> & distancias,
            int seed) {
    
    for(int i = 0; i < N; i++){
        soluciones.emplace(soluciones.end(), flujos, distancias, seed);
        seed++;
    }
    
    
}



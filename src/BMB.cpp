/* 
 * File:   BMB.cpp
 * Author: carlos
 * 
 * Created on 29 de mayo de 2023, 19:19
 */

#include "BMB.h"
#include "funciones.h"
#include <iostream>

using namespace std;

BMB::BMB(const vector<vector<int>> & flujos, const vector<vector<int>> & distancias,
            int seed) {
    
    best = 0;
    int costeMejor = 999999999;
    for(int i = 0; i < N; i++){
        //Obtengo soluciones desde distintos puntos de partida
        soluciones.emplace(soluciones.end(), flujos, distancias, seed);
        seed++;
        //las evaluo y me quedo con la mejor
        float f = 1;
        int c = evaluarSolucion(soluciones[i].getSolucion(), flujos, distancias, f);
        if(c < costeMejor){
            costeMejor = c;
            best = i;
        }
    }
}



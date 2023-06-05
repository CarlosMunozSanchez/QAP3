/* 
 * File:   ES.cpp
 * Author: carlos
 * 
 * Created on 29 de mayo de 2023, 12:22
 */

#include "ES.h"
#include "random.hpp"
#include "funciones.h"
#include <iostream>
#include <cmath>

using namespace std;
// get base random alias which is auto seeded and has static API and internal state
// it is not threads secure, you can also use ::random_thread_local
using Random = effolkronium::random_static;

ES::ES(const vector<vector<int>> & flujos, 
        const vector<vector<int>> & distancias, int seed) {
    
    //inicializar el vector solucion
    solucion.resize(flujos[0].size());
    for(int i = 0; i < solucion.size(); i++){
        solucion[i] = i;
    }    
    
    //inicialización aleatoria
    Random::seed(seed);
    Random::shuffle(solucion);
    
    //Inicialización de parámetros
    
    //Cálculo de la temperatura inicial
    float f = 1;
    TINICIAL = T = (0.3 * evaluarSolucion(solucion, flujos, distancias, f)) / (-log(0.2));
    
    while(T < TFINAL){
        T *= 10;
    }
    
    MAX_VECINOS = 5 * solucion.size();
    MAX_EXITOS = 0.1 * MAX_VECINOS;
    MAX_ITER = 50000 / MAX_VECINOS;
    B = (TINICIAL - TFINAL) / (MAX_ITER * TINICIAL * TFINAL);
    
    simularEnfriamiento(flujos, distancias);    
}

ES::ES(const vector<int> & inicial, const vector<vector<int>> & flujos, 
        const vector<vector<int>> & distancias, int seed) {
    
    //inicializar el vector solucion
    solucion = inicial;
    
    //inicialización aleatoria
    Random::seed(seed);
    
    //Inicialización de parámetros
    
    //Cálculo de la temperatura inicial
    float f = 1;
    TINICIAL = T = (0.3 * evaluarSolucion(solucion, flujos, distancias, f)) / (-log(0.2));
    
    while(T < TFINAL){
        T *= 10;
    }
    
    MAX_VECINOS = 5 * solucion.size();
    MAX_EXITOS = 0.1 * MAX_VECINOS;
    MAX_ITER = 50000 / MAX_VECINOS;
    B = (TINICIAL - TFINAL) / (MAX_ITER * TINICIAL * TFINAL);
    
    simularEnfriamiento(flujos, distancias);    
}


void ES::simularEnfriamiento(const vector<vector<int>> & flujos, 
            const vector<vector<int>> & distancias){
    
    //bucle externo, controla el fin de la ejeución
    int iter = 0;
    int exitos = 1;
    while(T > TFINAL and iter < MAX_ITER and exitos > 0){
        //bucle interno, controla las iteraciones 
        //para un nivel de temperatura concreto
        exitos = 0;
        for(int i = 0; i < MAX_VECINOS and exitos < MAX_EXITOS; i++){
            int v1, v2;
            v1 = Random::get(0, (int)solucion.size()-1);
            
            do{
                v2 = Random::get(0, (int)solucion.size()-1);
            }while(v1 == v2);
            
            int c = comprobarMovimiento(v1, v2, flujos, distancias);
            
            if(c < 0){ //Se ha encontrado una solución mejor
                aplicarMovimiento(v1, v2);
                exitos++;
                //cout << "sustitución directa -> c = " << c << endl;
            } else{ //se comprueba la posibilidad de pasar a una solución peor
                //Obtengo TRUE con probabilidad p
                float p = exp(-c/T);
                bool aceptar = Random::get(p);
                if(aceptar){
                    aplicarMovimiento(v1, v2);
                    exitos++;
                    //cout << "Empeoramiento -> c = " << c << endl;
                }
            }
            
        }
        enfriar();
        iter++;
    }
    /*
    cout << "Estadísticas: " << endl;
    cout << "MAX ITER: " << MAX_ITER << endl;
    cout << "END ITER: " << iter << endl;
    cout << "MAXVECINOS: " << MAX_VECINOS << endl;
    cout << "INIT T: " << TINICIAL << endl;
    cout << "TCOLD: " << TFINAL << endl;
    cout << "LAST T: " << T << endl;
    cout << "B: " << B << endl;
    cout << "MAX SUCCESS: " << MAX_EXITOS << endl;
    cout << "LAST SUCCESS: " << exitos << endl;*
    */
}

void ES::enfriar(){
    T = T / (1 + B*T);
}

int ES::comprobarMovimiento(int i, int j, const vector<vector<int>> & flujos, 
        const vector<vector<int>> & distancias){
    int diferencia = 0;
    
    //factorización del cambio en el coste debido a cambio
    for(int k = 0; k < solucion.size(); k++){
        if(k != i and k != j){
            diferencia +=
            flujos[i][k] * (distancias[solucion[j]][solucion[k]] - distancias[solucion[i]][solucion[k]]) +
            flujos[j][k] * (distancias[solucion[i]][solucion[k]] - distancias[solucion[j]][solucion[k]]) +
            flujos[k][i] * (distancias[solucion[k]][solucion[j]] - distancias[solucion[k]][solucion[i]]) +
            flujos[k][j] * (distancias[solucion[k]][solucion[i]] - distancias[solucion[k]][solucion[j]]);
        }
    }
    
    return diferencia;
}
        
void ES::aplicarMovimiento(int i, int j){
    int aux = solucion[i];
    //permutar i y j
    solucion[i] = solucion[j];
    solucion[j] = aux;    
}
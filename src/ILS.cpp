/* 
 * File:   ILS.cpp
 * Author: carlos
 * 
 * Created on 31 de mayo de 2023, 18:15
 */

#include "ILS.h"
#include "funciones.h"
#include "random.hpp"
#include "QAPBL.h"
#include <iostream>

using namespace std;
// get base random alias which is auto seeded and has static API and internal state
// it is not threads secure, you can also use ::random_thread_local
using Random = effolkronium::random_static;

ILS::ILS(const vector<vector<int>> & flujos, 
            const vector<vector<int>> & distancias, int seed) {
    
    //Genero la primera solución
    QAPBL busqueda(flujos, distancias, seed);
    float f = 1;
    solucion = busqueda.getSolucion();
    costeActual =  evaluarSolucion(solucion, flujos, distancias, f);
    
    for(int i = 0; i < MAX_ITER-1; i++){
        //muto la solución
        vector<int> mutacion = mutar();
        
        //la mejoro con BL
        QAPBL mejorar(mutacion, flujos, distancias, seed);
        
        //Me quedo con la mejor        
        int c = evaluarSolucion(mejorar.getSolucion(), flujos, distancias, f);
        if(c < costeActual){
            solucion = mejorar.getSolucion();
        }      
    }
}

vector<int> ILS::mutar(){
    int p = Random::get(0, (int)solucion.size()-1);
    vector<int> valores;
    
    //escogemos los valores de las posiciones a barajar
    for(int i = 0; i < solucion.size()/3; i++){
        valores.push_back(solucion[p]);
        p = (p + 1) % solucion.size();
    }
    
    //barajo los valores obtenidos
    Random::shuffle(valores);
    
    //Reasigno en una copia de la solucion
    vector<int> resultado = solucion;
    for(int i = 0; i < resultado.size()/3; i++){
        p = (p - 1 + resultado.size()) % resultado.size();
        resultado[p] = valores[i];
    } 
    
    return resultado;
}



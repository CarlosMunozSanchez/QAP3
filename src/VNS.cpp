/* 
 * File:   VNS.cpp
 * Author: carlos
 * 
 * Created on 5 de junio de 2023, 12:51
 */

#include "VNS.h"
#include <vector>
#include "funciones.h"
#include "random.hpp"
#include "BLP3.h"
#include <iostream>

using namespace std;
// get base random alias which is auto seeded and has static API and internal state
// it is not threads secure, you can also use ::random_thread_local
using Random = effolkronium::random_static;

VNS::VNS(const std::vector<std::vector<int>> & flujos, 
            const std::vector<std::vector<int>> & distancias, int seed) {
    
    //Genero la primera solución
    BLP3 busqueda(flujos, distancias, seed, 1, 2000);
    float f = 1;
    solucion = busqueda.getSolucion();
    costeActual =  evaluarSolucion(solucion, flujos, distancias, f);
    int k = 1;
    
    for(int i = 0; i < MAX_ITER-1; i++){
        //muto la solución
        vector<int> mutacion = mutar();
        
        //la mejoro con BL
        BLP3 mejorar(mutacion, flujos, distancias, seed, k, 2000);
        
        //Me quedo con la mejor        
        int c = evaluarSolucion(mejorar.getSolucion(), flujos, distancias, f);
        if(c < costeActual){
            solucion = mejorar.getSolucion();
            k = 1;
        }      
        else{
            k++;
            if(k > KMAX){
                k = 1;
            }
        }
    }
    
}

vector<int> VNS::mutar(){
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


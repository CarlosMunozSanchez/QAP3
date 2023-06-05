/* 
 * File:   QAPBL.cpp
 * Author: carlos
 * 
 * Created on 5 de abril de 2023, 13:18
 * Rework on 19 de mayo de 2023, 13:00
 * Modified for P3 on 5 de junio de 2023, 11:58
 */

#include "BLP3.h"
#include "random.hpp"
#include "funciones.h"
#include <iostream>

using namespace std;
// get base random alias which is auto seeded and has static API and internal state
// it is not threads secure, you can also use ::random_thread_local
using Random = effolkronium::random_static;


BLP3::BLP3(const vector<vector<int>> & flujos, const vector<vector<int>> & distancias, 
        int seed, int k, int MAX_EVAL) {
    //inicializar la máscara dlb
   // dlb.assign(, 0);
    
    solucion.resize(flujos.size());
    this->MAX_EVAL = MAX_EVAL;
    
    //inicializar el vector solucion
    for(int i = 0; i < solucion.size(); i++){
        solucion[i] = i;
    }    
    //inicialización aleatoria
    Random::seed(seed);   
    Random::shuffle(solucion);

    float aux = 1;
    coste = evaluarSolucion(solucion, flujos, distancias, aux);
        
    busquedaLocal(flujos, distancias, k);
}


BLP3::BLP3(const std::vector<int> & inicial, const vector<vector<int>> & flujos, 
        const vector<vector<int>> & distancias, int seed, int k, int MAX_EVAL) {
    //inicializar la máscara dlb
    // dlb.assign(, 0);
    
    solucion = inicial;
    this->MAX_EVAL = MAX_EVAL;

    float aux = 1;
    coste = evaluarSolucion(solucion, flujos, distancias, aux);
        
    busquedaLocal(flujos, distancias, k);
}

int BLP3::comprobarMovimiento(int i, int j, const vector<vector<int>> & flujos, 
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
        
void BLP3::aplicarMovimiento(int i, int j){
    int aux = solucion[i];
    //permutar i y j
    solucion[i] = solucion[j];
    solucion[j] = aux;    
}

void BLP3::busquedaLocal(const vector<vector<int>> & flujos, const vector<vector<int>> & distancias, int k){
    int iter = 0;
    //bool hay_mejora;
   
    //Para llevar la cuenta de cuántos bits de dlb están a 0
    //int dlbStatus = dlb.size();
    
    //Se explora el espacio de soluciones mientras no se supere el umbral MAX_EVAL
    // EN ESTA VERSIÓN NO SE USA DLB
    while(iter < MAX_EVAL /*and dlbStatus > 0*/){
        //ESQUEMA ANTIGUO CON DLB
        /*
         //para cada unidad
        for(int i = 0; i < solucion.size(); i++){
            //se comprueba la máscara
            if(!dlb[i]){
                hay_mejora = false;
                //se busca la primera solución que mejore
                for(int j = 0; j < solucion.size(); j++){
                    int aux = comprobarMovimiento(i, j, flujos, distancias);
                    iter++;
                    //cuando encontremos mejora, la realizamos
                    if(aux < 0){
                        hay_mejora = true;
                        aplicarMovimiento(i, j);
                        
                        //actualizamos los bits
                        if(dlb[i] != false){
                            dlb[i] = false;
                            dlbStatus++;
                        }
                        if(dlb[j] != false){
                            dlb[j] = false;
                            dlbStatus++;
                        }
                    }
                }
                //si no hay mejora
                if(!hay_mejora){
                    dlb[i] = true;
                    dlbStatus--;
                }
            }            
        }
         */
        //ESQUEMA NUEVO CON POSICIONES ALEATORIAS 
        if(k == 1){ //caso normal
            int i = Random::get(0, (int)solucion.size()-1);
            int j = Random::get(0, (int)solucion.size()-1);
            int c = comprobarMovimiento(i, j, flujos, distancias);
        
            //cuando encontremos mejora, la realizamos
            if(c < 0){
                //hay_mejora = true;
                aplicarMovimiento(i, j);
            }
        }
        else{ //casos del VNS
            vector<int> aux = solucion;
            int c = 0;
            
            //intercambio vecinos de dos en dos y voy calculando el cambio en
            //el coste de forma acumulada. Luego, restauro la solución original 
            //y me planteo el cambio
            for(int w = 0; w < k; w++){
                //obtengo dos vecinos
                int i = Random::get(0, (int)solucion.size()-1);
                int j = Random::get(0, (int)solucion.size()-1);
                //acumulo el cambio (uso la factorización)
                c += comprobarMovimiento(i, j, flujos, distancias);
                //aplico el movimiento para seguir acumulando
                aplicarMovimiento(i, j);
            }
            
            //He acabado: compruebo si la solución es ahora mejor
            if(c > 0){//he perdido con los cambios
                //restauro la solución
                solucion = aux;
            }
            //else -> los cambios ya se han realizado y la solución ha mejorado
            
        }
        
        iter++;
    }

    float aux = 1;
    coste = evaluarSolucion(solucion, flujos, distancias, aux);
}

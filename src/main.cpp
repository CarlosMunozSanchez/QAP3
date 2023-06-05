/* 
 * File:   main.cpp
 * Author: carlos
 *
 * Created on 17 de abril de 2023, 18:46
 */
#include <iostream>
#include <chrono>
#include "ES.h"
#include "funciones.h"
#include "BMB.h"
#include "ILS.h"
#include "BLP3.h"
#include "VNS.h"
#include "ILS_ES.h"

using namespace std;
using namespace std::chrono;

/*
 * 
 */
int main(int argc, char** argv){
    
    if(argc < 3 or argc > 4){
        cerr << "Uso: " << argv[0] << " [archivo de datos] [semilla] [archivo de solucion]" << endl;
        exit(-1);
    }
    
    //lectura de datos de entrada
    string entrada(argv[1]);
    int seed = atoi(argv[2]);
    string sol;
    vector<int> optimo;
    int costeOptimo = 1;
    
    if(argc == 4){
        sol = argv[3];
        costeOptimo = leerSolucion(sol, optimo);
    }
    
    vector<vector<int>> flujos, distancias;
    
    leerDatos(entrada, flujos, distancias);
    
    vector<int> solucion;
    
    cout << "---------------------------------------------------------------" << endl;
    cout << "Resultados del archivo " << entrada << endl << endl;
    
    //Enfriamiento simulado
    auto momentoInicio = high_resolution_clock::now();
    ES es(flujos, distancias, seed);
    
    solucion = es.getSolucion();
    auto momentoFin = high_resolution_clock::now();
    
    float fitness = costeOptimo;
    cout << "Solución ES con coste " << evaluarSolucion(solucion, flujos, distancias, fitness) <<
            " y fitness = " << fitness << endl;    
    mostrarVector(solucion);
    
    microseconds tiempo = duration_cast<std::chrono::microseconds>(momentoFin - momentoInicio);
    cout << "Tiempo Pasado (ms): " << tiempo.count() / 1000.0 << endl;
    
    cout << "---------------------------------------------------------------" << endl;
    
    //Búsqueda local Multiarranque Básica
     momentoInicio = high_resolution_clock::now();
    BMB bmb(flujos, distancias, seed);
    
    solucion = bmb.getSolucion();
    momentoFin = high_resolution_clock::now();
    
    fitness = costeOptimo;
    cout << "Solución BMB con coste " << evaluarSolucion(solucion, flujos, distancias, fitness) <<
            " y fitness = " << fitness << endl;    
    mostrarVector(solucion);
    
    tiempo = duration_cast<std::chrono::microseconds>(momentoFin - momentoInicio);
    cout << "Tiempo Pasado (ms): " << tiempo.count() / 1000.0 << endl;
    
    cout << "---------------------------------------------------------------" << endl;
    
    //ILS
    momentoInicio = high_resolution_clock::now();
    ILS ils(flujos, distancias, seed);
    
    solucion = ils.getSolucion();
    momentoFin = high_resolution_clock::now();
    
    fitness = costeOptimo;
    cout << "Solución ILS con coste " << evaluarSolucion(solucion, flujos, distancias, fitness) <<
            " y fitness = " << fitness << endl;    
    mostrarVector(solucion);
    
    tiempo = duration_cast<std::chrono::microseconds>(momentoFin - momentoInicio);
    cout << "Tiempo Pasado (ms): " << tiempo.count() / 1000.0 << endl;
    
    cout << "---------------------------------------------------------------" << endl;
    
    //BL modificada (sin dlb)
     momentoInicio = high_resolution_clock::now();
    BLP3 bl(flujos, distancias, seed);
    
    solucion = bl.getSolucion();
    momentoFin = high_resolution_clock::now();
    
    fitness = costeOptimo;
    cout << "Solución BL modificada p3 (sin dlb) con coste " << evaluarSolucion(solucion, flujos, distancias, fitness) <<
            " y fitness = " << fitness << endl;    
    mostrarVector(solucion);
    
    tiempo = duration_cast<std::chrono::microseconds>(momentoFin - momentoInicio);
    cout << "Tiempo Pasado (ms): " << tiempo.count() / 1000.0 << endl;
    
    cout << "---------------------------------------------------------------" << endl;
    
    //VNS
    momentoInicio = high_resolution_clock::now();
    VNS vns(flujos, distancias, seed);
    
    solucion = vns.getSolucion();
    momentoFin = high_resolution_clock::now();
    
    fitness = costeOptimo;
    cout << "Solución VNS con coste " << evaluarSolucion(solucion, flujos, distancias, fitness) <<
            " y fitness = " << fitness << endl;    
    mostrarVector(solucion);
    
    tiempo = duration_cast<std::chrono::microseconds>(momentoFin - momentoInicio);
    cout << "Tiempo Pasado (ms): " << tiempo.count() / 1000.0 << endl;
    
    cout << "---------------------------------------------------------------" << endl;
    
    //AM 10, 0.1
    momentoInicio = high_resolution_clock::now();
    ILS_ES ils_es(flujos, distancias, seed);
    
    solucion = ils_es.getSolucion();
    momentoFin = high_resolution_clock::now();
    
    fitness = costeOptimo;
    cout << "Solución ILS con ES con coste " << evaluarSolucion(solucion, flujos, distancias, fitness) <<
            " y fitness = " << fitness << endl;    
    mostrarVector(solucion);
    
    tiempo = duration_cast<std::chrono::microseconds>(momentoFin - momentoInicio);
    cout << "Tiempo Pasado (ms): " << tiempo.count() / 1000.0 << endl;
    
    cout << "---------------------------------------------------------------" << endl;
    /*
    //AM 10, mej0.1
     momentoInicio = high_resolution_clock::now();
    AM diezMejores(1, 2, optimo.size(), flujos, distancias, seed);
    
    solucion = diezMejores.getSolucion();
    momentoFin = high_resolution_clock::now();
    
    fitness = costeOptimo;
    cout << "Solución AM con hibridación 10, mej0.1 con coste " << evaluarSolucion(solucion, flujos, distancias, fitness) <<
            " y fitness = " << fitness << endl;    
    mostrarVector(solucion);
    
    tiempo = duration_cast<std::chrono::microseconds>(momentoFin - momentoInicio);
    cout << "Tiempo Pasado (ms): " << tiempo.count() / 1000.0 << endl;
    
    cout << "---------------------------------------------------------------" << endl;
    */
}
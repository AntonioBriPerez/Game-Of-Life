//Ultima modificacion 16-11-2019: 17:39
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include<stdio.h>
#include<cstdlib>
#include<dirent.h>
using namespace std;

typedef vector< vector<size_t> > Patron; // tipo de dato del patron (matriz)
//int numGeneraciones; // variable global del numero de generaciones 


// ** VARIABLES AUXILIARES PARA CALCULAR CÉLULAS VIVAS **

int vivas_centro(Patron &p, int fila, int columna){
    return (p [fila - 1] [columna - 1]  // arriba izquierda
          + p [fila - 1] [columna]      // arriba
          + p [fila - 1] [columna + 1]  // arriba derecha
          + p [fila]     [columna - 1]  // izquierda
          + p [fila]     [columna + 1]  // derecha
          + p [fila + 1] [columna - 1]  // abajo izquierda 
          + p [fila + 1] [columna]      // abajo
          + p [fila + 1] [columna + 1]);// abajo derecha
}

int vivas_derecha(Patron &p, int fila, int columna, int tam){
    return (p [fila - 1] [columna - 1]
          + p [fila - 1] [columna]
          + p [fila - 1] [columna - tam + 1]  // arriba derecha
          + p [fila]     [columna - 1]
          + p [fila]     [columna - tam + 1]  // derecha
          + p [fila + 1] [columna - 1]
          + p [fila + 1] [columna]
          + p [fila + 1] [columna - tam + 1]);// abajo derecha
}

int vivas_izquierda(Patron &p, int fila, int columna, int tam){
    return (p [fila - 1] [columna + tam - 1]  // arriba izquierda
          + p [fila - 1] [columna]      
          + p [fila - 1] [columna + 1]   
          + p [fila]     [columna + tam - 1]  // izquierda
          + p [fila]     [columna + 1]  
          + p [fila + 1] [columna + tam - 1]  // abajo
          + p [fila + 1] [columna]      
          + p [fila + 1] [columna + 1]);
}

int vivas_abajo(Patron &p, int fila, int columna, int tam){
    return (p [fila - 1] [columna - 1]  
          + p [fila - 1] [columna]      
          + p [fila - 1] [columna + 1]  
          + p [fila]     [columna - 1]  
          + p [fila]     [columna + 1]  
          + p [fila - tam + 1] [columna - 1]  // abajo izquierda 
          + p [fila - tam + 1] [columna]      // abajo
          + p [fila - tam + 1] [columna + 1]);// abajo derecha
}

int vivas_arriba(Patron &p, int fila, int columna, int tam){
    return (p [fila + tam - 1] [columna - 1]  // arriba izquierda
          + p [fila + tam - 1] [columna]      // arriba
          + p [fila + tam - 1] [columna + 1]  // arriba derecha
          + p [fila]     [columna - 1]  
          + p [fila]     [columna + 1]  
          + p [fila + 1] [columna - 1]   
          + p [fila + 1] [columna]      
          + p [fila + 1] [columna + 1]);
}

int vivas_esq_arribaizq(Patron &p, int fila, int columna, int tam){
    return (p [fila + tam - 1] [columna + tam - 1]  // arriba izquierda
          + p [fila + tam - 1] [columna]      // arriba
          + p [fila + tam - 1] [columna + 1]  // arriba derecha
          + p [fila]     [columna + tam - 1]  // izquierda
          + p [fila]     [columna + 1]  
          + p [fila + 1] [columna + tam - 1]  // abajo izquierda 
          + p [fila + 1] [columna]      
          + p [fila + 1] [columna + 1]);
}

int vivas_esq_arribader(Patron &p, int fila, int columna, int tam){
    return (p [fila + tam - 1] [columna - 1]  // arriba izquierda
          + p [fila + tam - 1] [columna]      // arriba
          + p [fila + tam - 1] [columna - tam + 1]  // arriba derecha
          + p [fila]     [columna - 1]  
          + p [fila]     [columna - tam + 1]  // derecha
          + p [fila + 1] [columna - 1]  
          + p [fila + 1] [columna]      
          + p [fila + 1] [columna - tam + 1]);// abajo derecha
}

int vivas_esq_abajoizq(Patron &p, int fila, int columna, int tam){
    return (p [fila - 1] [columna + tam - 1]  // arriba izquierda
          + p [fila - 1] [columna]      
          + p [fila - 1] [columna + 1]  
          + p [fila]     [columna + tam - 1]  // izquierda
          + p [fila]     [columna + 1]  
          + p [fila - tam + 1] [columna + tam - 1]  // abajo izquierda 
          + p [fila - tam + 1] [columna]      // abajo
          + p [fila - tam + 1] [columna + 1]);// abajo derecha
}

int vivas_esq_abajoder(Patron &p, int fila, int columna, int tam){
    return (p [fila - 1] [columna - 1]  
          + p [fila - 1] [columna]      
          + p [fila - 1] [columna - tam + 1]  // arriba derecha
          + p [fila]     [columna - 1]  
          + p [fila]     [columna - tam + 1]  // derecha
          + p [fila - tam + 1] [columna - 1]  // abajo izquierda 
          + p [fila - tam + 1] [columna]      // abajo
          + p [fila - tam + 1] [columna - tam + 1]);// abajo derecha
}


// ** GAME OF LIFE **

void gameoflife(Patron &p, int tam){
    Patron g = vector< vector<size_t> >(tam, vector<size_t>(tam,0));
    
    


    int aliveCells = 0;
    // estudiar las casillas
   
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            //  ESQUINAS    
            if(i == 0 && j == 0) // arriba izquierda
                aliveCells = vivas_esq_arribaizq(p, i, j, tam);
            else if(i == 0 && j == tam-1) // arriba derecha
                aliveCells = vivas_esq_arribader(p, i, j, tam);
            else if(i == tam-1 && j == 0) // abajo izquierda
                aliveCells = vivas_esq_abajoizq(p, i, j, tam);
            else if(i == tam-1 && j == tam-1)
                aliveCells = vivas_esq_abajoder(p, i, j, tam);
            // LADOS
            else if(i == 0) // arriba
                aliveCells = vivas_arriba(p, i, j, tam);
            else if(i == tam-1) // abajo
                aliveCells = vivas_abajo(p, i, j, tam);
            else if(j == 0) // izquierda
                aliveCells = vivas_izquierda(p, i, j, tam);
            else if(j == tam-1) // derecha
                aliveCells = vivas_derecha(p, i, j, tam);
            // CENTRO
            else{
                aliveCells = vivas_centro(p, i, j);
            }

            if(p[i][j] == 0) // muerta
                if(aliveCells == 3)
                    g[i][j] = 1;
            
            if(p[i][j] == 1) // viva
                if (aliveCells != 2 && aliveCells != 3)
                    g[i][j] = 0;
                else{
                    g[i][j] = 1;
                }
        }
    }
   
    
 
    // sustituir el patron viejo por el generado
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            p[i][j] = g[i][j];
        }
    }
}

// **  LEE TODOS LOS FICHEROS DEL DIRECTORIO **

void listFile(vector<string> &fnames,string path){
  string name;
        DIR *pDIR;
        struct dirent *entry;
        if( (pDIR=opendir(path.c_str())) ){
                while((entry = readdir(pDIR))){
                        if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
                          name = entry->d_name;
                          fnames.push_back(name);
                        
                      }
                }
                closedir(pDIR);
        }
}

// ** LECTURA DE LOS PATRONES **

void lecturaPatrones(string path,vector<string>fnames,int numGeneraciones){
    double tiempoTotal=0;
    int tam = 0;
    ofstream finalFile;

    finalFile.open("ficheroFinal.out");
    
   
    string auxPath="";
    for(unsigned int i=0; i<path.size();i++){
        if(i>1){
            auxPath.push_back(path[i]);
        }
    }

    for(unsigned int i=0; i<fnames.size();i++){
        string filename=fnames[i];

    //    cout << filename << endl;

        path= auxPath +"/" + filename;



        ifstream file;
        file.open(path);
        
        if(file.is_open()){
            
            while(!file.eof()){ 
                file>>tam;
             //   cout << tam << endl;
                Patron p = vector< vector<size_t> >(tam, vector<size_t>(tam,0)); // lo inicializa con 0 al principio
                for(int i = 0; i < tam; i++){
                    for(int j = 0; j < tam; j++){
                        file >> p[i][j];   
                    }
                }
                /*

                cout << "**** patron inicial ****" << endl;

                for(int i = 0; i < tam; i++){
                    for(int j = 0; j < tam; j++){
                        cout << p[i][j];   
                    }
                    cout << endl;
                }
                cout << endl;*/

                clock_t start, end;
                 start = clock();
                //patron leido -> mandamos a gameoflife
                 //Realizamos la simulación del patron

                for(int i = 0; i < numGeneraciones; i++){
                    gameoflife(p,tam);
                }

                end = clock();
                double tiempo = double(end - start) / double(CLOCKS_PER_SEC);
                tiempoTotal+=tiempo;
                finalFile << i << " " << filename << " " << tam*tam << " " << numGeneraciones;
                finalFile << " " << tiempo << endl;
               
               /* cout << "**** primera generacion ****" << endl;
                for(int i = 0; i < tam; i++){
                    for(int j = 0; j < tam; j++){
                        cout << p[i][j];
                    }
                    cout << endl;
                }
                cout << endl;*/
               
               // llamar al writeFile  
               break;
               
            }

        }
        else{
            cout << "No se pudo abrir el fichero. " << endl;
        }
        path="";

    }
    finalFile << fnames.size() << " ";
    finalFile << tam*tam*fnames.size() * fnames.size()*numGeneraciones;
    finalFile << " "  << tiempoTotal << " " << (tam*tam*fnames.size()*fnames.size()*numGeneraciones)/tiempoTotal;
    finalFile.close();

}







int main(int argc, char **argv){

    if(argc <  2){
        cout << "Error en los argumentos" << endl;
        cout << "./gameoflife directorio numGeneraciones" << endl;
    }
    
    else{
        
        string path = argv[1];
        int numGeneraciones = std::stoi(argv[2]);

    //    cout << "numGeneraciones " << numGeneraciones << endl;
        vector<string> fnames; 
    	listFile(fnames,path);
        lecturaPatrones(path,fnames,numGeneraciones);
    }
}
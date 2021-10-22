#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

void creaPatrones(int tam, int patrones){
    int t, p;
    srand(time(NULL));
    ofstream file;
    clock_t start, end;
    double tiempos[patrones];
    for (int i = 0; i < patrones; i++){

	
		//creacion de matriz con memoria dinamica
		start=clock();
		int** m;
		m = new int*[tam];
		for(int i=0; i<tam; i++){
			m[i] = new int[tam];
		}

		//inicializacion de matriz
		for(int x=0; x < tam; x++){				
			for(int y=0; y < tam; y++){
				m[x][y] = (rand()%2);
			}			
		}
		end = clock();
		

		//guarda matriz en fichero
        file.open("patrones/patron"+std::to_string(i)+".in");
        file<<tam<<"\n";
        for (int x = 0; x < tam; x++){
            for (int y = 0; y < tam; y++){
                file << m[x][y] <<" ";
            }
            file<<"\n";
            
        }

        double tiempo = double(end - start) / double(CLOCKS_PER_SEC);
        tiempos[i] = tiempo;
        file.close();
    }
    
    file.open("patrones/patterns_report.in");
    double total = 0;
    for (int i = 0; i < patrones; i++){
        //Nº patron, tamanyo, nº celulas, tiempo
        file<<i<<" "<<tam<<" "<<tam*tam<<" "<<tiempos[i]<<"\n";
        total = total + tiempos[i];
    }
    //total patrones, total celulas, total tiempo, media tiempo
    file<<patrones<<" "<<tam*tam*patrones<<" "<<total<<" "<<double(total/patrones);
    file.close();
    
}

/*Primero el tamanyo, segundo la cantidad de patrones a generar.*/
int main(int argc, char *argv[])
{
    if(argc < 2){
    	cout << "Error en los argumentos" << endl;
    	return 0;
    }
    int tam = std::stoi(argv[1]);
    int patrones = std::stoi(argv[2]);
    //clock_t start, end;
    //start=clock();
    creaPatrones(tam, patrones);
    //end = clock();
    //double tiempo = double(end - start) / double(CLOCKS_PER_SEC);
    //cout << "Tiempo: " << fixed << tiempo << endl;

    return 0;
    
}

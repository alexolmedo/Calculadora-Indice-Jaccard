#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm> 
#include <iomanip>
#include <cstdio>
#include <ctime>
#include <omp.h>

using namespace std;
vector<vector<string>> compuestos;
vector <map<char,int>> mapCaracteres;
std::string res;

int main() 
{
    //Mostrar hora de inicio
    time_t now = time(0);
    tm* horaLocal = localtime(&now);
    cout << "Hora de inicio: " << asctime(horaLocal) << endl;

    std::clock_t inicio;
    double duracion;
    inicio = std::clock();
    //Llenar vector con nombre del compuesto y su string
    ifstream input("ZINC_chemicals.tsv");
    char const limite_linea = '\n';
    char const limite_campo = '\t';

    int numLinea = 0;
    for (string linea; getline(input, linea, limite_linea); ) {
        if (numLinea != 0){
            compuestos.push_back(vector<vector<string>>::value_type());
            istringstream ss(linea);
            int columna = 0;
            for (string campo; getline(ss, campo, limite_campo); ) {
                if (columna!=2 && columna!=0){
                    compuestos.back().push_back(campo);
                }
                columna++;            
            }
        }
        numLinea++;
    }
    //Llenar otro vector con frecuencia de cada caracter
    for (int i=0; i<compuestos.size();i++){
        map <char, int> elementos;
        int longitud = compuestos[i][1].length();
        for(int j=0; j < longitud; j++){
            ++elementos[compuestos[i][1][j]] ;
        }
        mapCaracteres.push_back(elementos);
    }

    //Eliminar caracteres no válidos del diccionario de frecuencias
    char noValidos[]={'[', ']', '(', ')', '-', '+', '=', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i=0; i<mapCaracteres.size();i++){
        for(const char &letra : noValidos){
            mapCaracteres[i].erase(letra);
        }
    }

    //Agregar el numero total de elementos al vector
    for (int i=0; i<mapCaracteres.size(); i++){
        int numElementos = 0;
        for(map<char,int>::const_iterator it = mapCaracteres[i].begin();
        it != mapCaracteres[i].end(); ++it){
            numElementos += it->second ;
        }
        compuestos[i].push_back(to_string(numElementos));
    }
    
    //Calcular el coeficiente de jaccard y hacer append a un string
    
    FILE* fout = fopen("solution_cpp.tsv", "w");
    fprintf(fout, "compound_a\tcompound_b\tvalue\n");
    omp_set_num_threads(4);
    #pragma omp for ordered schedule(static,4)
    for (int i=0; i<compuestos.size(); i++){
        for(int j=i+1; j<compuestos.size(); j++){
            int elementosComunes = 0;
            for(map<char,int>::const_iterator it = mapCaracteres[i].begin();
            it != mapCaracteres[i].end(); ++it){
                if(mapCaracteres[j].count(it->first)>0){
                    elementosComunes += min(mapCaracteres[i][it->first],mapCaracteres[j][it->first]);
                }
            }
            double indiceJaccard = elementosComunes / (atof(compuestos[i][2].c_str())+atof(compuestos[j][2].c_str())-elementosComunes);
            //Tomar solo dos decimales
            stringstream stream;
            stream << fixed << setprecision(2) << indiceJaccard;
            string dosDecimales = stream.str();
            //Guardar los resultados en orden
            #pragma omp ordered 
            res.append(compuestos[i][0]+"\t"+compuestos[j][0]+"\t"+dosDecimales+"\n");
        }
    }
    //Escribir string de resultados a archivo
    fprintf(fout, "%s", res.c_str());
    fclose(fout);
        
    duracion = ( std::clock() - inicio ) / (double) CLOCKS_PER_SEC;
    cout << duracion <<" segundos\n";
    cout << duracion/60 <<" minutos\n";
}
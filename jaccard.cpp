#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm> 

using namespace std;

int main() 
{
    //Llenar vector con nombre del compuesto y su string
    vector<vector<string>> compuestos;
    ifstream input("ZINC_chemicals_test.tsv");
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
    vector <map<char,int>> mapCaracteres;
    for (int i=0; i<compuestos.size();i++){
        map <char, int> elementos;
        int longitud = compuestos[i][1].length();
        for(int j=0; j < longitud; j++){
            ++elementos[compuestos[i][1][j]] ;
        }
        mapCaracteres.push_back(elementos);
    }

    //Eliminar caracteres no válidos del diccionario de frecuencias
    char noValidos[]={'[', ']', '(', ')', '-', '+', '=', '/'};
    for (int i=0; i<mapCaracteres.size();i++){
        for(const char &letra : noValidos){
            mapCaracteres[i].erase(letra);
        }
    }

    //Agregar el numero total de elementos al arreglo
    for (int i=0; i<mapCaracteres.size(); i++){
        int numElementos = 0;
        for(map<char,int>::const_iterator it = mapCaracteres[i].begin();
        it != mapCaracteres[i].end(); ++it){
            numElementos += it->second ;
        }
        compuestos[i].push_back(to_string(numElementos));
    }
    
    for (int i=0; i<compuestos.size(); i++){
        for(int j=i+1; j<compuestos.size(); j++){
            int elementosComunes = 0;
            for(map<char,int>::const_iterator it = mapCaracteres[i].begin();
            it != mapCaracteres[i].end(); ++it){
                if(mapCaracteres[j].count(it->first)>0){
                    elementosComunes += min(mapCaracteres[i][it->first],mapCaracteres[j][it->first]);
                }
            }
            cout << compuestos[i][1] << " , " << compuestos[j][1]<<" , "<<elementosComunes<<endl;
        }
    }

    
    


    //Imprimir todos los elementos del vector
    /*for (int i=0; i<compuestos.size();i++){
        cout << compuestos[i][1] + " " + compuestos[i][2] ;
        cout << endl;
        for(map<char,int>::const_iterator it = mapCaracteres[i].begin();
        it != mapCaracteres[i].end(); ++it)
        {
            std::cout << it->first << " " << it->second << "\n";
        }*
    }*/

}
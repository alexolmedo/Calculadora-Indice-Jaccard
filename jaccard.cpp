#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

int main() 
{
    //Llenar vector con nombre del compuesto y su string
    vector<vector<string>> compuestos;
    ifstream input("ZINC_chemicals_test.tsv");
    char const limite_linea = '\n';
    char const limite_campo = '\t';
    for (string linea; getline(input, linea, limite_linea); ) {
        compuestos.push_back(vector<vector<string>>::value_type());
        istringstream ss(linea);
        int index = 0;
        for (string campo; getline(ss, campo, limite_campo); ) {
            if (index!=2 && index!=0){
                compuestos.back().push_back(campo);
            }
            index++;            
        }
    }
    //Llenar vector con frecuencia de cada caracter
    vector <map<char,int>> mapCaracteres;
    for (int i=0; i<compuestos.size();i++){
        map <char, int> elementos;
        int longitud = compuestos[i][1].length();
        for(int j=0; j < longitud; j++){
            ++elementos[compuestos[i][1][j]] ;
        }
        mapCaracteres.push_back(elementos);
    }

    //Imprimir todos los elementos del vector
    for (int i=0; i<compuestos.size();i++){
        cout << compuestos[i][1] + " ";
        cout << endl;
    }
}
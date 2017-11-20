#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() 
{
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

    //Imprimir todos los elementos del vector
    for (int i=0; i<compuestos.size();i++){
        for (int j=0; j<compuestos[i].size();j++){
            cout << compuestos[i][j] + " ";
        }
        cout << endl;
    }
}
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() 
{
    typedef vector<vector<string> > Compuestos;
    Compuestos compuestos;
    ifstream input("ZINC_chemicals_test.tsv");
    char const limite_linea = '\n';
    char const limite_campo = '\t';
    for (string linea; getline(input, linea, limite_linea); ) {
        compuestos.push_back(Compuestos::value_type());
        istringstream ss(linea);
        for (string campo; getline(ss, linea, limite_campo); ) {
            cout << linea << endl;
            compuestos.back().push_back(linea);
        }
    }
}
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

string linea;
string texto;

int main() {
	
	ifstream archivo("documento.txt");
	
	while (getline(archivo,linea)){
    texto=texto+linea+"\n";
	}
	archivo.close();
	cout<< texto << endl;
	
	return 0;
}

#include "header.cc"

class Lector {
    private:
        vector <string> elementos;
        string terminal;
        vector <string> produccion;
    public:
        Lector(string);
        string getTerminal();
        vector <string> getElementos();
        static vector <string> lectura();
        ~Lector();
    private:
        void generaTerminal();
        void generaElementos();
};

Lector::Lector(string produccion) {
    string aux;
    for(unsigned int i = 0; i < produccion.size(); i++) {
        aux = produccion[i];
        if((int)produccion[i] >= 97 && (int)produccion[i] <= 122) { //no terminales
            this->produccion.push_back(aux);
        }
        else {
            while(i+1 != produccion.size() && (int)produccion[i+1] >= 48 && (int)produccion[i+1] <= 57) {
                aux += produccion[i+1];
                i++;
            }
            this->produccion.push_back(aux);
        }
    }
    terminal = "";
}

void Lector::generaTerminal() {
    for(unsigned int i = 0; i < produccion.size(); i++) {
        if(produccion[i] == "-") {
            produccion.erase(produccion.begin(), produccion.begin()+i+2);
            break;
        }
        terminal += produccion[i];
    }
}

void Lector::generaElementos() {
    for(unsigned int i = 0; i < produccion.size(); i++) {
        elementos.push_back(produccion[i]);
    }
}
//retorna el elemento Terminal de la producción
string Lector::getTerminal() {
    generaTerminal();
    return this->terminal;
}
//retorna el resto de elementos que produce la producción
vector <string> Lector::getElementos() {
    generaElementos();
    return this->elementos;
}

vector <string> Lector::lectura() {
    vector <string> v;
    ifstream archivo;
    string produccion;

    archivo.open("gramatica0.txt", ios::in);
    if(archivo.fail()) {
        cout << "Ha ocurrido un error al tratar de abrir el archivo de la gramática" << endl;
        exit(1);
    }

    while(!archivo.eof()) {
        getline(archivo,produccion);
        if(produccion == "") continue;
        v.push_back(produccion);
    }
    archivo.close();
    //v.erase(v.begin()+v.size()); //quitar la cadena vacía
    return v;
}

Lector::~Lector() {
    terminal = "";
    if(!elementos.empty()) elementos.clear();
    if(!produccion.empty()) produccion.clear();
}

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
//retorna el resto de elementos que produce la produccion
vector <string> Lector::getElementos() {
    generaElementos();
    return this->elementos;
}

Lector::~Lector() {
    terminal = "";
    if(!elementos.empty()) elementos.clear();
    if(!produccion.empty()) produccion.clear();
}

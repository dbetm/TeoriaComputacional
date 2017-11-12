#include "header.cc"

class Lector {
    private:
        vector <char> elementos;
        string terminal;
        vector <char> produccion;
    public:
        Lector(string);
        string getTerminal();
        vector <char> getElementos();
        ~Lector();
    private:
        void generaTerminal();
        void generaElementos();
};

Lector::Lector(string produccion) {
    for(unsigned int i = 0; i < produccion.size(); i++) {
        this->produccion.push_back(produccion[i]);
    }
    terminal = "";
}

void Lector::generaTerminal() {
    for(unsigned int i = 0; i < produccion.size(); i++) {
        if(produccion[i] == '-') {
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
//retorn el resto de elementos que produce la produccion
vector <char> Lector::getElementos() {
    generaElementos();
    return this->elementos;
}

Lector::~Lector() {
    terminal = "";
    if(!elementos.empty()) elementos.clear();
    if(!produccion.empty()) produccion.clear();
}

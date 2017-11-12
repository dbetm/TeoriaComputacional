#include "Lector.cxx"
#include "header.cc"
// Programa que lleva a la forma normal de Chomsky determinada gramática

struct Pro {
    string terminal;
    vector <string> elementos;
};

class Normalizer {
    private:
        vector <Pro> gramatica;
        vector <Pro> gramE1; // gramática etapa 1
        vector <Pro> gramF; // gramática etapa final
        unsigned int actualA; //al generar nuevas producciones se usará la A_##
    public:
        Normalizer();
        void leerGramatica(unsigned int, vector <string>);
        void mostrarGramaticaFinal();
        //Etapa 1 (a)
        void buscarFormaSimple();
        //Etapa 1 (b)
        void compilarNoTerminales();
        void generarTerminales(vector <char>);
        //Etapa 1 (c)
        void sustituir(unsigned int);
        char buscarEnGramE1(unsigned int, char);
        ~Normalizer();
};

Normalizer::Normalizer() {
    actualA = 1;
}

void Normalizer::leerGramatica(unsigned int numPro, vector <string> pros) {
    Pro aux;
    string produccion;
    for(unsigned int i = 0; i < numPro; i++) {
        if(!aux.elementos.empty()) aux.elementos.clear();
        // -- cout << "Escriba la producción (ej. A->abcDA): ";
        produccion = pros[i];
        //Instanciando un nuevo objeto de la clase Lector
        Lector l(produccion);
        aux.terminal = l.getTerminal();
        aux.elementos = l.getElementos();
        gramatica.push_back(aux);
    }

    //mostrando lo que guarda
    for(unsigned int i = 0; i < numPro; i++) {
        cout << gramatica[i].terminal << " -> ";
        for(unsigned int j = 0; j < gramatica[i].elementos.size(); j++) {
            cout << gramatica[i].elementos[j];
        }
        cout << endl;
    }
}

void Normalizer::mostrarGramaticaFinal() {
    for(unsigned int i = 0; i < gramF.size(); i++) {
        cout << gramF[i].terminal << " -> ";
        for(unsigned int j = 0; j < gramF[i].elementos.size(); j++) {
            cout << gramF[i].elementos[j];
        }
        cout << endl;
    }
}

//Etapa 1 (a)
void Normalizer::buscarFormaSimple() { //buscar las que tienen la forma P -> a
    for(unsigned int i = 0; i < gramatica.size(); i++) {
        if(gramatica[i].elementos.size() == 1) {
            gramE1.push_back(gramatica[i]);
            gramatica.erase(gramatica.begin()+i);
            i--;
        }
    }

    //mostrando lo que guarda
    cout << endl;
    for(unsigned int i = 0; i < gramE1.size(); i++) {
        cout << gramE1[i].terminal << " -> ";
        for(unsigned int j = 0; j < gramE1[i].elementos.size(); j++) {
            cout << gramE1[i].elementos[j];
        }
        cout << endl;
    }
}

//Etapa 1 (b)
void Normalizer::compilarNoTerminales() {
    vector <char> noTerminales;
    for(unsigned int i = 0; i < gramatica.size(); i++) {
        for(unsigned int j = 0; j < gramatica[i].elementos.size(); j++) {
            if((int)gramatica[i].elementos[j] >= 97 && (int)gramatica[i].elementos[j] <= 122) {
                if(find(noTerminales.begin(), noTerminales.end(), gramatica[i].elementos[j]) == noTerminales.end()) //para evitar duplicados
                    noTerminales.push_back(gramatica[i].elementos[j]);
            }
        }
    }
    // --Test display
    cout << endl;
    for(unsigned int i = 0; i < noTerminales.size(); i++) {
        cout << noTerminales[i] << " ";
    }
    cout << endl;
    generarTerminales(noTerminales);
}

void Normalizer::generarTerminales(vector <char> noTerminales) {
    Pro Aux;
    unsigned int ref = gramE1.size() - 1;
    for(unsigned int i = 0; i < noTerminales.size(); i++) {
        Aux.terminal = "";
        Aux.terminal += "A_" + to_string(actualA);
        actualA++;
        Aux.elementos.push_back(noTerminales[i]);
        gramE1.push_back(Aux);
        Aux.elementos.clear();
    }

    sustituir(ref);
}

//Etapa 1 (c)
void Normalizer::sustituir(unsigned int ref) {
    for(unsigned int i = 0; i < gramatica.size(); i++) {
        for(unsigned int j = 0; j < gramatica[i].elementos.size(); j++) {
            if((int)gramatica[i].elementos[j] >= 97 && (int)gramatica[i].elementos[j] <= 122) {
                gramatica[i].elementos[j] = buscarEnGramE1(ref, gramatica[i].elementos[j]);
            }
        }
        gramE1.push_back(gramatica[i]);
    }

    // -Test
    cout << endl;
    for(unsigned int i = ref; i < gramE1.size(); i++) {
        cout << gramE1[i].terminal << " -> ";
        for(unsigned int j = 0; j < gramE1[i].elementos.size(); j++) {
            cout << gramE1[i].elementos[j];
        }
        cout << endl;
    }
}
//Retorna el Terminal generado
char Normalizer::buscarEnGramE1(unsigned int ref, char elemento) {
    for(unsigned int i = 0; i < gramE1.size(); i++) {
        if(gramE1[i].elementos.size() == 1) {
            if(elemento == gramE1[i].elementos[0]) return gramE1[i].terminal[0];
        }
    }
    return '#';
}

Normalizer::~Normalizer() {
    if(!gramatica.empty()) gramatica.clear();
    if(!gramE1.empty()) gramE1.clear();
    if(!gramF.empty()) gramF.clear();
}

int main(int argc, char const *argv[]) {
    Normalizer n1;
    vector <string> pros;
    pros.push_back("S->maAcaA");
    pros.push_back("S->maBca");
    pros.push_back("S->macaA");
    pros.push_back("S->maca");
    pros.push_back("B->maB");
    pros.push_back("B->ma");
    pros.push_back("A->aCdA");
    pros.push_back("A->aCd");
    pros.push_back("C->y");
    n1.leerGramatica(pros.size(), pros);
    n1.buscarFormaSimple();
    n1.compilarNoTerminales();

    return 0;
}

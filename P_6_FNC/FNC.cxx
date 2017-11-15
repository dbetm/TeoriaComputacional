#include "Lector.cxx"
#include "header.cc"
// Programa que lleva a la forma normal de Chomsky determinada gramática

vector <string> lectura();

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
        string buscarEnGramE1(unsigned int, char); //busca elementos de producciones generadas
        //Etapa 2 (a)
        void agregarElementosNormalizados();
        //Etapa 2 (b)
        void generarPares(); //los va generando e incluyendo en el vector gramática final
        string generarTerminalE2();
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
    // for(unsigned int i = 0; i < numPro; i++) {
    //     cout << gramatica[i].terminal << " -> ";
    //     for(unsigned int j = 0; j < gramatica[i].elementos.size(); j++) {
    //         cout << gramatica[i].elementos[j];
    //     }
    //     cout << endl;
    // }
}

void Normalizer::mostrarGramaticaFinal() {
    for(unsigned int i = 0; i < gramF.size(); i++) {
        cout << " " << gramF[i].terminal << " ->\t";
        for(unsigned int j = 0; j < gramF[i].elementos.size(); j++) {
            cout << gramF[i].elementos[j] << " ";
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
}

//Etapa 1 (b)
void Normalizer::compilarNoTerminales() {
    vector <char> noTerminales;
    for(unsigned int i = 0; i < gramatica.size(); i++) {
        for(unsigned int j = 0; j < gramatica[i].elementos.size(); j++) {
            if(gramatica[i].elementos[j].size() == 1) {
                if((int)gramatica[i].elementos[j][0] >= 97 && (int)gramatica[i].elementos[j][0] <= 122) {
                    if(find(noTerminales.begin(), noTerminales.end(), gramatica[i].elementos[j][0]) == noTerminales.end()) //para evitar duplicados
                    noTerminales.push_back(gramatica[i].elementos[j][0]);
                }
            }
        }
    }
    // // --Test display
    // cout << endl;
    // for(unsigned int i = 0; i < noTerminales.size(); i++) {
    //     cout << noTerminales[i] << " ";
    // }
    // cout << endl;
    generarTerminales(noTerminales);
}

void Normalizer::generarTerminales(vector <char> noTerminales) {
    Pro Aux;
    string aux;
    unsigned int ref = gramE1.size() - 1; //referencia para que al hacer las sustituciones solo se tomen en cuenta la generadas
    for(unsigned int i = 0; i < noTerminales.size(); i++) {
        Aux.terminal = "";
        aux = "";
        Aux.terminal += "A" + to_string(actualA);
        actualA++;
        aux += noTerminales[i];
        Aux.elementos.push_back(aux);
        gramE1.push_back(Aux);
        Aux.elementos.clear();
    }

    sustituir(ref);
}

//Etapa 1 (c)
void Normalizer::sustituir(unsigned int ref) {
    for(unsigned int i = 0; i < gramatica.size(); i++) {
        for(unsigned int j = 0; j < gramatica[i].elementos.size(); j++) {
            if(gramatica[i].elementos[j].size() == 1) {
                if((int)gramatica[i].elementos[j][0] >= 97 && (int)gramatica[i].elementos[j][0] <= 122) {
                    gramatica[i].elementos[j] = buscarEnGramE1(ref, gramatica[i].elementos[j][0]);
                }
            }
        }
        gramE1.push_back(gramatica[i]);
    }

    // -Test
    // cout << "\nPrimera etapa finalizada" << endl;
    // for(unsigned int i = ref; i < gramE1.size(); i++) {
    //     cout << gramE1[i].terminal << " -> ";
    //     for(unsigned int j = 0; j < gramE1[i].elementos.size(); j++) {
    //         cout << gramE1[i].elementos[j] << " ";
    //     }
    //     cout << endl;
    // }
}
//Retorna el Terminal generado
string Normalizer::buscarEnGramE1(unsigned int ref, char elemento) {
    for(unsigned int i = 0; i < gramE1.size(); i++) {
        if(gramE1[i].elementos.size() == 1) {
            if(elemento == gramE1[i].elementos[0][0]) return gramE1[i].terminal;
        }
    }
    return "#";
}

//Etapa 2 (a)
void Normalizer::agregarElementosNormalizados() { //ejemplo A1 -> a o A -> bA1;
    for(unsigned int i = 0; i < gramE1.size(); i++) {
        if(gramE1[i].elementos.size() == 2 || gramE1[i].elementos.size() == 1) {
            gramF.push_back(gramE1[i]);
            gramE1.erase(gramE1.begin()+i);
            i--;
        }
    }
}

//Etapa 2 (b)
void Normalizer::generarPares() {
    vector <string> AuxTerm;
    string term;
    for(unsigned int i = 0; i < gramE1.size(); i++) {
        term = gramE1[i].terminal;
        for(unsigned int j = 0; j < gramE1[i].elementos.size() - 1; j++) {
            Pro Aux;
            Aux.terminal = term;
            Aux.elementos.push_back(gramE1[i].elementos[j]);
            if(j < gramE1[i].elementos.size() - 2) term = generarTerminalE2();
            else term = gramE1[i].elementos[j+1];

            Aux.elementos.push_back(term);
            gramF.push_back(Aux);
        }
    }
}

string Normalizer::generarTerminalE2() {
    string terminal = "";
    terminal += "A" + to_string(actualA);
    actualA++;
    return terminal;
}

Normalizer::~Normalizer() {
    if(!gramatica.empty()) gramatica.clear();
    if(!gramE1.empty()) gramE1.clear();
    if(!gramF.empty()) gramF.clear();
}

int main(int argc, char const *argv[]) {
    char opc;
    bool control = true;

    do {
        system("clear");
        vector <string> pros = lectura(); //lee todas los elementos de la produccion de un archivo

        if(pros.size() == 0) {
            cout << "Oh, parece que el archivo donde se encuentra la gramática está vacío" << endl;
            cout << "Modifiquelo y enseguida de enter para continuar...";
            cin.get();
            continue;
        }
        cout << "\tSU GRAMÁTICA ES: " << endl;
        for(unsigned int i = 0; i < pros.size(); i++) {
            cout << " " << pros[i] << endl;
        }
        cout << "PRESIONE ENTER PARA NORMALIZAR..";
        cin.ignore().get();

        cout << "\n\tFORMA NORMAL DE CHOMSKY: " << endl;
        Normalizer n1;
        //Llamada a los métodos del objeto
        n1.leerGramatica(pros.size(), pros); //número de producciones, vector <string> de producciones
        //primera etapa
        n1.buscarFormaSimple();
        n1.compilarNoTerminales();
        //segunda etapa
        n1.agregarElementosNormalizados();
        n1.generarPares();
        n1.mostrarGramaticaFinal();
        cout << "\n (NOTA: Debe modificar el archivo de texto para intentar con otra gramática)" << endl;

        cout << "\n Intentar otra vez (S/N) >> ";
        cin >> opc;
        if(opc == 'S' || opc == 's') {
            system("nano gramatica1.txt");
            continue;
        }
        else break;
    } while(control);
    /*
    Normalizer n1;
    vector <string> pros = lectura();
    pros.push_back("S->maAcaA");
    pros.push_back("S->maBca");
    pros.push_back("S->macaA");
    pros.push_back("S->maca");
    pros.push_back("B->maB");
    pros.push_back("B->ma");
    pros.push_back("A->aCdA");
    pros.push_back("A->aCd");
    pros.push_back("C->y");
    */
    return 0;
}

vector <string> lectura() {
    vector <string> v;
    ifstream archivo;
    string produccion;

    archivo.open("gramatica1.txt", ios::in);
    if(archivo.fail()) {
        cout << "Ha ocurrido un error al tratar de abrir el archivo de la gramática" << endl;
        exit(1);
    }

    while(!archivo.eof()) {
        getline(archivo,produccion);
        v.push_back(produccion);
    }
    archivo.close();
    v.erase(v.begin()+v.size()); //quitar la cadena vacía
    return v;
}

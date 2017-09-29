#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;
typedef unsigned int ui;

int validaEntero();
int menu(string);
string validaExpresionRegular();

struct Transicion { // (q_0, E) -> q1
    ui estado;
    char condicion;
    ui estadoDestino;
};

class Automata {
    private:
        int estadoActual;
        string expresionRegular;
        vector <char> expRegularVector;
        vector <char> Alfabeto;
        vector <Transicion> Delta;
    public:
        Automata(string);
        void compilarAlfabeto();
        void setExpresionRegular(string);
        string getExpresionRegular();
        int getEstadoFinal();
        vector <char> getAlfabeto();
        vector <Transicion> getDelta();
        void generarEstados();
        ~Automata();
    private:
        void asterisco(char);
        void plus(char);
        void interrogacion(char);
        void pipe(char, char);
        void punto();
};

Automata::Automata(string eR) {
    this->expresionRegular = eR;
    estadoActual = 0;
    for (int i = 0; i < eR.length(); i++) {
        expRegularVector.push_back(eR[i]);
    }
}

void Automata::compilarAlfabeto() {
    for(ui i = 0; i < expresionRegular.length(); i++) {
        if(expresionRegular[i] != '*' && expresionRegular[i] != '+' && expresionRegular[i] != '.' && expresionRegular[i] != '?' && expresionRegular[i] != '|')
            Alfabeto.push_back(expresionRegular[i]);
    }
}

void Automata::setExpresionRegular(string eR) {
    this->expresionRegular = eR;
    expRegularVector.clear();
    Alfabeto.clear();
    Delta.clear();
    estadoActual = 0;
    for (int i = 0; i < eR.length(); i++) {
        expRegularVector.push_back(eR[i]);
    }
}

string Automata::getExpresionRegular() {
    return this->expresionRegular;
}

int Automata::getEstadoFinal() {
    return this->estadoActual;
}

vector <char> Automata::getAlfabeto() {
    return this->Alfabeto;
}

vector <Transicion> Automata::getDelta() {
    return this->Delta;
}

void Automata::generarEstados() {
    ui i = 0;
    while(!expRegularVector.empty()) {
        if(expRegularVector[i] == '*' || expRegularVector[i] == '+' || expRegularVector[i] == '?' ) {
            if(expRegularVector[i] == '*') asterisco(expRegularVector[i-1]);
            else if(expRegularVector[i] == '+') plus(expRegularVector[i-1]);
            else interrogacion(expRegularVector[i-1]);

            expRegularVector.erase(expRegularVector.begin(), expRegularVector.begin()+i+1);
            i = 0;
        }
        else if(expRegularVector[i] == '|') {
            pipe(expRegularVector[i-1], expRegularVector[i+1]);
            expRegularVector.erase(expRegularVector.begin(), expRegularVector.begin()+i+2);

        }
        else if(expRegularVector[i] == '.') {
        }
        i++;
    }
}

void Automata::asterisco(char condicion) {
    int estadoAux = estadoActual;
    Transicion aux;
    for(ui i = 0; i < 5; i++) {
        if(i == 0 || i == 1 || i == 2 || i == 3)
            aux.estado = estadoActual;
        if(i == 0 || i == 2 || i == 3 || i == 4)
            aux.condicion = 'E';
        if(i == 0 || i == 1 || i == 3)
            estadoActual++;
        if(i == 1) aux.condicion = condicion;
        if(i == 2) aux.estadoDestino = estadoActual - 1;
        if(i == 0 || i == 1 || i == 3 || i == 4)
            aux.estadoDestino = estadoActual;
        if(i == 4)
            aux.estado = estadoAux;
        Delta.push_back(aux);
    }
}

void Automata::plus(char condicion) {
    Transicion aux;
    for(ui i = 0; i < 4; i++) {
        if(i == 0 || i == 1 || i == 2 || i == 3)
            aux.estado = estadoActual;
        if(i == 0 || i == 2 || i == 3 || i == 4)
            aux.condicion = 'E';
        if(i == 0 || i == 1 || i == 3)
            estadoActual++;
        if(i == 1) aux.condicion = condicion;
        if(i == 2) aux.estadoDestino = estadoActual - 1;
        if(i == 0 || i == 1 || i == 3 || i == 4)
            aux.estadoDestino = estadoActual;
        Delta.push_back(aux);
    }
}

void Automata::interrogacion(char condicion) {
    int estadoAux = estadoActual;
    Transicion aux;
    for(ui i = 0; i < 4; i++) {
        if(i == 0 || i == 1 || i == 2)
            aux.estado = estadoActual;
        if(i == 0 || i == 2 || i == 3)
            aux.condicion = 'E';
        if(i == 0 || i == 1 || i == 2)
            estadoActual++;
        if(i == 1) aux.condicion = condicion;
        if(i == 3) aux.estado = estadoAux;
        aux.estadoDestino = estadoActual;
        Delta.push_back(aux);
    }
}

void Automata::pipe(char x, char y) {
    Transicion aux;
    for(ui i = 0; i < 6; i++) {
        if(i == 0)  aux.estado = estadoActual;
        if(i != 0) aux.estado = estadoActual - 1;
        if(i == 0 || i == 1 || i == 4 || i == 5) {
            aux.condicion = 'E';
        }
        if(i == 2) aux.condicion = x;
        if(i == 3) aux.condicion = y;
        if(i != 5) estadoActual++;
        aux.estadoDestino = estadoActual;
        Delta.push_back(aux);
    }
}

void Automata::punto() {
}

Automata::~Automata() {
    if(!Alfabeto.empty()) Alfabeto.clear();
    if(!Delta.empty()) Delta.clear();
}

int main(int argc, char const *argv[]) {
    int opc;
    bool respuesta, control = true;
    string expresionRegular;
    vector <char> alfabeto;
    vector <Transicion> delta;

    system("clear");
    cout << "\tPARA EMPEZAR\nEscriba una expresión regular: ";
    expresionRegular = validaExpresionRegular();

    Automata a(expresionRegular); // se instancia un nuevo objeto

    do {
        system("clear");
        opc = menu(expresionRegular);
        switch(opc) {
            case 1:
                cout << "Escriba la nueva expresión regular: ";
                expresionRegular = validaExpresionRegular();
                a.setExpresionRegular(expresionRegular);
                cout << "\n¡Hecho!" << endl;
                cin.get();
                break;
            case 2:
                cout << "M = ({";
                //para el alfabeto
                a.compilarAlfabeto();
                alfabeto = a.getAlfabeto();
                for (ui i = 0; i < alfabeto.size(); i++) {
                    if(i + 1 == alfabeto.size()) cout << alfabeto[i] << "} ";
                    else cout << alfabeto[i] << ", ";
                }
                a.generarEstados();
                //Transiciones
                cout << endl;
                delta = a.getDelta();
                for (ui i = 0; i < delta.size(); i++) {
                    cout << "(q" << delta[i].estado << ", " << delta[i].condicion << ")" << " -> " << "q" << delta[i].estadoDestino << endl;
                }
                break;
            case 3:
                control = false;
                break;
            default:
                cout << "¡Opción no válida!" << endl;
                break;
        }
        cout << "\nPresione una tecla para continuar...";
        cin.get();
    } while(control);
    return 0;
}

int menu(string expresion) {
    int opt;
    cout << "\t>> Menú <<\nLa expresión regular es: " << expresion << endl;
    cout << "[1] Nueva expresión regular." << endl;
    cout << "[2] Generar AFND" << endl;
    cout << "[3] Salir." << endl;
    cout << ">> ";
    opt = validaEntero();

    return opt;
}

int validaEntero() {
    int num, ok, ch;
    do {
		fflush(stdout);
		if ((ok = scanf("%d", &num)) == EOF)
		return EXIT_FAILURE;

		if ((ch = getchar()) != '\n') {
    		ok = 0;
    		printf("Vuelva a intentarlo: ");
    		while ((ch = getchar()) != EOF && ch != '\n');
		}
	} while(!ok);

	return num;
}

string validaExpresionRegular() {
    string er;
    bool key = true, control = false;
    int cont = 0;

    while(key) {
        cin >> er;
        control = false;
        cont = 0;
        for(int unsigned i = 0; i < er.length(); i++) {
            if(i < er.length() - 1) { //evitar dos meta-carácteres diferentes
                if(er[i] == er[i+1] && (er[i] != '.' && er[i] != '|' && er[i] != '*' && er[i] != '+' && er[i] != '?')) {
                    cout << "Vuelva a intentarlo: ";
                    control = true;
                    break;
                }
            }

            if(er[i] == '?' || er[i] == '.' || er[i] == '|' || er[i] == '*' || er[i] == '+') {
                cont++;
            }

            if( ((int)er[i] < 97 || (int)er[i] > 122) && ((int)er[i] != 46) && ((int)er[i] != 42) && ((int)er[i] != 43) && ((int)er[i] != 124) && ((int)er[i] != 63)) {
                cout << "Meta-carácter no válido, vuelva a intentarlo: ";
                control = true;
                break;
            }
        }
        if(!control) key = false;
        if(cont == 0 && !control) {
            key = true;
            cout << "Debe tener al menos un meta-carácter: ";
        }
    }
    return er;
}

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
        int estadoInicial;
        string expresionRegular;
        vector <char> Alfabeto;
        vector <Transicion> Delta;
        vector <int> EstadosFinales;
    public:
        Automata(string);
        void compilarAlfabeto();
        void setExpresionRegular(string);
        string getExpresionRegular();
        int getEstadoInicial();
        vector <char> getAlfabeto();
        vector <Transicion> getDelta();
        vector <int> getEstadosFinales();
        ~Automata();
};

Automata::Automata(string eR) {
    this->expresionRegular = eR;
}

void Automata::compilarAlfabeto() {
    for(ui i = 0; i < expresionRegular.length(); i++) {
        if(expresionRegular[i] != '*' && expresionRegular[i] != '+' && expresionRegular[i] != '.' && expresionRegular[i] != '?' && expresionRegular[i] != '|')
            Alfabeto.push_back(expresionRegular[i]);
    }
}

void Automata::setExpresionRegular(string eR) {
    this->expresionRegular = eR;
}

string Automata::getExpresionRegular() {
    return this->expresionRegular;
}

int Automata::getEstadoInicial() {
    return this->estadoInicial;
}

vector <char> Automata::getAlfabeto() {
    return this->Alfabeto;
}

vector <Transicion> Automata::getDelta() {
    return this->Delta;
}

vector <int> Automata::getEstadosFinales() {
    return this->EstadosFinales;
}

Automata::~Automata() {
    if(!Alfabeto.empty()) Alfabeto.clear();
    if(!Delta.empty()) Delta.clear();
    if(!EstadosFinales.empty()) EstadosFinales.clear();
}

int main(int argc, char const *argv[]) {
    int opc;
    bool respuesta, control = true;
    string expresionRegular;
    vector <char> alfabeto;

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

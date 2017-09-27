#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

/* Nombre: David Betancourt Montellano
 * Boleta: 2017670141
 * Fecha: 14/09/2017
 * UA: Teoría computacional
 * Programa académico: ISC
 * Evidencia: Práctica_2 Realización de un programa que reconozca un lenguaje
   determinado.
 * Descripción: Desarrollar un programa de computadora que
   permita leer una expresión regular, una cadena determinada
   y verifique si dicha cadena es aceptada por la expresión
   regular
 * Maestra: M. en Ed. Karina Rodríguez Mejía
 * Grupo: 2CM1.
*/

using namespace std;
//funciones genéricas de estructura básica
int menu(string);
int validaEntero();
string validaExpresionRegular();

class Validator {
    private:
        string expresionRegular;
        string cadena;
        int unsigned posExpresion;
        int unsigned posCadena;
    public:
        Validator(string);
        //Setters and getters
        void setExpresionRegular(string);
        void setCadena(string);
        string getExpresionRegular();
        string getCadena();
        //Método que retorna la respuesta
        bool valida();
        ~Validator();
    private: //otras funciones
        char encuentraMeta();
        int totalMeta();
        //filtros                       //patrones
        bool filtroAsterisco(char);     //  x*, 0  más veces
        bool filtroPlus(char);          // x+, 1 o más veces
        bool filtroPipe(char, char);    // x|y, XOR x^y
        bool filtroQuestion(char);      // x?
        bool filtroPunto(char, char, int);         //a.
};

Validator::Validator(string expresionRegular) {
    this->expresionRegular = expresionRegular;
    this->cadena = "";
    posCadena = 0;
    posExpresion = 0;
}

void Validator::setExpresionRegular(string expresion) {
    this->expresionRegular = expresion;
    posExpresion = 0;
}

void Validator::setCadena(string str) {
    this->cadena = str;
    posCadena = 0;
    posExpresion = 0;
}

string Validator::getExpresionRegular() {
    return this->expresionRegular;
}

string Validator::getCadena() {
    return this->cadena;
}

bool Validator::valida() {
    bool respuesta = true;
    char meta, ultimoMeta = '<';
    int numeroMetas = totalMeta(), cont = 0;
    //se "divide" la expresión regular como bloques, cada bloque se va ir validando
    while(cont < numeroMetas) {
        meta = encuentraMeta();
        switch(meta) {
            case '*':
                if(!filtroAsterisco(expresionRegular[posExpresion - 1])) respuesta = false;
                ultimoMeta = '*';
                cont++;
                break;
            case '+':
                if(!filtroPlus(expresionRegular[posExpresion - 1])) respuesta = false;
                ultimoMeta = '+';
                cont++;
                break;
            case '|':
                if(!filtroPipe(expresionRegular[posExpresion - 1], expresionRegular[posExpresion + 1])) respuesta = false;
                ultimoMeta = '|';
                cont++;
                break;
            case '?':
                if(!filtroQuestion(expresionRegular[posExpresion - 1])) respuesta = false;
                ultimoMeta = '?';
                cont++;
                break;
            case '.':
                if(ultimoMeta == '.') { //caso [...].a.[...]
                    if(!filtroPunto(expresionRegular[posExpresion - 1], expresionRegular[posExpresion + 1], 1)) respuesta = false;
                    cont++;
                }
                else if(ultimoMeta == '<') { //cuando se da el caso a.[...]
                    if(cadena[0] != expresionRegular[posExpresion - 1]) respuesta = false;
                    if(totalMeta() == 1) { //caso simple
                        if(!filtroPunto(expresionRegular[posExpresion - 1], expresionRegular[posExpresion + 1], 0)) respuesta = false;
                        else cont++;
                    }
                }
                ultimoMeta = '.';
                if(expresionRegular[expresionRegular.length()-2] == '.') {
                    cont++;
                }
                break;
        }
        if(!respuesta) break;
    }
    return respuesta;
}
//cuenta la cantidad de meta-carácteres significativos para crear los bloques
int Validator::totalMeta() {
    int total = 0;
    for (int unsigned i = 0; i < expresionRegular.length(); i++) {
        if(expresionRegular[i] == '*' || expresionRegular[i] == '+' || expresionRegular[i] == '?' || expresionRegular[i] == '|')
            total++;
        if((expresionRegular[i] == '.' && expresionRegular[i+2] == '.') || (expresionRegular[i] == '.' && (i+2) == expresionRegular.length())) total++;
    }
    return total;
}

char Validator::encuentraMeta() {
    char meta;
    int unsigned i = posExpresion + 1;
    while(i < expresionRegular.length()) {
        if(expresionRegular[i] == '*') {
            meta = '*';
            break;
        }
        else if(expresionRegular[i] == '+') {
            meta = '+';
            break;
        }
        else if(expresionRegular[i] == '?') {
            meta = '?';
            break;
        }
        else if(expresionRegular[i] == '|') {
            meta = '|';
            break;
        }
        else if(expresionRegular[i] == '.') {
            meta = '.';
            break;
        }
        i++;
    }
    posExpresion = i;
    return meta;
}

bool Validator::filtroAsterisco(char simbolo) {
    int unsigned i = posCadena;
    //cuando es el caso simple -> a*
    if(totalMeta() == 1) {
        for(int unsigned j = posCadena; j < cadena.length(); j++) {
            if(cadena[j] != simbolo && cadena[j] != 'E') return false;
        }
    }
    //cuando está inmerso -> .a*. -> .a* -> a*.
    while(cadena[i] == simbolo || cadena[i] == 'E') {
        i++;
    }
    posCadena = i;
    return true;
}

bool Validator::filtroPlus(char simbolo) {
    int unsigned i = posCadena;
    int unsigned j;
    //cuando es el caso simple -> a+
    if(totalMeta() == 1) {
        for(j = posCadena; j < cadena.length(); j++) {
            if(cadena[j] != simbolo) return false;
        }
        if(posCadena == j) return false;
    }
    //cuando esta inmerso -> .a+. -> .a+ -> a+.
    while(cadena[i] == simbolo) {
        i++;
    }
    if(posCadena == i) return false;
    else posCadena = i;
    return true;
}

bool Validator::filtroPipe(char x, char y) {
    bool respuesta = false;
    char aux;
    if(totalMeta() == 1) { // caso simple x|y
        if(cadena.length() > 1) return false;
        else if(cadena[posCadena] == x || cadena[posCadena] == y) respuesta = true;
    }
    else if(cadena[posCadena] == x || cadena[posCadena] == y) { //caso inmerso
        respuesta = true;
        if(cadena[posCadena] == x) aux = y;
        else aux = x;

        if(cadena[posCadena+1] == aux) return false;
        posCadena++;
    }

    return respuesta;
}

bool Validator::filtroQuestion(char simbol) {
    bool respuesta = true;
    if(totalMeta() == 1) { //Caso simple a?
        if(cadena.length() > 1) return false;
        else if(cadena[posCadena] == simbol || cadena[posCadena] == 'E') respuesta = true;
    }
    else {
        if(simbol == cadena[posCadena] || cadena[posCadena] == 'E') {
            respuesta = true;
            posCadena++;
        }
        if(posExpresion == expresionRegular.length() - 1) {
            if((posCadena-1) != cadena.length() - 1) respuesta = false;
        }
    }
    return respuesta;
}
//Función para el caso simple a.b e inmerso [...].a.[...]
bool Validator::filtroPunto(char x, char y, int opt) { //opt = 1, caso inmerso, opt = 0 caso simple
    bool respuesta = false;
    if(opt == 0) { //caso simple
        if(cadena[0] == x && cadena[1] == y)  {
            respuesta = true;
        }
        if(cadena.length() > 2 || cadena.length() < 1) return false;
    }
    else { //caso inmerso
        if(x == cadena[posCadena]) {
            respuesta = true;
            posCadena++;
        }
    }
    return respuesta;
}

Validator::~Validator() {}

int main(int argc, char const *argv[]) {
    int opc;
    bool respuesta, control = true;
    string expresionRegular, cadena;

    system("clear");
    cout << "\tPARA EMPEZAR\nEscriba una expresión regular: ";
    expresionRegular = validaExpresionRegular();

    Validator v(expresionRegular); // se instancia un nuevo objeto

    do {
        system("clear");
        opc = menu(expresionRegular);
        switch(opc) {
            case 1:
                cout << "Escriba la nueva expresión regular: ";
                expresionRegular = validaExpresionRegular();
                v.setExpresionRegular(expresionRegular);
                cout << "\n¡Hecho!" << endl;
                break;
            case 2:
                cout << "\nLa expresión regular es: " << v.getExpresionRegular() << endl;
                break;
            case 3:
                cout << "\nEscriba la cadena a validar: ";
                cin >> cadena;
                cin.get();
                v.setCadena(cadena);
                respuesta = v.valida();
                cout << "La cadena: " << v.getCadena() << "--> ";
                if(!respuesta) cout << "NO SE ACEPTA." << endl;
                else cout << "SE ACEPTA." << endl;
                break;
            case 4:
                control = false;
                break;
            case 5:
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
    cout << "[2] Ver expresión regular." << endl;
    cout << "[3] Validar cadena." << endl;
    cout << "[4] Salir." << endl;
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

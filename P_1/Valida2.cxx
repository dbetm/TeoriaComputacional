#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int menu(string);

class Validator {
    private:
        string expresionRegular;
        string cadena;
        int posExpresion;
        int posCadena;
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
    cout << numeroMetas << endl;

    while(cont < numeroMetas) {
        meta = encuentraMeta();
        //cout << "Meta: " << meta << endl;
        cout << "En la cadena " << cadena[posCadena] << ", contador es: " << cont << endl;
        switch(meta) {
            case '*':
                if(!filtroAsterisco(expresionRegular[posExpresion - 1])) respuesta = false;
                ultimoMeta = '*';
                cont++;
                cout << "Astérisco dice: " << respuesta << endl;
                break;
            case '+':
                if(!filtroPlus(expresionRegular[posExpresion - 1])) respuesta = false;
                ultimoMeta = '+';
                cont++;
                cout << "Plus dice: " << respuesta << endl;
                break;
            case '|':
                if(!filtroPipe(expresionRegular[posExpresion - 1], expresionRegular[posExpresion + 1])) respuesta = false;
                ultimoMeta = '|';
                cont++;
                cout << "Pipe dice: " << respuesta << endl;
                break;
            case '?':
                if(!filtroQuestion(expresionRegular[posExpresion - 1])) respuesta = false;
                ultimoMeta = '?';
                cont++;
                cout << "Question dice: " << respuesta << endl;
                break;
            case '.':
                if(ultimoMeta == '.') { //caso [...].a.[...]
                    if(!filtroPunto(expresionRegular[posExpresion - 1], expresionRegular[posExpresion + 1], 1)) respuesta = false;
                    cout << "Soy la c rara" << endl;
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
                cout << "Punto: " << respuesta << endl;
                break;
        }
        if(!respuesta) break;
    }
    return respuesta;
}

int Validator::totalMeta() {
    int total = 0;
    for (int i = 0; i < expresionRegular.length(); i++) {
        if(expresionRegular[i] == '*' || expresionRegular[i] == '+' || expresionRegular[i] == '?' || expresionRegular[i] == '|')
            total++;
        if((expresionRegular[i] == '.' && expresionRegular[i+2] == '.') || (expresionRegular[i] == '.' && (i+2) == expresionRegular.length())) total++;
    }
    return total;
}

char Validator::encuentraMeta() {
    char meta;
    int i = posExpresion + 1;
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
    int i = posCadena;
    //cuando es el caso simple -> a*
    if(totalMeta() == 1) {
        for(int j = posCadena; j < cadena.length(); j++) {
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
    int i = posCadena;
    int j;
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
        if(cadena[posCadena == x]) aux = y;
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
        cout << "Hola mundo " << x << " " << y << endl;
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

Validator::~Validator() {

}

int main(int argc, char const *argv[]) {
    int opc;
    bool respuesta, control = true;
    string expresionRegular, cadena;

    system("clear");
    cout << "\tPARA EMPEZAR\nEscriba una expresión regular: ";
    cin >> expresionRegular;

    Validator v(expresionRegular); // se instancia un nuevo objeto

    do {
        system("clear");
        opc = menu(expresionRegular);
        switch(opc) {
            case 1:
                cout << "Escriba la nueva expresión regular: ";
                cin >> expresionRegular;
                v.setExpresionRegular(expresionRegular);
                cout << "\n¡Hecho!" << endl;
                break;
            case 2:
                cout << "\nLa expresión regular es: " << v.getExpresionRegular() << endl;
                break;
            case 3:
                cout << "\nEscriba la cadena a validar: ";
                cin >> cadena;
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
        cin.ignore().get();
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
    cin >> opt;

    return opt;
}

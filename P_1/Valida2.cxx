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
        //filtros
        bool filtroAsterisco(char);
        bool filtroPlus(char);
        bool filtroQuestion(char);
        bool filtroPipe(char);

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
    char meta, ultimoMeta;
    int numeroMetas = totalMeta(), cont = 0;
    cout << numeroMetas << endl;

    while(cont < numeroMetas) {
        meta = encuentraMeta();
        //cout << "Meta: " << meta << endl;
        switch(meta) {
            case '*':
                cout << expresionRegular[posExpresion - 1] << "*" << endl;
                if(!filtroAsterisco(expresionRegular[posExpresion - 1])) respuesta = false;
                ultimoMeta = '*';
                cont++;
                break;
            case '+':
                cout << expresionRegular[posExpresion - 1] << "+" << endl;
                ultimoMeta = '+';
                cont++;
                break;
            case '|':
                cout << expresionRegular[posExpresion - 1] << "|" << expresionRegular[posExpresion + 1] << endl;
                ultimoMeta = '|';
                cont++;
                break;
            case '?':
                cout << expresionRegular[posExpresion - 1] << "?" << endl;
                ultimoMeta = '?';
                cont++;
                break;
            case '.':
                if(ultimoMeta == '.') {
                    cout << expresionRegular[posExpresion - 1] << endl;
                    cont++;
                }
                ultimoMeta = '.';
                posCadena++;
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
    //cuando es el caso simple
    if(totalMeta() == 1) {
        for(int j = posCadena; j < cadena.length(); j++) {
            if(cadena[j] != simbolo && cadena[j] != 'E') return false;
        }
    }

    while(cadena[i] == simbolo || cadena[i] == 'E') {
        i++;
    }
    posCadena = i;

    return true;
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

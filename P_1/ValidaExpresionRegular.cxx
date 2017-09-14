#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int menu();

class Validator {
    private:
        string regularExpression;
        string str;
        int posChars;
    public:
        Validator();
        void setRegularExpression(string);
        void setStr(string);
        string getRegularExpression();
        string getStr();
        bool valida();
        int findMeta(int); //Va buscando meta-carácteres y retorna sus posciones
        bool filterAst(char);
        bool filterPlus(int, char);
        bool filterPipe(char, char);
        bool filterQues(int, char);
        bool filterPoint(int, char, char);
        ~Validator();
};

Validator::Validator() {
    this->regularExpression = "";
    this->str = "";
    posChars = 0;
}

void Validator::setRegularExpression(string expression) {
    this->regularExpression = expression;
}

void Validator::setStr(string str) {
    this->str = str;
    posChars = 0;
}

string Validator::getRegularExpression() {
    return this->regularExpression;
}

string Validator::getStr() {
    return this->str;
}

bool Validator::valida() {
    int pos = 0, aux = 0;
    bool answer = true;
    char latestMeta;
    system("clear");
    while(true) {
        pos = findMeta(pos);
        cout << latestMeta << endl;

        if(aux == pos) break;
        aux = pos;

        switch(regularExpression[pos]) {
            case '*':
                latestMeta = '*';
                if(!filterAst(regularExpression[pos - 1])) {
                    answer = false;
                    cout << "asterisco" << endl;
                }
                break;
            case '+':
                latestMeta = '+';
                if(!filterPlus(pos, regularExpression[pos - 1])) {
                    answer = false;
                    cout << "plus" << endl;
                }
                break;
            case '|':
                latestMeta = '|';
                if(!filterPipe(regularExpression[pos - 1], regularExpression[pos + 1])) {
                    answer = false;
                    cout << "pipe" << endl;
                }
                break;
            case '?':
                latestMeta = '?';
                if(!filterQues(pos, regularExpression[pos - 1])) {
                    cout << "ques" << endl;
                    answer = false;
                }
                break;
            case '.':
            if(latestMeta == '.') posChars++;
                latestMeta = '.';
                break;
        }
        if(answer == false) break;
    }
    return answer;
}
//Se utiliza esta función para encontrar las posiciones de los meta-carácteres  en la expresión regular
int Validator::findMeta(int pos) {

    for(int i = pos + 1; i < regularExpression.length(); i++) {
        if(regularExpression[i] == '*') {
            pos = i;
            break;
        }
        else if(regularExpression[i] == '|') {
            pos = i;
            break;
        }
        else if(regularExpression[i] == '+') {
            pos = i;
            break;
        }
        else if(regularExpression[i] == '?') {
            pos = i;
            break;
        }
        else if(regularExpression[i] == '.') {
            pos = i;
            break;
        }
    }
    return pos;
}

bool Validator::filterAst(char simbol) {
    bool answer = true;
    int i = posChars;

    while(str[i] == simbol || simbol == 'E') {
        i++;
    }
    posChars = i;
    return answer;
}

bool Validator::filterPlus(int pos, char simbol) {
    bool answer = true;
    int cont = 0;
    int i = posChars;
    cout << "Estoy en plus\n" << simbol << endl;

    while(str[i] == simbol) {
        cont++;
        i++;
    }
    posChars = i;
    if(cont < 1) answer = false;

    return answer;
}

bool Validator::filterPipe(char x, char y) {
    bool answer = false;
    char c;
    //cout << str[posChars] << endl;
    if(str[posChars] == x || str[posChars] == y) {
        answer = true;
        if(str[posChars] == x) c = y;
        else c = x;
    }
    if(posChars != str.length() - 1) {
        if(str[posChars + 1] == c) answer = false;
    }
    return answer;
}

bool Validator::filterQues(int pos, char simbol) {
    if(posChars == 0) { //es una situación especial cuando el primer meta-caracter es '?'
        if(str[posChars] == simbol || str[posChars] == 'E') { // E = Epsilon
            //posChars++;
            if(pos == regularExpression.length() - 1) { //si ya es el primer y últmi meta-carácter a evaluar
                for(int i = posChars + 1; i < str.length(); i++) { //si entra al ciclo y no es vacío entonces ya no cumple
                    if(str[i] == 'E') continue; ///tener muchos epsilon da lo mismo
                    return false;
                }
            }
        }
    }
    if(str[posChars] == simbol) posChars++;
    return true;
}

bool Validator::filterPoint(int pos, char simbol, char latestMeta) {
}

Validator::~Validator() {}

int main() {
    int opt;
    bool answer, control = true;
    string regularExpression, str;

    Validator v; // se instancia un nuevo objeto

    do {
        system("clear");
        opt = menu();
        switch(opt) {
            case 1:
                cout << "Escriba la nueva expresión regular: ";
                cin >> regularExpression;
                v.setRegularExpression(regularExpression);
                cout << "¡Hecho!" << endl;
                break;
            case 2:
                cout << "\nLa expresión regular es: " << v.getRegularExpression() << endl;
                break;
            case 3:
                cout << "\nEscriba la cadena a validar: ";
                cin >> str;
                v.setStr(str);
                answer = v.valida();
                cout << "La cadena: " << v.getStr() << "--> ";
                if(!answer) cout << "NO SE ACEPTA." << endl;
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

int menu() {
    int opt;
    cout << "\t>> Menú <<" << endl;
    cout << "[1] Nueva expresión regular." << endl;
    cout << "[2] Ver expresión regular." << endl;
    cout << "[3] Validar cadena." << endl;
    cout << "[4] Salir." << endl;
    cout << ">> ";
    cin >> opt;

    return opt;
}

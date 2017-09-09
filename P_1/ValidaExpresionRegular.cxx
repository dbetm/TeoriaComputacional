#include <iostream>
#include <string>

using namespace std;

class Validator {
    private:
        string regularExpression;
        string str;
        int posChars;
    public:
        Validator();
        void setRegularExpression(string);
        void setStr(string);
        bool valida();
        int findMeta(int); //Va buscando meta-carácteres y retorna sus posciones
        bool filterAst(int, char);
        bool filterPlus(int, char);
        ~Validator();
};

Validator::Validator() {
    this->regularExpression = "";
    this->str = "";
    posChars = 0;
}

void Validator::setRegularExpression(string expression) {
    this->regularExpression = expression;
    cout << this->regularExpression << endl;
}

void Validator::setStr(string str) {
    this->str = str;
}

bool Validator::valida() {
    int pos = 0;
    bool answer = true;

    while(true) {
        pos = findMeta(pos);
        cout << regularExpression[pos] << endl;
        //cout << "La posición en la expresión es: " << pos << endl;
        switch(regularExpression[pos]) {
            case '*':
                if(!filterAst(pos, regularExpression[pos - 1])) {
                    answer = false;
                }
                break;
            case '+':
                if(!filterPlus(pos, regularExpression[pos - 1])) {
                    answer = false;
                }
                break;
            case '|':
                break;
            case '?':
                break;
            default:
                break;
        }
        if(answer == false || pos == regularExpression.length() - 1) {
            break;
        }
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

bool Validator::filterAst(int pos, char simbol) {
    return true;
}

bool Validator::filterPlus(int pos, char simbol) {
    bool answer = true;
    int cont = 0;
    int i = posChars;
    while (str[i] == simbol) {
        cont++;
        i++;
    }
    posChars = i;
    if(cont < 1) answer = false;
    //cout << "Contador vale: " << cont << endl;
    return answer;
}

Validator::~Validator() {}

int main() {
    Validator v;
    bool x;
    v.setRegularExpression("a+.b*.c.b|d.x?");
    v.setStr("aacb");
    x = v.valida();
    if(!x) cout << "No se acepta" << endl;
    else cout << "Se acepta" << endl;

    return 0;
}

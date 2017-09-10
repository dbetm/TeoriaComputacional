#include <iostream>
#include <cstdlib>
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
        string getRegularExpression();
        string getStr();
        bool valida();
        int findMeta(int); //Va buscando meta-carácteres y retorna sus posciones
        bool filterAst(int, char);
        bool filterPlus(int, char);
        bool filterPipe(char, char);
        bool filterQues(char);
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

string Validator::getRegularExpression() {
    return this->regularExpression;
}

string Validator::getStr() {
    return this->str;
}

bool Validator::valida() {
    int pos = 0;
    bool answer = true;
    system("clear");
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
                if(!filterPipe(regularExpression[pos - 1], regularExpression[pos + 1])) {
                    answer = false;
                }
                break;
            case '?':
                if(!filterQues(regularExpression[pos - 1])) answer = false;
                break;
            case '.':
                break;
        }
        //cout << "Aquí estoy" << endl;
        if(answer == false || pos == regularExpression.length() - 1 || pos == regularExpression.length() - 2) {
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
    bool answer = true;
    int i = posChars;

    while(str[i] == simbol) {
        i++;
    }
    posChars = i;
    //cont puede ser 0, por ende la respuesta no se modifica
    //cout << "asterisco dice: " << answer << endl;
    return answer;
}

bool Validator::filterPlus(int pos, char simbol) {
    bool answer = true;
    int cont = 0;
    int i = posChars;
    while(str[i] == simbol) {
        cont++;
        i++;
    }
    posChars = i;
    if(cont < 1) answer = false;
    //cout << "Contador vale: " << cont << endl;
    //cout << "Plus dice: " << answer << endl;
    return answer;
}

bool Validator::filterPipe(char x, char y) {
    bool answer = false;

    if(posChars != 0) posChars++;

    //cout << posChars << endl << x << ", " << y << endl;
    if(str[posChars] == x || str[posChars] == y) {
        //cout << str[posChars] << endl;
        answer = true;
    }
    //cout << "Pipe dice: " << answer << endl;

    if(posChars == 0 && str[posChars+1] == y) {
        answer = false;
    }
    return answer;
}

bool Validator::filterQues(char simbol) {
    if(str[posChars+1] == simbol) {
        posChars++;
    }
    return true;
}

Validator::~Validator() {}

int main() {
    Validator v;
    bool x;

    v.setRegularExpression("x|m.a?.b");
    v.setStr("xmb");

    /*
    v.setRegularExpression("a+.b*.c.b|d.x?");
    v.setStr("bcx");
    */
    x = v.valida();
    cout << "La expresión regular es: " << v.getRegularExpression() << endl;
    cout << "La cadena es: " << v.getStr() << endl;
    if(!x) cout << "No se acepta" << endl;
    else cout << "Se acepta" << endl;

    return 0;
}

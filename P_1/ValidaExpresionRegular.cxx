#include <iostream>
#include <string>

using namespace std;

class Validator {
    private:
        string regularExpression;
        string str;
    public:
        Validator();
        void setRegularExpression(string);
        void setCadena(string);
        bool valida();
        int findMeta(pos); //Va buscando meta-carácteres y retorna sus posciones
        bool filertAst();
        ~Validator();
};

Validator::Validator() {
    this->regularExpression = "";
    this->str = "";
}

void Validator::setRegularExpression(string expression) {
    this->regularExpression = expression;
    cout << this->regularExpression << endl;
}

void Validator::setCadena(string str) {
    this->str = str;
}

bool Validator::valida() {
    int pos = 0
    bool answer = false;

    //while(false) {}
    pos = findMeta(pos);

    switch (regularExpression[pos]) {
        case '*':
            cout << "Encontré un *" << endl;
            break;
        case '+':
            if(!filertAst(pos)) {
                answer = false;
                break;
            }
        case '|':
            break;
        case '?':
            break;
        default:
            break;
    }
    
    return answer;
}

int Validator::findMeta(int pos) {
    for (int i = pos; i < str.size(); i++) {
        if(str[i] == '*') {
            pos = i;
            break;
        }
        else if(str[i] == '|') {
            pos = i;
            break;
        }
        else if(str[i] == '+') {
            pos = i;
            break;
        }
        else if(str[i] == '?') {
            pos = i;
            break;
        }
        else if(str[i] == '.') {
            pos = i;
            break;
        }
    }
    //int posFirstMetaChar = regularExpression.find_first_of("*|+.?");
    return pos;
}

bool Validator::filertAst() {

}

Validator::~Validator(){}

int main() {
    Validator v;
    bool x;
    v.setRegularExpression("a+.b*");
    x = v.valida();
    return 0;
}

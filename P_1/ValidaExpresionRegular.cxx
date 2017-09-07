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
        int findMeta(); //Busca el primer meta-carácter
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
    int pos = findMeta();
    bool answer = false;

    switch (regularExpression[pos]) {
        case '*':
            cout << "Encontré un *" << endl;
            break;
        case '+':
            /*if(!filertAst()) {
                answer = false;
                break;
            }
            */
        case '|':
            break;
        case '?':
            break;
        default:
            break;
    }

    return answer;
}

int Validator::findMeta() {
    int posFirstMetaChar = regularExpression.find_first_of("*|+.?");
    return posFirstMetaChar;
}

Validator::~Validator(){}

int main() {
    Validator v;
    bool x;
    v.setRegularExpression("a+.b*");
    x = v.valida();
    return 0;
}

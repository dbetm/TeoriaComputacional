#include <iostream>
#include <string>

using namespace std;

class Validator {
    private:
        string regularExpression;
        string str;
    public:
        Validator();
        void setRegularExpression(string expression);
        void setCadena(string str);
        bool valida();
        ~Validator();
};

Validator::Validator() {
    this->regularExpression = "";
    this->str = "";
}

int main() {

    return 0;
}

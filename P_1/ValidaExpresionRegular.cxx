#include <iostream>
#include <string>

using namespace std;

class Validator {
    private:
        String regularExpression;
        String str;
    public:
        Validator();
        void setRegularExpression(String expression);
        void setCadena(String str);
        bool valida();
        ~Validator();
};

Validator::Validator() {
    _regularExpression = "";
    _str = "";
}

int main() {

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// Programa que lleva a la forma normal de Chomsky determinada gramática

using namespace std;

struct Pro {
    sting terminal;
    vector <string> noTerminales;
}

class Normalizer {
    private:
        vector <Pro> gramatica;
        vector <Pro> gramE1; // gramática etapa 1
        vector <Pro> gramF; // gramática etapa final
    public:
        Normalizer();
        ~Normalizer();
};

Normalizer::Normalizer() {}

Normalizer::~Normalizer() {}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}

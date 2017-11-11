#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// Programa que lleva a la forma normal de Chomsky determinada gramática

using namespace std;

struct Pro {
    string terminal;
    vector <string> noTerminales;
};

class Normalizer {
    private:
        vector <Pro> gramatica;
        vector <Pro> gramE1; // gramática etapa 1
        vector <Pro> gramF; // gramática etapa final
    public:
        Normalizer();
        void leerGramatica();
        void mostrarGramaticaFinal();
        //Etapa 1 (a)
        Pro buscarFormaSimple();
        void quitarFormaSimple(int index);
        //Etapa 1 (b)
        void compilarNoTerminales();
        void generarTerminales();
        //Etapa 1 (c)
        void sustituir();

        ~Normalizer();
};

Normalizer::Normalizer() {}

Normalizer::~Normalizer() {}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}

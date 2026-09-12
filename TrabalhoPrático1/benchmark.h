#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <string>
#include <vector>

using namespace std;

class benchmark{

public:
    void executar(string caminhoCSV);
    void medirAcessoDiretoVsSequencial(string base, int N);
    void imprimirTabelaRelatorio(vector<benchmark> res);
};

#endif
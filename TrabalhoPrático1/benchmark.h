#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <string>
#include <vector>

using namespace std;

class Benchmark{

public:
    void executar(string caminhoCSV);
    void medirAcessoDiretoVsSequencial(string base, int N);
    void imprimirTabelaRelatorio(vector<Benchmark> res);
};

#endif
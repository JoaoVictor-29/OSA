#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <string>
#include <vector>

using namespace std;

struct Metricas{
    string formato;
    string volume;
    double tamanhoDisco;
    double bytesUteis;
    double eficiencia;
    double tempoLeitura;
};

class Benchmark{

public:
    void executar(string caminhoCSV);
    void medirAcessoDiretoVsSequencial(string base, int N);
    void imprimirTabelaRelatorio(vector<Benchmark> res);
    void imprimirTabelaRelatorio(vector<Metricas> res);
};

#endif
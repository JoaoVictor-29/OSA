#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include "benchmark.h"
#include "gerenciadorArquivo.h"

using namespace std;

void Benchmark::executar(string caminhoCSV){
    vector<Aluno> alunos = GerenciadorArquivo::lerCSV(caminhoCSV);
    auto inicio = chrono::high_resolution_clock::now();

    GerenciadorArquivo::salvarFixo(alunos_fixo.bin,alunos);
    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracao = fim - inicio;
    cout << "Tempo de execução: " << duracao.count() << "ms\n";


}
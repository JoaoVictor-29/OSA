#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include "benchmark.h"
#include "gerenciadorArquivo.h"

using namespace std;

void Benchmark::executar(string caminhoCSV){
    vector<Aluno> alunos = GerenciadorArquivo::lerCSV(caminhoCSV);
    if(alunos.empty()){
        cout << "Erro: Arquivo CSV vazio ou não enconrado! \n";
        return;
    }
    Metricas met;
    met.quantidadeRegistros = alunos.size();
    string arqFixo = "alunos_fixo.bin";
    string arqDelimitado = "alunos_delimitado.bin";
    string arqIndicador = "alunos_indicador.bin";

    using clock = chrono::high_resolution_clock;
    using ms = chrono::duration<double, milli>;

    auto inicio = clock::now();
    GerenciadorArquivo::salvarFixo(arqFixo, alunos);
    auto fim = clock::now();
    met.tempoEscritaFixo = ms(fim - inicio).count();

    inicio =clock::now();
    GerenciadorArquivo::salvarDelimitado(arqDelimitado, alunos);
    fim = clock::now();
    met.tempoEscritaDelimitado = ms(fim - inicio).count();

    inicio = clock::now();
    GerenciadorArquivo::salvarDelimitado(arqIndicador, alunos);
    fim = clock::now();
    met.tempoEscritaIndicador = ms(fim - inicio).count();

    inicio = clock::now();
    vector<Aluno> lidosFixo = GerenciadorArquivo::lerFixo(arqFixo);
    fim = clock::now();
    met.tempoLeituraFixo = ms(fim - inicio).count();

    inicio = clock::now();
    vector<Aluno> lidosDelimitado = GerenciadorArquivo::lerDelimitado(arqDelimitado);
    fim = clock::now();
}
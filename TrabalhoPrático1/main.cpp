#include <iostream>
#include <vector>
#include <string>
#include "benchmark.h"

using namespace std;

int main(){
    Benchmark benchmark;

    vector<string> bases = {"alunos_1k", "alunos_10k", "alunos_50k", "alunos_100k",};

    for(const string&base : bases){
        cout << "Processando: " << base << ".csv" << endl;
        benchmark.executar(base + ".csv");
    }

    cout << "--- O(1) vs O(N)" << endl;

    benchmark.medirAcessoDiretoVsSequencial("alunos_100k", 100000);

    cout << "Testes finalizados!" << endl;

    return 0;
}
#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "benchmark.h"
#include "gerenciadorArquivo.h"
#include "aluno.h"

using namespace std;

void Benchmark::medirAcessoDiretoVsSequencial(string base, int N){
    long long tempoFixo = 0;
    long long tempoDelimitado = 0;

    for(int i = 0; i < 100; i++){
        int rrnAlvo = rand() % N;
        
        auto inicioFixo = chrono::high_resolution_clock::now();

        Aluno alunoTemp;

        GerenciadorArquivo::lerPorRRN(base + "_fixo.bin", rrnAlvo, alunoTemp);

        auto fimFixo = chrono::high_resolution_clock::now();

        tempoFixo += chrono::duration_cast<chrono::microseconds>(fimFixo - inicioFixo).count();

        auto inicioDelimitado = chrono::high_resolution_clock::now();

        ifstream arquivoDelimitado(base + "_delimitado.bin", ios::in | ios:: binary);
        string linha;
        int cont = 0;

        while(getline(arquivoDelimitado, linha)){
            if(cont == rrnAlvo)
                break;
            
            cont++;
        }
        arquivoDelimitado.close();
        auto fimDelimitado = chrono::high_resolution_clock::now();
        tempoDelimitado += chrono::duration_cast<chrono::microseconds>(fimDelimitado - inicioDelimitado).count();
    }

    cout << "Tempo Fixo: " <<  tempoFixo << " microsegundos" << endl;
    cout << "Tempo Delimitado: " <<  tempoDelimitado << " microsegundos" << endl;
}

void Benchmark::imprimirTabelaRelatorio(vector<Metricas> res){
    cout << endl;
    cout << left
         << setw(25) << "Formato Avaliado"
         << setw(15) << "Volume"
         << setw(15) << "Tam. Disco"
         << setw(15) << "Bytes Uteis"
         << setw(15) << "Eficiencia(%)"
         << setw(15) << "Tempo Leitura" << endl;

    cout << string(100, '-') << endl;

    for (const Metricas& m : res) {
        
        std::cout << std::left 
                  << std::setw(25) << m.formato
                  << std::setw(15) << m.volume
                  << std::fixed << std::setprecision(1)
                  << std::setw(11) << m.tamanhoDisco << " KB  "
                  << std::setw(11) << m.bytesUteis << " KB  "
                  << std::setw(13) << m.eficiencia << " %  "
                  << std::setw(11) << m.tempoLeitura << " ms\n";
    }
    std::cout << endl;
}

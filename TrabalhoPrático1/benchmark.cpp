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

void Benchmark::executar(string caminhoCSV){
    vector<Aluno> alunos = GerenciadorArquivo::lerCSV(caminhoCSV);
    if(alunos.empty()){
        cout << "Erro: Arquivo CSV vazio ou não enconrado! \n";
        return;
    }

    string volumeStr = to_string(alunos.size()) + "reg";
    if(alunos.size() == 1000){
        volumeStr = "1.000 reg";
    }else if(alunos.size() == 10000){
        volumeStr = "10.000 reg";
    }else if(alunos.size() == 50000){
        volumeStr = "50.000 reg";
    }else if(alunos.size() == 100000){
        volumeStr = "100.000 reg";
    }

    double bytesUteisTotais = 0;
    for(Aluno& a : alunos){
        bytesUteisTotais += a.getBytesUteis();
    }

    string arqFixo = "_fixo.bin";
    string arqDelimitado = "_delimitado.bin";
    string arqIndicador = "_indicador.bin";

    GerenciadorArquivo::salvarFixo(arqFixo, alunos);
    GerenciadorArquivo::salvarDelimitado(arqDelimitado, alunos);
    GerenciadorArquivo::salvarIndicador(arqIndicador, alunos);

    using clock = chrono::high_resolution_clock;
    using ms = chrono::duration<double, milli>;

    auto inicio = clock::now();
    vector<Aluno> lidosFixo = GerenciadorArquivo::lerFixo(arqFixo);
    auto fim = clock::now();
    double tempoFixo = ms(fim - inicio).count();

    inicio = clock::now();
    vector<Aluno> lidosDelimitado = GerenciadorArquivo::lerDelimitado(arqDelimitado);
    fim = clock::now();
    double tempoDelimitado = ms(fim - inicio).count();

    inicio = clock::now();
    vector<Aluno> lidosIndicador = GerenciadorArquivo::lerIndicador(arqIndicador);
    fim = clock::now();
    double tempoIndicador = ms(fim - inicio).count();

    vector<Metricas> resultadosDaRodada;

    Metricas metFixo;
    metFixo.formato = "Formato 1: Fixo Total";
    metFixo.volume = volumeStr;
    metFixo.bytesUteis = bytesUteisTotais;
    metFixo.tamanhoDisco = GerenciadorArquivo::obterTamanhoArquivo(arqFixo);
    metFixo.eficiencia = (metFixo.bytesUteis / metFixo.tamanhoDisco)*100.0;
    metFixo.tempoLeitura = tempoFixo;
    resultadosDaRodada.push_back(metFixo);

    Metricas metDelimitado;
    metDelimitado.formato = "Formato 2: Delimitado";
    metDelimitado.volume = volumeStr;
    metDelimitado.bytesUteis = bytesUteisTotais;
    metDelimitado.tamanhoDisco = GerenciadorArquivo::obterTamanhoArquivo(arqDelimitado);
    metDelimitado.eficiencia = (metDelimitado.bytesUteis / metDelimitado.tamanhoDisco)*100.0;
    metDelimitado.tempoLeitura = tempoDelimitado;
    resultadosDaRodada.push_back(metDelimitado);

    Metricas metIndicador;
    metIndicador.formato = "Formato 3: Indicador";
    metIndicador.volume = volumeStr;
    metIndicador.bytesUteis = bytesUteisTotais;
    metIndicador.tamanhoDisco = GerenciadorArquivo::obterTamanhoArquivo(arqIndicador);
    metIndicador.eficiencia = (metIndicador.bytesUteis / metIndicador.tamanhoDisco)*100.0;
    metIndicador.tempoLeitura = tempoIndicador;
    resultadosDaRodada.push_back(metIndicador);

    this -> imprimirTabelaRelatorio(resultadosDaRodada);
}

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

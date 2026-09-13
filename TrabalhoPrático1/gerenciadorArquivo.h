#ifndef GERENCIADORARQUIVO_H
#define GERENCIADORARQUIVO_H
#include <vector>
#include <string>
#include "Aluno.h"

using namespace std;

class GerenciadorArquivo{
    public:

    vector<Aluno> lerCSV(string caminho);
    bool salvarFixo(string arq, vector<Aluno> al);
    bool salvarDelimitado(string arq, vector<Aluno> al);
    bool salvarIndicador(string arq, vector<Aluno> al);
    vector<Aluno> lerFixo(string arq);
    vector<Aluno> lerDelimitado(string arq);
    vector<Aluno> lerIndicador(string arq);
    bool lerPorRRN(string arq, int rrn, Aluno& out);
    long long obterTamanhoArquivo(string arq);
};

#endif
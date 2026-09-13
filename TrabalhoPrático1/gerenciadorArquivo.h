#ifndef GERENCIADORARQUIVO_H
#define GERENCIADORARQUIVO_H
#include <vector>
#include <string>
#include "aluno.h"

using namespace std;

class GerenciadorArquivo{
    public:

    static vector<Aluno> lerCSV(string caminho);
    static bool salvarFixo(string arq, vector<Aluno> al);
    static bool salvarDelimitado(string arq, vector<Aluno> al);
    static bool salvarIndicador(string arq, vector<Aluno> al);
    static vector<Aluno> lerFixo(string arq);
    static vector<Aluno> lerDelimitado(string arq);
    static vector<Aluno> lerIndicador(string arq);
    static bool lerPorRRN(string arq, int rrn, Aluno& out);
    static long long obterTamanhoArquivo(string arq);
};

#endif
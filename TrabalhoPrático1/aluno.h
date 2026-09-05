#ifndef ALUNO_H
#define ALUNO_H
#include <string>

using namespace std;

class Aluno{
    
private:
    int matricula;
    string nome;
    int idade;
    string curso;
    string cidade;
    string uf;
    float cra;

public:

    int packFixo(char* buffer);
    string packDelimitado();
    int packDelimitado(char* buffer);
    int packIdicador(char* buffer);
    void unpackFixo(const char* buffer);
    void unpackDelimitado(const string& buffer);
    void unpackIndicador(const char* buffer);
    int getBytesUteis();
    void imprimir();
};

#endif
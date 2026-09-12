#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "gerenciadorArquivo.h"
#include "aluno.h"

using namespace std;

vector<Aluno> gerenciadorArquivo::lerCSV(string caminho){
    ifstream arquivo("aluno_1k.csv");
}

bool gerenciadorArquivo::salvarFixo(string arq, vector<Aluno> al){
    ofstream arqFixo(arq, ios::out | ios::binary);
    if(!arqFixo.is_open()){
        return false;
    }

    const int tamanhoRegistro = 120;
    char buffer[tamanhoRegistro];
    for(Aluno& aluno : al){
        fill(buffer, buffer + tamanhoRegistro, '\0');
        aluno.packFixo(buffer);
        arqFixo.write(buffer, tamanhoRegistro);
    }
    arqFixo.close();
    return true;
}

bool gerenciadorArquivo::salvarDelimitado(string arq, vector<Aluno> al){
    ofstream arqDelimitado(arq, ios::out | ios::binary);
    if(!arqDelimitado.is_open()){
        return false;
    }

    for(Aluno& aluno : al){
       string alunoAtual = aluno.packDelimitado();
       arqDelimitado << alunoAtual; 
    }
    arqDelimitado.close();
    return true;
}

bool gerenciadorArquivo::salvarIndicador(string arq, vector<Aluno> al){
    ofstream arqIndicador(arq, ios::out | ios::binary);
    if(!arqIndicador.is_open()){
        return false;
    }

    const int tamanhoMaximo = 512;
    char buffer[tamanhoMaximo];
    for(Aluno& aluno : al){
        fill(buffer, buffer + tamanhoMaximo, '\0');
        int tamanhoRegistro = aluno.packIndicador(buffer);
        arqIndicador.write(buffer, tamanhoRegistro);
    }

    arqIndicador.close();
    return true;
}
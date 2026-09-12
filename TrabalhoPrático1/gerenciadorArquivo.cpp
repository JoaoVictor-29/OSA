#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "gerenciadorArquivo.h"

using namespace std;

bool salvarFixo(string arq, vector<Aluno> al){
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

bool salvarDelimitado(string arq, vector<Aluno> al){
    ofstream arqDelimitado(arq);
    if(!arqDelimitado.is_open()){
        return false;
    }

    for(Aluno& aluno : al){
       string alunoAtual = aluno.packDelimitado();
       arqDelimitado << alunoAtual << "\n"; 
    }
    arqDelimitado.close();
    return true;
}

bool salvarIndicador(string arq, vector<Aluno> al){
    ofstream arqIndicador(arq, ios::out | ios::binary);
    if(!arqIndicador.is_open()){
        return false;
    }

    const int tamanhoMaximo = 512;
    char buffer[tamanhoMaximo];
    for(Aluno& aluno : al){
        fill(buffer, buffer + tamanhoMaximo, '\0');
        int tamanhoRegistro = aluno.packIdicador(buffer);
        arqIndicador.write(reinterpret_cast<const char*>(&tamanhoRegistro), sizeof(int));
        arqIndicador.write(buffer, tamanhoRegistro);
    }

    arqIndicador.close();
    return true;
}
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

vector<Aluno> lerFixo(string arq){
    vector<Aluno> listaAlunos;
    ifstream arqFixo(arq, ios::in | ios::binary);
    if(!arqFixo.is_open()){
        return listaAlunos;
    }
    const int tamanhoExato = 120;
    char buffer[tamanhoExato];
    while(arqFixo.read(buffer, tamanhoExato)){
        if(arqFixo.gcount() == tamanhoExato){
            Aluno aluno;
            aluno.unpackFixo(buffer);
            listaAlunos.push_back(aluno);
        }
    }
    arqFixo.close();
    return listaAlunos;
}

vector<Aluno> lerDelimitado(string arq){
    vector<Aluno> listaAlunos;
    ifstream arqDelimitado(arq);
    if(!arqDelimitado.is_open()){
        return listaAlunos;
    }
    string linha;
    while(getline(arqDelimitado, linha)){
        if(linha.empty()){
            continue;
        }
        Aluno aluno;
        aluno.unpackDelimitado(linha);
        listaAlunos.push_back(aluno);
    }
    arqDelimitado.close();
    return listaAlunos;
}

vector<Aluno> lerIndicador(string arq){
    vector<Aluno> listaAlunos;
    ifstream arqIndicador(arq, ios::in | ios::binary);
    if(!arqIndicador.is_open()){
        return listaAlunos;
    }
    int tamanhoRegistro;
    const int tamanhoMaximo = 512;
    char buffer[tamanhoMaximo];
    while(arqIndicador.read(reinterpret_cast<char*>(&tamanhoRegistro), sizeof(int))){
        fill(buffer, buffer + tamanhoMaximo, '\0');
        arqIndicador.read(buffer, tamanhoRegistro);
        if(arqIndicador.gcount() == tamanhoRegistro){
            Aluno aluno;
            aluno.unpackIndicador(buffer);
            listaAlunos.push_back(aluno);
        }
    }
    arqIndicador.close();
    return listaAlunos;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "gerenciadorArquivo.h"
#include "aluno.h"

using namespace std;

vector<Aluno> gerenciadorArquivo::lerCSV(string caminho){
    ifstream arquivo(caminho);
    vector<Aluno> listaAlunos;

    if(!arquivo.is_open()){
        return listaAlunos;
    }

    string linha;
    getline(arquivo, linha);

    while(getline(arquivo, linha)){
        Aluno aluno;
        size_t pos;

        //matricula
        pos = linha.find(',');
        string parte = linha.substr(0, pos);
        aluno.matricula = stoi(parte);
        linha.erase(0, pos + 1);

        //nome
        pos = linha.find(',');
        parte = linha.substr(0, pos);
        aluno.nome = parte;
        linha.erase(0, pos + 1);

        //idade
        pos = linha.find(',');
        parte = linha.substr(0, pos);
        aluno.idade = stoi(parte);
        linha.erase(0, pos + 1);

        //curso
        pos = linha.find(',');
        parte = linha.substr(0, pos);
        aluno.curso = parte;
        linha.erase(0, pos + 1);

        //cidade
        pos = linha.find(',');
        parte = linha.substr(0, pos);
        aluno.cidade = parte;
        linha.erase(0, pos + 1);

        //uf
        pos = linha.find(',');
        parte = linha.substr(0, pos);
        aluno.uf = parte;
        linha.erase(0, pos + 1);

        aluno.cra = stof(linha);

        listaAlunos.push_back(aluno);

    }
    return listaAlunos;
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

bool gerenciadorArquivo::lerPorRRN(string arq, int rrn, Aluno& out){
    if(rrn < 0)
        return false;

    ifstream arquivo(arq, ios::in | ios::binary);

    if(!arquivo.is_open())
        return false;

    arquivo.seekg(rrn * 120, ios::beg);

    if(!arquivo)
        return false;

    char buffer[120];
    arquivo.read(reinterpret_cast<char*>(buffer), 120);

    out.unpackFixo(buffer);

    arquivo.close();

    return true;
}
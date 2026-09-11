#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include "aluno.h"

using namespace std;


string Aluno::packDelimitado(){
    string buffer = "";

    buffer += to_string(matricula) + "#";
    buffer += nome + "#";
    buffer += to_string(idade) + "#";
    buffer += curso + "#";
    buffer += cidade + "#";
    buffer += uf + "#";
    buffer += to_string(cra) + "|";

    return buffer;
}

int Aluno::packFixo(char* buffer){
    memset(buffer, '\0', 120);

    int posicao = 0;

    memcpy(buffer + posicao, &matricula, sizeof(int));
    posicao += sizeof(int);
    
    memcpy(buffer + posicao, nome.c_str(), nome.length());
    posicao += 40;

    memcpy(buffer + posicao, &idade, sizeof(int));
    posicao += sizeof(int);

    memcpy(buffer + posicao, curso.c_str(), curso.length());
    posicao += 35;

    memcpy(buffer + posicao, cidade.c_str(), cidade.length());
    posicao += 30;

    memcpy(buffer + posicao, uf.c_str(), uf.length());
    posicao += 3;

    memcpy(buffer + posicao, &cra, sizeof(float));
    posicao += sizeof(float);

    return 120;

}

void Aluno::unpackDelimitado(const string& buffer){
    vector<string> dados;

    size_t pos;
    string aux = buffer;

    while((pos = aux.find('#')) != string::npos){
        dados.push_back(aux.substr(0, pos));

        aux.erase(0, pos + 1);
    }

    pos = aux.find('|');
    dados.push_back(aux.substr(0, pos));

    matricula = stoi(dados[0]);
    nome = dados[1];
    idade = stoi(dados[2]);
    curso = dados[3];
    cidade = dados[4];
    uf = dados[5];
    cra = stof(dados[6]);

}

void Aluno::unpackFixo(const char* buffer){
    
}

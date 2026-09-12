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
    int posicao = 0;

    memcpy(&matricula, buffer + posicao, sizeof(int));
    posicao += sizeof(int);

    char auxNome[41] = {0};
    memcpy(auxNome, buffer + posicao, 40);
    nome = auxNome;
    posicao += 40;

    memcpy(&idade, buffer + posicao, sizeof(int));
    posicao += sizeof(int);

    char auxCurso[36] = {0};
    memcpy(auxCurso, buffer + posicao, 35);
    curso = auxCurso;
    posicao += 35;

    char auxCidade[31] = {0};
    memcpy(auxCidade, buffer + posicao, 30);
    cidade = auxCidade;
    posicao += 30;

    char auxUf[4] = {0};
    memcpy(auxUf, buffer + posicao, 3);
    uf = auxUf;
    posicao += 3;

    memcpy(&cra, buffer + posicao, sizeof(float));
    posicao += sizeof(float);
}

int Aluno::packIndicador(char* buffer){
    int posicao = sizeof(unsigned short);
    memcpy(buffer + posicao, &matricula, sizeof(int));
    posicao += sizeof(int);

    //Aqui é pra indicar o tamanho do nome
    unsigned char tamanhoNome = nome.length();
    memcpy(buffer + posicao, &tamanhoNome, sizeof(unsigned char));
    posicao += sizeof(unsigned char);
    memcpy(buffer + posicao, nome.c_str(), tamanhoNome);
    posicao += tamanhoNome;

    memcpy(buffer + posicao, &idade, sizeof(int));
    posicao += sizeof(int);

    unsigned char tamanhoCurso = curso.length();
    memcpy(buffer + posicao, &tamanhoCurso, sizeof(unsigned char));
    posicao += sizeof(unsigned char);
    memcpy(buffer + posicao, curso.c_str(), tamanhoCurso);
    posicao += tamanhoCurso;

    unsigned char tamanhoCidade = cidade.length();
    memcpy(buffer + posicao, &tamanhoCidade, sizeof(unsigned char));
    posicao += sizeof(unsigned char);
    memcpy(buffer + posicao, cidade.c_str(), tamanhoCidade);
    posicao += tamanhoCidade;

    unsigned char tamanhoUf = uf.length();
    memcpy(buffer + posicao, &tamanhoUf, sizeof(unsigned char));
    posicao += sizeof(unsigned char);
    memcpy(buffer + posicao, uf.c_str(), tamanhoUf);
    posicao += tamanhoUf;

    memcpy(buffer + posicao, &cra, sizeof(float));
    posicao += sizeof(float);

    //calcular tamanho total
    unsigned short tamanhoTotal = posicao - sizeof(unsigned short);
    memcpy(buffer, &tamanhoTotal, sizeof(unsigned short));
    return posicao;
}

void Aluno::unpackIndicador(const char* buffer){
    int posicao = sizeof(unsigned short);

    memcpy(&matricula, buffer + posicao, sizeof(int));
    posicao += sizeof(int);

    unsigned char tamNome;
    memcpy(&tamNome, buffer + posicao, sizeof(unsigned char));
    posicao += sizeof(unsigned char);
    nome = string(buffer + posicao, tamNome);
    posicao += tamNome;

    memcpy(&idade, buffer + posicao, sizeof(int));
    posicao += sizeof(int);

    unsigned char tamCurso;
    memcpy(&tamCurso, buffer + posicao, sizeof(unsigned char));
    posicao += sizeof(unsigned char);
    curso = string(buffer + posicao, tamCurso);
    posicao += tamCurso;

    unsigned char tamCidade;
    memcpy(&tamCidade, buffer + posicao, sizeof(unsigned char));
    posicao += sizeof(unsigned char);
    cidade = string(buffer + posicao, tamCidade);
    posicao += tamCidade;

    unsigned char tamUf;
    memcpy(&tamUf, buffer + posicao, sizeof(unsigned char));
    posicao += sizeof(unsigned char);
    uf = string(buffer + posicao, tamUf);
    posicao += tamUf;

    memcpy(&cra, buffer + posicao, sizeof(float));
    posicao += sizeof(float);
}

int Aluno::getBytesUteis(){
    int total = 0;
    total += sizeof(int);
    total += sizeof(int);
    total += sizeof(float);
    total += nome.length();
    total += curso.length();
    total += cidade.length();
    total += uf.length();

    return total;
}

void Aluno::imprimir(){
    cout << "Matricula: " << matricula << " | " << "Nome: " << nome << " | " << "idade: " << idade << " | " << "Curso: " << curso << " | " << "Cidade: " << cidade << " | " << "UF: " << uf << " | " << "CRA: " << cra << " | " << endl;  
}

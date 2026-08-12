#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Registro{
    int matricula;
    int idade;
    float media;
};

void gravarAlunos(const vector<Registro>& alunos, ofstream& arquivoBin){
    
    if(arquivoBin.is_open()){
        for(int i = 0; i < 5; i++){
            arquivoBin.write(reinterpret_cast<char*>(*Registro), sizeof Registro);
        }
    }else{
        cout << "Erro ao abrir o arquivo" << endl;
    }
}

void lerAlunos(vector<Registro>& alunos, ifstream& arquivoBin){
    
}

int main (){
    vector<Registro> registro;

    registro.push_back({1, 16, 22.5});
    registro.push_back({2, 17, 28.0});
    registro.push_back({3, 14, 20.6});
    registro.push_back({4, 18, 19.3});
    registro.push_back({5, 15, 21.9});

    ofstream arquivo("alunos.bin", ios::binary);
    if(!arquivo){
        cout << "Erro ao criar o arquivo" << endl;
    }

    gravarAlunos(registro, arquivo);
    arquivo.close;

    return 0;
}
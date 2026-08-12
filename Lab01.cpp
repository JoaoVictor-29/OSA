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
        for(const Registro& registro : alunos){
            arquivoBin.write(reinterpret_cast<const char*>(&registro), sizeof registro);
        }
    }else{
        cout << "Erro ao abrir o arquivo" << endl;
    }
}

void lerAlunos(vector<Registro>& alunos, ifstream& arquivoBin){
    if(arquivoBin.is_open()){
        Registro aux;
        while(arquivoBin.read(reinterpret_cast<char*>(&aux), sizeof(Registro))){
            alunos.push_back(aux);
        }
    }else{
        cout << "Erro ao abrir o arquivo" << endl;
    }

    cout << alunos.size() << endl;
}

void buscarPorMatricula(vector<Registro>& alunos){
    int matric;
    cout << "Digite a matricula do aluno que deseja buscar:" << endl;
    cin >> matric;

    for(int i = 0; i < alunos.size(); i++){
        if(alunos[i].matricula == matric){
            cout << "Matricula: " << alunos[i].matricula << endl;
            cout << "Idade: " << alunos[i].idade << endl;
            cout << "Media: " << alunos[i].media << endl;
            return;
        }
    }
    cout << "Matricula nao encontrada" << endl;
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
    arquivo.close();

    ifstream arquivoLeitura("alunos.bin", ios::binary);
    if(!arquivoLeitura.is_open()){
        cout << "Erro ao ler o arquivo" << endl;
    }

    vector<Registro> regLidos;
    lerAlunos(regLidos, arquivoLeitura);
    arquivoLeitura.close();

    buscarPorMatricula(registro);

    return 0;
}
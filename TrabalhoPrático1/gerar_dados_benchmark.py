#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script Gerador de Dados para o Trabalho Prático 01 (TP1)
Disciplina: Organização e Sistemas de Arquivos (OSA) - IFNMG
Professor: Wagner Ferreira de Barros

Uso:
    python gerar_dados_benchmark.py --total 10000 --saida alunos_10k.csv
    python gerar_dados_benchmark.py --cenarios
"""

import csv
import random
import argparse
import sys

def gerar_base(total_registros, nome_arquivo, seed=42):
    random.seed(seed)

    nomes = [
        "Ana", "Bruno", "Carlos", "Daniela", "Eduardo", "Fernanda", "Gabriel", "Helena",
        "Igor", "Juliana", "Lucas", "Mariana", "Nicolas", "Olivia", "Pedro", "Rafaela",
        "Samuel", "Tatiana", "Vinicius", "Yasmin", "Alexandre", "Beatriz", "Caio", "Debora",
        "Enzo", "Flavia", "Guilherme", "Isabela", "Joao", "Larissa", "Matheus", "Natalia",
        "Rodrigo", "Camila", "Felipe", "Leticia", "Thiago", "Amanda", "Gustavo", "Luana"
    ]

    sobrenomes = [
        "Silva", "Santos", "Oliveira", "Souza", "Rodrigues", "Ferreira", "Alves", "Pereira",
        "Lima", "Gomes", "Costa", "Ribeiro", "Martins", "Carvalho", "Almeida", "Lopes",
        "Soares", "Fernandes", "Vieira", "Barbosa", "Rocha", "Dias", "Nascimento", "Andrade",
        "Moreira", "Nunes", "Marques", "Machado", "Mendes", "Freitas", "Cardoso", "Ramos",
        "Teixeira", "Moura", "Cavalcanti", "Monteiro", "Medeiros", "Pinto", "Castro", "Brito"
    ]

    cursos = [
        "Ciencia da Computacao", "Engenharia Eletrica", "Sistemas de Informacao",
        "Analise e Desenvolvimento de Sistemas", "Engenharia de Software", "Medicina",
        "Administracao", "Direito", "Agronomia", "Matematica", "Fisica", "Quimica"
    ]

    cidades = [
        "Montes Claros", "Januaria", "Salinas", "Pirapora", "Almenara", "Teofilo Otoni",
        "Belo Horizonte", "Diamantina", "Porteirinha", "Brasilia de Minas", "Janauba",
        "Sao Francisco", "Coronel Fabriciano", "Uberlandia", "Juiz de Fora", "Vicosa",
        "Lavras", "Ouro Preto", "Curvelo", "Governador Valadares"
    ]

    estados = ["MG", "BA", "SP", "RJ", "ES", "GO", "DF"]

    registros = []
    for i in range(1, total_registros + 1):
        matricula = 20260000 + i
        
        # Variacao proposital de tamanho para evidenciar diferenca entre fixo e variavel
        r = random.random()
        if r < 0.20:
            # Nome curto (2 palavras)
            nome = f"{random.choice(nomes)} {random.choice(sobrenomes)}"
        elif r < 0.70:
            # Nome medio (3 palavras)
            nome = f"{random.choice(nomes)} {random.choice(sobrenomes)} {random.choice(sobrenomes)}"
        else:
            # Nome longo (4 palavras)
            nome = f"{random.choice(nomes)} {random.choice(sobrenomes)} {random.choice(sobrenomes)} {random.choice(sobrenomes)}"
            
        idade = random.randint(18, 55)
        curso = random.choice(cursos)
        cidade = random.choice(cidades)
        uf = random.choice(estados)
        cra = round(random.uniform(5.0, 9.9), 2)
        
        registros.append({
            "matricula": matricula,
            "nome": nome,
            "idade": idade,
            "curso": curso,
            "cidade": cidade,
            "uf": uf,
            "cra": cra
        })

    with open(nome_arquivo, mode="w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=["matricula", "nome", "idade", "curso", "cidade", "uf", "cra"])
        writer.writeheader()
        for reg in registros:
            writer.writerow(reg)

    print(f"[OK] Arquivo '{nome_arquivo}' gerado com sucesso: {total_registros} registros.")

def main():
    parser = argparse.ArgumentParser(description="Gerador de bases de dados para Benchmark de OSA (TP1)")
    parser.add_argument("--total", type=int, default=10000, help="Quantidade total de registros a serem gerados")
    parser.add_argument("--saida", type=str, default="alunos_benchmark.csv", help="Nome do arquivo CSV de saida")
    parser.add_argument("--cenarios", action="store_true", help="Gera automaticamente 4 cenarios: 1K, 10K, 50K e 100K registros")
    parser.add_argument("--seed", type=int, default=42, help="Semente de aleatoriedade")

    args = parser.parse_args()

    if args.cenarios:
        print("Gerando cenários padronizados para o Benchmark completo...")
        gerar_base(1000, "alunos_1k.csv", args.seed)
        gerar_base(10000, "alunos_10k.csv", args.seed)
        gerar_base(50000, "alunos_50k.csv", args.seed)
        gerar_base(100000, "alunos_100k.csv", args.seed)
        print("Todos os cenários foram gerados com sucesso!")
    else:
        gerar_base(args.total, args.saida, args.seed)

if __name__ == "__main__":
    main()

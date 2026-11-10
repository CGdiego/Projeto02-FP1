/*============================================================================*/
/* ICSF13 - 2026-2 - TRABALHO 2                                               */
/*----------------------------------------------------------------------------*/
/* Diego Soares                                                               */
/* Vinicius Hirai                                                             */
/*============================================================================*/

#include <math.h>
#include "trabalho2.h"

// Função 1: Altera o ganho de um sinal
void mudaGanho(double* dados, int n_amostras, double ganho){
    int i;

    // Percorre cada amostra
    for (i = 0; i < n_amostras; i++){
        // Multiplica e armazena
        dados[i] *= ganho;
    }
}

// Função 2: Conta o número de amostras que extrapolam o limite (quando tem valor absoluto maior que 1)
int contaSaturacoes(double* dados, int n_amostras){
    int i, n_saturadas = 0;

    // Itera para cada amostra
    for (i = 0; i < n_amostras; i++){
        // Conta quantas amostras são saturadas (o fabs() é pra deixar positivo se for negativo)
        if (fabs(dados[i]) > 1)
            n_saturadas++;
    }

    return n_saturadas;
}

// Função 3: Faz hard clipping (o valor aboluto fica "limitado") de cada amostra, alterando o vetor, e retorna quantas amostras foram alteradas
int hardClipping(double* dados, int n_amostras, double limite){
    int i, n_alteradas = 0;

    // Itera cada amostra
    for (i = 0; i < n_amostras; i++){
        // Verifica se o valor absoluto da amostra é maior que o limite
        if (fabs(dados[i]) > limite){
            // Faz o hard clipping da amostra cujo valor absoluto é maior que o limite
            if (dados[i] > 0)
                dados[i] = limite;
            else
                dados[i] = -limite;

            // Aumenta o contador de amostras alteradas
            n_alteradas++;
        }
    }

    return n_alteradas;
}

// Função 4: Limite de sinal intervalo [-1, 1] e afeta amostras vizinhas
void limitaSinal(double* dados, int n_amostras, int n_passos){
    int i, j;
    double ganho, aumento_ganho, ganho_atual;

    // Percorrer todas amostras
    for (i = 0; i < n_amostras; i++){
        // Verificacao de limite
        if (fabs(dados[i]) > 1.0){
            // Calculo do ganho pra amostra
            ganho = 1.0 / fabs(dados[i]);
            // Calcula a diferenca para cada passo
            aumento_ganho = (1.0 - ganho) / (n_passos + 1.0);
            // Aplica o ganho na amostra que passou o limite
            dados[i] *= ganho;

            // Percorre os vizinhos
            for (j = 1; j <= n_passos; j++){
                // Calculo do ganho
                ganho_atual = ganho + (j * aumento_ganho);

                // Verifica vizinho na esquerda
                if (i - j >= 0)
                    dados[i -j] *= ganho_atual;
                // Verifica vizinho na direita
                if (i + j < n_amostras)
                    dados[i +j] *= ganho_atual;
            }
        }
    }
}

// Função 5: Gera ondas que possuem apenas 1 e -1 (ondas quadradas), para criar audio sintético
void geraOndaQuadrada(double* dados, int n_amostras, int taxa, double freq){
    int i, amostras_restantes, flag_onda = 1;
    double meio_periodo, tamanho_mais_erro, erro = 0;

    meio_periodo = taxa / (freq * 2); // Quantas amostras tem em 1 segundo / quantos ciclos ocorrem em 1 segundos * 2 (troca entre 1 e -1)

    amostras_restantes = (int) meio_periodo; // Usa type casting pra remover a parte decimal
    erro = meio_periodo - amostras_restantes; // Subtrai o valor real com o inteiro pra pegar apenas a parte decimal

    // Itera para cada amostra
    for (i = 0; i < n_amostras; i++){
        dados[i] = flag_onda; // Coloca ou 1 ou -1 no vetor
        amostras_restantes--; // Diminui o contador de amostras

        if (!amostras_restantes){
            flag_onda = -flag_onda; // Inverte a flag

            tamanho_mais_erro = meio_periodo + erro; // Serve pra simplificar o código e não ter que repetir duas vzes
            amostras_restantes = (int) tamanho_mais_erro; // Usa type casting pra remover a parte decimal e inclui o erro
            erro = tamanho_mais_erro - amostras_restantes; // Subtrai o valor real com o inteiro pra pegar apenas a parte decimal
        }
    }
}

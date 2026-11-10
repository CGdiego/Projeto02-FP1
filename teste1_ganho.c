/*============================================================================*/
/* Exemplo: Modifica o volume de um sinal. . */

#include <stdlib.h>
#include "wavfile.h"

#include "trabalho2.h"

/*============================================================================*/

#define INPUT_FILE "data/sonic1.wav"
#define OUTPUT_FILE "data/teste1_ganho_aluno.wav"

/*============================================================================*/

int main ()
{
	WavHeader header; /* Cabeçalho para as informações sobre o arquivo. */
	double* dados_l; /* Dados do canal esquerdo. Alocado na readWavFile. */
	double* dados_r; /* Dados do canal direito. Alocado na readWavFile, se necessário. */
	int n_amostras; /* Número de amostras nos buffers. */

    /* Lê um arquivo. */
    n_amostras = readWavFile (INPUT_FILE, &header, &dados_l, &dados_r);
    if (!n_amostras)
    {
        printf ("Erro lendo %s.\n", INPUT_FILE);
        return (1);
    }

	/* Confirma que o arquivo é stereo. */
    if (!dados_r)
    {
        printf ("%s nao eh um arquivo stereo.\n", INPUT_FILE);
        return (1);
    }

    /* Reduz o volume no início. */
    mudaGanho (dados_l, n_amostras/8, 0.2);
    mudaGanho (dados_r, n_amostras/8, 0.2);
    mudaGanho (dados_l + n_amostras/8, n_amostras/8, 0.5);
    mudaGanho (dados_r + n_amostras/8, n_amostras/8, 0.5);

    /* Escreve em outro arquivo. */
    if (!writeWavFile (OUTPUT_FILE, &header, dados_l, dados_r))
    {
        printf ("Erro salvando %s.\n", OUTPUT_FILE);
        return (1);
    }

    /* Desaloca os vetores. O direito só vai ter sido alocado se o arquivo for estéreo. */
	free (dados_l);
	if (dados_r)
        free (dados_r);

	return (0);
}

/*============================================================================*/

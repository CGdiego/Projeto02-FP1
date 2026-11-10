/*============================================================================*/
/* ICSF13 - 2026-2 - TRABALHO 2                                               */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu                                                            */
/* Leyza E. B. Dorini                                                         */
/* Daniel F. Pigatto                                                          */
/*============================================================================*/
/** Funções pedidas para o 2o trabalho da disciplina Fundamentos de Programação
 * 1, 2o semestre de 2026, profs. Bogdan T. Nassu, Leyza E. B. Dorini e Daniel
 * F. Pigatto, Universidade Tecnológica Federal do Paraná. */
/*============================================================================*/

#ifndef __TRABALHO2_H
#define __TRABALHO2_H

/*============================================================================*/

void mudaGanho (double* dados, int n_amostras, double ganho);
int contaSaturacoes (double* dados, int n_amostras);
int hardClipping (double* dados, int n_amostras, double limite);
void limitaSinal (double* dados, int n_amostras, int n_passos);
void geraOndaQuadrada (double* dados, int n_amostras, int taxa, double freq);

/*============================================================================*/
#endif /* __TRABALHO2_H */

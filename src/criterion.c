/* criterion(1)
 * criterion(1) is a tools that can be used by manager of the organization 
 * to made a decision under uncertainty environment.
 *
 * Please see README.md for the details.
 *
 * Copyright 2015 Bayu Aldi Yansyah <bayualdiyansyah@gmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    printf("============================================================\n");
    printf("==             Keputusan Dalam Ketidakpastian             ==\n");
    printf("============================================================\n");
    printf("Masukkan jumlah tindakan (T)         : ");
    int ntindakan = 0;
    if(scanf("%d", &ntindakan) != 1 || ntindakan == 0 || ntindakan > 99) {
        printf("Jumlah tindakan maksimal adalah 99.\n");
        exit(EXIT_FAILURE);
    }

    printf("Masukkan jumlah keadaan/kejadian (K) : ");
    int nkejadian = 0;
    if(scanf("%d", &nkejadian) != 1 || nkejadian == 0 || nkejadian > 99) {
        printf("Jumlah keadaan/kejadian maksimal adalah 99.\n");
        exit(EXIT_FAILURE);
    }

    /* Allocate memory for payoff matrix;
     * PAYOFF_M is an array of array of float. We allocate contiguous 
     * NTINDAKAN block of memory with size SIZEOF *PAYOFF_M for each 
     * block.*/
    float **payoff_m = calloc(ntindakan, sizeof *payoff_m);
    int i = 0, j = 0;
    for(i = 0; i < ntindakan; i++) {
        payoff_m[i] = calloc(nkejadian, sizeof *payoff_m[i]);

        for(j = 0; j < nkejadian; j++) {
            printf("Masukkan nilai untuk V(T%d, K%d)       : ", i + 1, j + 1);
            if(scanf("%f", &payoff_m[i][j]) != 1) {
                printf("Exit, Pastikan input anda benar.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    printf("\n");

    /* Print the matrix payoff to the STDOUT */
    printf("============================================================\n");
    printf("==                     Matriks Payoff                     ==\n");
    printf("============================================================\n");
    /* Table header */
    for(j = 0; j < nkejadian; j++) {
        if(j == 0) {
            printf("      K(%d)", j + 1);
        } else {
            printf("     K(%d)", j + 1);
        }

    }
    printf("\n");
    for(i = 0; i < ntindakan; i++) {
        printf("T(%d) ", i + 1);
        for(j = 0; j < nkejadian; j++) {
            printf("%8.4f ", payoff_m[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("============================================================\n");
    printf("==                   Analisa 4 Kriteria                   ==\n");
    printf("============================================================\n");

    printf("1. Kriteria Laplace\n");
    float laplace_t_max = 0.0;
    int laplace_t_max_i = 0;
    for(i = 0; i < ntindakan; i++) {
        float tindakan_sum = 0.0;
        for(j = 0; j < nkejadian; j++) {
            tindakan_sum += payoff_m[i][j];
        }
        tindakan_sum = (1 / (float)nkejadian) * tindakan_sum;
        printf("   * T%d: %f\n", i + 1, tindakan_sum);
        if(tindakan_sum > laplace_t_max) {
            laplace_t_max = tindakan_sum;
            laplace_t_max_i = i + 1;
        }
    }
    printf("   Tindakan yang dipilih = T%d\n", laplace_t_max_i);
    printf("\n");

    printf("2. Kriteria Wald\n");
    printf("   Ketik 1 untuk Maximin 2 untuk Minimax : ");
    int wald_n = 0;
    int wald_t_i = 0;           /* Ti choosed */
    if(scanf("%d", &wald_n) != 1 || wald_n < 0 || wald_n > 2) {
        printf("\nInput anda tidak valid.\n");
        exit(EXIT_FAILURE);
    }
    /* Minimax 
     * We choose the maximum of Kj and the minimum of Ti */
    float minimax_t_min = 0.0;
    /* Maximin 
     * We choose the minimum of Kj and the maximum of Ti */
    float maximin_t_max = 0.0;
    /* Maximin */
    if(wald_n == 1) {
        printf("   Maximin terpilih\n");
    }
    /* Minimax */
    if(wald_n == 2) {
        printf("   Minimax terpilih\n");
    }
    for(i = 0; i < ntindakan; i++) {
        /* Kmax & Kmin should reset for each row */
        float minimax_k_max = 0.0;
        float maximin_k_min = 0.0;

        for(j = 0; j < nkejadian; j++) {
            float kj = payoff_m[i][j];

            if(wald_n == 1) {
                /* set the first Kj in one row as a minimum */
                if(j == 0) {
                    maximin_k_min = kj;
                }
                if(kj < maximin_k_min) {
                    maximin_k_min = kj;
                }
            }

            if(wald_n == 2) {
                if(kj > minimax_k_max) {
                    minimax_k_max = kj;
                }
            }
        }

        /* Maximin */
        if(wald_n == 1) {
            printf("   * T%d: %f\n", i + 1, maximin_k_min);
            if(maximin_k_min > maximin_t_max) {
                maximin_t_max = maximin_k_min;
                wald_t_i = i + 1;
            }
        }

        /* Minimax */
        if(wald_n == 2) {
            printf("   * T%d: %f\n", i + 1, minimax_k_max);
            /* set the first maximum Kj as minimum Ti */
            if(i == 0) {
                minimax_t_min = minimax_k_max;
            }
            if(minimax_k_max < minimax_t_min) {
                minimax_t_min = minimax_k_max;
                wald_t_i = i + 1;
            }
        }
    }
    printf("   Tindakan yang dipilih = T%d\n", wald_t_i);
    printf("\n");

    printf("3. Kriteria Savage Minimax Regret\n");
    printf("   Ketik 1 jika V(Ti,Kj) laba; 2 jika V(Ti, Kj) kerugian : ");
    int savage_n = 0;
    if(scanf("%d", &savage_n) != 1 || savage_n < 0 || savage_n > 2) {
        printf("\nInput anda tidak valid.\n");
        exit(EXIT_FAILURE);
    }
    /* create new table; copy payoff matrix */
    float **savage_payoff = calloc(ntindakan, sizeof *savage_payoff);
    for(i = 0; i < ntindakan; i++) {
        savage_payoff[i] = calloc(nkejadian, sizeof *savage_payoff[i]);
        for(j = 0; j < nkejadian; j++) {
            savage_payoff[i][j] = payoff_m[i][j];
        }
    }
    /* for loss */
    float savage_v_min = 0.0;
    for(j = 0; j < nkejadian; j++) {
        /* for benefit; savage_v_mac should reset for each column */
        float savage_v_max = 0.0;
        for(i = 0; i < ntindakan; i++) {
            if(savage_n == 1) {
                if(savage_payoff[i][j] > savage_v_max) {
                    savage_v_max = savage_payoff[i][j];
                }
            }

            if(savage_n == 2) {
                /* set the first V(Tk, Kj) as minimum */
                if(i == 0) {
                    savage_v_min = savage_payoff[i][j];
                }

                if(savage_payoff[i][j] < savage_v_min) {
                    savage_v_min = savage_payoff[i][j];
                }
            }
        }
        for(i = 0; i < ntindakan; i++) {
            if(savage_n == 1) {
                savage_payoff[i][j] = savage_v_max - savage_payoff[i][j];
            }

            if(savage_n == 2) {
                savage_payoff[i][j] -= savage_v_min;
            }
        }
    }

    printf("   =========================================================\n");
    printf("   ==                 Tabel Kerugian Baru                 ==\n");
    printf("   =========================================================\n");
    /* Table header */
    for(j = 0; j < nkejadian; j++) {
        if(j == 0) {
            printf("         K(%d)", j + 1);
        } else {
            printf("     K(%d)", j + 1);
        }

    }
    printf("\n");
    for(i = 0; i < ntindakan; i++) {
        printf("   T(%d) ", i + 1);
        for(j = 0; j < nkejadian; j++) {
            printf("%8.4f ", savage_payoff[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    /* Minimax for a new payoff matrix */
    int savage_t_i = 0;
    float s_minimax_t_min = 0.0;
    printf("   Hasil Kriteria Minimax: \n");
    for(i = 0; i < ntindakan; i++) {
        float s_minimax_k_max = 0.0;

        for(j = 0; j < nkejadian; j++) {
            float kj = savage_payoff[i][j];
            if(kj > s_minimax_k_max) {
                s_minimax_k_max = kj;
            }
        }
        printf("   * T%d: %f\n", i + 1, s_minimax_k_max);
        /* set the first maximum Kj as minimum Ti */
        if(i == 0) {
            s_minimax_t_min = s_minimax_k_max;
        }
        if(s_minimax_k_max < s_minimax_t_min) {
            s_minimax_t_min = s_minimax_k_max;
            savage_t_i = i + 1;
        }
    }
    printf("   Tindakan yang dipilih = T%d\n", savage_t_i);
    printf("\n");

    /* deallocate the memory */
    for(i = 0; i < ntindakan; i++) {
        free(payoff_m[i]);
        free(savage_payoff[i]);
        payoff_m[i] = NULL;
        savage_payoff[i] = NULL;
    }
    free(payoff_m);
    free(savage_payoff);
    payoff_m = NULL;
    savage_payoff = NULL;

    return EXIT_SUCCESS;
}

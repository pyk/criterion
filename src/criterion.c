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
            printf("Masukkan nilai untuk V(T%d, K%d) : ", i+1, j+1);
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
        tindakan_sum = (1/(float)nkejadian) * tindakan_sum;
        printf("   * T%d: %f\n", i+1, tindakan_sum);
        if(tindakan_sum > laplace_t_max) {
            laplace_t_max = tindakan_sum;
            laplace_t_max_i = i + 1;
        }
    }
    printf("   Tindakan yang dipilih = T%d\n", laplace_t_max_i);


    /* deallocate the memory */
    for(i = 0; i < ntindakan; i++) {
        free(payoff_m[i]);
        payoff_m[i] = NULL;
    }
    free(payoff_m);
    payoff_m = NULL;

    return EXIT_SUCCESS;
}

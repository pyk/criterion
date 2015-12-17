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

    float **payoff_m = calloc(ntindakan, sizeof **payoff_m);
    int i = 0, j = 0;
    for(i = 0; i < ntindakan; i++) {
        payoff_m[i] = calloc(nkejadian, sizeof *payoff_m[i]);

        for(j = 0; j < nkejadian; j++) {
            printf("Masukkan nilai untuk V(T%d, K%d) : ", i, j);
            if(scanf("%f", &payoff_m[i][j]) != 1) {
                printf("Exit, Pastikan input anda benar.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    for(i = 0; i < ntindakan; i++) {
        for(j = 0; j < nkejadian; j++) {
            printf("V(T%d, K%d) = %3.3f\n", i, j, payoff_m[i][j]);
        }
    }

    return EXIT_SUCCESS;
}

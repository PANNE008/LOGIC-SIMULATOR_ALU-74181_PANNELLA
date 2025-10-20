#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



int AND(int a, int b) { return a * b; }
int NOT(int a) { return 1 - a; }
int OR(int a, int b) { return a + b - (a * b); }
int EXOR(int a, int b) { return (1 - a) * b + a * (1 - b); }
int NAND(int a, int b) { return NOT(AND(a, b)); }
int NOR(int a, int b) { return NOT(OR(a, b)); }
int EXNOR(int a, int b) { return NOT(EXOR(a, b)); }


int AND_3(int a, int b, int c) { return AND(a, AND(b, c)); }
int AND_4(int a, int b, int c, int d) { return AND(a, AND(b, AND(c, d))); }
int AND_5(int a, int b, int c, int d, int e) { return AND(a, AND(b, AND(c, AND(d, e)))); }
int OR_3(int a, int b, int c) { return OR(a, OR(b, c)); }
int OR_4(int a, int b, int c, int d) { return OR(a, OR(b, OR(c, d))); }
int NOR_3(int a, int b, int c) { return NOR(a, NOR(b, c)); }
int NOR_4(int a, int b, int c, int d) { return NOR(a, NOR(b, NOR(c, d))); }
int NAND_4(int a, int b, int c, int d) { return NAND(a, NAND(b, NAND(c, d))); }
int NAND_5(int a, int b, int c, int d, int e) { return NAND(a, NAND(b, NAND(c, NAND(d, e)))); }


void ALU_4_BIT(int A0, int A1, int A2, int A3,
                int B0, int B1, int B2, int B3,
                int S0, int S1, int S2, int S3,
                int M, int Cn,
                int *G_out, int *Cn_piu_4_out, int *P_out,
                int *F3_out, int *F2_out, int *A_uguale_B_out,
                int *F1_out, int *F0_out,
                int *G3_out, int *G2_out,
                int *P3_out, int *P2_out,
                int *G1_out, int *G0_out,
                int *P1_out, int *P0_out) {

    
    int NOTB0 = NOT(B0);
    int NOTB1 = NOT(B1);
    int NOTB2 = NOT(B2);
    int NOTB3 = NOT(B3);

    
    int P0 = NOT(OR_3(A0, AND(NOTB0, S1), AND(B0, S0)));
    int P1 = NOT(OR_3(A1, AND(NOTB1, S1), AND(B1, S0)));
    int P2 = NOT(OR_3(A2, AND(NOTB2, S1), AND(B2, S0)));
    int P3 = NOT(OR_3(A3, AND(NOTB3, S1), AND(B3, S0)));

    
    int G0 = NOT(OR(AND_3(A0, NOTB0, S2), AND_3(A0, B0, S3)));
    int G1 = NOT(OR(AND_3(A1, NOTB1, S2), AND_3(A1, B1, S3)));
    int G2 = NOT(OR(AND_3(A2, NOTB2, S2), AND_3(A2, B2, S3)));
    int G3 = NOT(OR(AND_3(A3, NOTB3, S2), AND_3(A3, B3, S3)));

    
    int NOTM = NOT(M);
    int NOTP0 = NOT(P0);
    int NOTP1 = NOT(P1);
    int NOTP2 = NOT(P2);
    int NOTP3 = NOT(P3);

    int AND01 = AND(NOTM, P0);
    int AND02 = AND_3(NOTM, G0, Cn);
    int AND03 = AND(NOTM, P1);
    int AND04 = AND_3(NOTM, P0, G1);
    int AND05 = AND_4(NOTM, Cn, G0, G1);
    int AND06 = AND(NOTM, P2);
    int AND07 = AND_3(NOTM, P1, G2);
    int AND08 = AND_4(NOTM, P0, G1, G2);
    int AND09 = AND_5(NOTM, Cn, G0, G1, G2);
    int AND010 = AND_4(P0, G1, G2, G3);
    int AND011 = AND_3(P1, G2, G3);
    int AND012 = AND(P2, G3);

    int NAND01 = NOT(AND(Cn, NOTM));
    int NAND02 = NOT(AND_4(G0, G1, G2, G3));
    int NAND03 = NOT(AND_5(Cn, G0, G1, G2, G3));

    int AND001 = EXOR(P0, G0);
    int AND002 = EXOR(P1, G1);
    int AND003 = EXOR(P2, G2);
    int AND004 = EXOR(P3, G3);

    int NOR001 = NOT(OR(AND01, AND02));
    int NOR002 = NOT(OR_3(AND03, AND04, AND05));
    int NOR003 = NOT(OR_4(AND06, AND07, AND08, AND09));
    int NOR004 = NOT(OR_4(AND010, AND011, AND012, P3));

    
    int F0 = EXOR(NAND01, AND001);
    int F1 = EXOR(NOR001, AND002);
    int F2 = EXOR(NOR002, AND003);
    int F3 = EXOR(NOR003, AND004);

    
    int G = NAND02;
    int P = NOR004;
    int Cn_piu_4 = OR(G, NAND03);

    
    int A_uguale_B = AND_4(F0, F1, F2, F3); 

   
    *G_out = G;
    *Cn_piu_4_out = Cn_piu_4;
    *P_out = P;
    *F3_out = F3;
    *F2_out = F2;
    *A_uguale_B_out = A_uguale_B;
    *F1_out = F1;
    *F0_out = F0;
    *P3_out = P3;
    *P2_out = P2;
    *G3_out = G3;
    *G2_out = G2;
    *P1_out = P1;
    *P0_out = P0;
    *G1_out = G1;
    *G0_out = G0;
}


void decimalToBinary32bit(uint32_t n) {
    char binaryString[33];
    int i;

    for (i = 31; i >= 0; i--) {
        if (n % 2 == 1) {
            binaryString[i] = '1';
        } else {
            binaryString[i] = '0';
        }
        n /= 2;
    }
    binaryString[32] = '\0';

    printf("La rappresentazione binaria a 32 bit: %s\n", binaryString);
}

uint32_t binaryToDecimal(const char *binaryString) {
    uint32_t decimalValue = 0;
    int length = strlen(binaryString);

    if (length != 32) {
        fprintf(stderr, "Errore: La stringa binaria deve essere di 32 bit.\n");
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if (binaryString[i] == '1') {
            decimalValue = (decimalValue << 1) | 1;
        } else if (binaryString[i] != '0') {
            fprintf(stderr, "Errore: La stringa binaria contiene caratteri non validi.\n");
            return 0;
        } else {
            decimalValue = decimalValue << 1;
        }
    }
    return decimalValue;
}

uint32_t convertiBinario4BitInDecimale(const char *stringaBinaria) {
    uint32_t numeroDecimale = 0;
    int lunghezza = strlen(stringaBinaria);
    int i;

    if (lunghezza != 4) {
        fprintf(stderr, "Errore: La stringa binaria deve essere di 4 bit.\n");
        return 0;
    }

    for (i = 0; i < lunghezza; i++) {
        if (stringaBinaria[i] == '1') {
            numeroDecimale = (numeroDecimale << 1) | 1;
        } else if (stringaBinaria[i] != '0') {
            fprintf(stderr, "Errore: Carattere non valido nella stringa binaria.\n");
            return 0;
        } else {
            numeroDecimale = numeroDecimale << 1;
        }
    }
    return numeroDecimale;
}


void ALU_32_BIT_Corrected(
    int A[32], int B[32],
    int S0, int S1, int S2, int S3, int M, int Cn_initial,
    int F[32], int *Final_G, int *Final_P, int *Final_Cn_piu_32, int *Final_A_uguale_B) {

    int current_Cn = Cn_initial;
    int local_G, local_P, local_Cn_piu_4;
    int F_block[4];
    int P_block[4], G_block[4];

    int all_F_equal_1 = 1; 


    for (int i = 0; i < 8; i++) {

        ALU_4_BIT(A[i*4], A[i*4+1], A[i*4+2], A[i*4+3],
                  B[i*4], B[i*4+1], B[i*4+2], B[i*4+3],
                  S0, S1, S2, S3,
                  M, current_Cn,
                  &local_G, &local_Cn_piu_4, &local_P,
                  &F_block[3], &F_block[2], Final_A_uguale_B, 
                  &F_block[1], &F_block[0],
                  &G_block[3], &G_block[2],
                  &P_block[3], &P_block[2],
                  &G_block[1], &G_block[0],
                  &P_block[1], &P_block[0]);

        
        F[i*4] = F_block[0];
        F[i*4+1] = F_block[1];
        F[i*4+2] = F_block[2];
        F[i*4+3] = F_block[3];

        
        current_Cn = local_Cn_piu_4;

      
        if (F_block[0] == 0 || F_block[1] == 0 || F_block[2] == 0 || F_block[3] == 0) {
            all_F_equal_1 = 0;
        }
    }

    *Final_Cn_piu_32 = current_Cn; 

 
    *Final_G = local_G;
    *Final_P = local_P;

    
    *Final_A_uguale_B = all_F_equal_1;
}


void delay(int number_of_seconds) {
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

int main() {
    int s, u = 1, t;
    int e, e1, a, b, SOM, SOT;
    uint32_t decimalNumber;
    uint32_t decimalOutput;
    char binaryInput[33];

    int A[32], B[32]; 
    int F[32];        

    int S0, S1, S2, S3; 
    int M, Cn;          

    int G_32, P_32, Cn_plus_32, A_equals_B_32; 

    printf("Inserire il tempo di ritardo (in secondi) della macchina:");
    scanf("%d", &t);
   

    while (u == 1) {
        printf("\nMENU A SCELTA\n");
        printf("\nALU a 4 BIT = 1\n");
        printf("ALU a 32 BIT = 2\n");
        printf("OPERAZIONI ARITMETICHE = 3\n");
        printf("CONVERTITORE DA DECIMALE A BINARIO = 4\n");
        printf("CONVERTITORE DA BINARIO A DECIMALE = 5\n");
        printf("\nScegli = ");
        scanf("%d", &e);

        if (e == 1) {
            

            int A0, A1, A2, A3;
            int B0, B1, B2, B3;
            int local_F0, local_F1, local_F2, local_F3;
            int local_G, local_P, local_Cn_piu_4, local_A_uguale_B;
            int local_G0, local_G1, local_G2, local_G3;
            int local_P0, local_P1, local_P2, local_P3;

            printf("\nInserisci le variabili per la ALU a 4 BIT:\n");
            
            printf("INSERISCI A (A3 A2 A1 A0)\n"); 
            scanf("%d %d %d %d", &A3, &A2, &A1, &A0);
            printf("INSERISCI B (B3 B2 B1 B0)\n"); 
            scanf("%d %d %d %d", &B3, &B2, &B1, &B0);
            
            printf("----------------------------------------------------------------------------------------------\n");
            printf("| SELECTION               | M = H           | M = L; ARITHMETIC OPERATIONS               |\n");
            printf("|(S3 S2 S1 S0)            | LOGIC FUNCTIONS | Cn' = H (no carry) | Cn' = L (with carry)     |\n");
            printf("----------------------------------------------------------------------------------------------\n");
            printf("| L   L   L   L           | F = A           | F = A              | F = A PLUS 1             |\n");
            printf("| L   L   L   H           | F = A + B       | F = A + B          | F = (A + B) PLUS 1       |\n");
            printf("| L   L   H   L           | F = A'B         | F = A + B'         | F = (A + B') PLUS 1      |\n");
            printf("| L   L   H   H           | F = 0           | F = MINUS 1 (2's COMPL) | F = ZERO             |\n");
            printf("| L   H   L   L           | F = A'B'        | F = A PLUS B'      | F = A PLUS B' PLUS 1     |\n");
            printf("| L   H   L   H           | F = B           | F = (A + B') + AB' | F = (A + B') + AB' PLUS 1 |\n");
            printf("| L   H   H   L           | F = A XOR B     | F = A MINUS B MINUS 1 | F = A MINUS B         |\n");
            printf("| L   H   H   H           | F = A'B'        | F = A'B' MINUS 1   | F = A'B'                 |\n");
            printf("| H   L   L   L           | F = A' + B      | F = A' + B         | F = A' + B PLUS 1        |\n");
            printf("| H   L   L   H           | F = A XOR B     | F = A PLUS B       | F = A PLUS B PLUS 1      |\n");
            printf("| H   L   H   L           | F = B           | F = (A + B') + AB' | F = (A + B') + AB' PLUS 1 |\n");
            printf("| H   L   H   H           | F = A'B         | F = A'B' MINUS 1   | F = A'B'                 |\n");
            printf("| H   H   L   L           | F = 1           | F = A PLUS A       | F = A PLUS A PLUS 1      |\n");
            printf("| H   H   L   H           | F = A' + B'     | F = (A + B') + A   | F = (A + B') + A PLUS 1  |\n");
            printf("| H   H   H   L           | F = A' + B      | F = (A + B') + A   | F = (A + B') + A PLUS 1  |\n");
            printf("| H   H   H   H           | F = A           | F = A              | F = A                    |\n");
            printf("----------------------------------------------------------------------------------------------\n");
            
            printf("INSERISCI S (S3 S2 S1 S0)\n"); 
            scanf("%d %d %d %d", &S3, &S2, &S1, &S0);
            printf("M="); 
            scanf("%d", &M);
            printf("Cn="); 
            scanf("%d", &Cn);

            if ((S0 == 0 || S0 == 1) && (S1 == 0 || S1 == 1) && (S2 == 0 || S2 == 1) && (S3 == 0 || S3 == 1) &&
                (A0 == 0 || A0 == 1) && (A1 == 0 || A1 == 1) && (A2 == 0 || A2 == 1) && (A3 == 0 || A3 == 1) &&
                (B0 == 0 || B0 == 1) && (B1 == 0 || B1 == 1) && (B2 == 0 || B2 == 1) && (B3 == 0 || B3 == 1) &&
                (M == 0 || M == 1) && (Cn == 0 || Cn == 1)) {

                ALU_4_BIT(A0, A1, A2, A3, B0, B1, B2, B3, S0, S1, S2, S3, M, Cn,
                          &local_G, &local_Cn_piu_4, &local_P,
                          &local_F3, &local_F2, &local_A_uguale_B, &local_F1, &local_F0,
                          &local_G3, &local_G2, &local_P3, &local_P2, &local_G1, &local_G0, &local_P1, &local_P0);

                printf("\n\nI risultati sono:\n\n");
                printf("F=");
                printf("%d %d %d %d\n",local_F3, local_F2, local_F1, local_F0);
                /*printf("F3=%d\n", local_F3);
                printf("F2=%d\n", local_F2);
                printf("F1=%d\n", local_F1);
                printf("F0=%d\n", local_F0);*/
                printf("\nG=%d\n", local_G);
                printf("Cn+4=%d\n", local_Cn_piu_4);
                printf("P=%d\n", local_P);
                printf("A=B=%d\n", local_A_uguale_B);
            } else {
                printf("ERRORE. PUOI INSERIRE SOLO 0 O 1\n");
            }

        } else if (e == 3) {
            printf("\nPREMI 1 PER SOMMA 2 PER SOTTRAZIONE\n");
            printf("\nScegli=");
            scanf("%d", &e1);
            if (e1 == 1) {
                printf("\nPRIMO VALORE=");
                scanf("%d", &a);
                printf("\nSECONDO VALORE=");
                scanf("%d", &b);
                SOM = a + b;
                printf("IL RISULTATO DELLA SOMMA E'=%d\n", SOM);
            } else if (e1 == 2) {
                printf("\nPRIMO VALORE=");
                scanf("%d", &a);
                printf("\nSECONDO VALORE=");
                scanf("%d", &b);
                SOT = a - b; 
                printf("IL RISULTATO DELLA SOTTRAZIONE E'=%d\n", SOT);
            }
        } else if (e == 4) {
            printf("Inserisci un numero decimale (0 - 4294967295): ");
            scanf("%u", &decimalNumber);
            decimalToBinary32bit(decimalNumber);
        } else if (e == 5) {
            printf("Inserisci una stringa binaria di 32 bit: ");
            if (scanf("%32s", binaryInput) == 1) {
                decimalOutput = binaryToDecimal(binaryInput);
                if (decimalOutput != 0 || (decimalOutput == 0 && strcmp(binaryInput, "00000000000000000000000000000000") == 0)) {
                    printf("Il valore decimale: %u\n", decimalOutput);
                }
            } else {
                printf("Errore nell'input.\n");
            }
        } else if (e == 2) {
            printf("\nInserisci le variabili per la ALU a 32 BIT:\n");

            uint32_t numero1, numero2;
            printf("Inserisci il primo numero intero senza segno (0 - 4294967295): ");
            scanf("%u", &numero1);
            for (int i = 0; i < 32; i++) {
                A[i] = (numero1 >> i) & 1; 
            }

            printf("Inserisci il secondo numero intero senza segno (0 - 4294967295): ");
            scanf("%u", &numero2);
            for (int i = 0; i < 32; i++) {
                B[i] = (numero2 >> i) & 1; 
            }

            printf("Rappresentazione binaria di A:\n");
            for (int i = 31; i >= 0; i--) { 
                printf("%d", A[i]);
            }
            printf("\n");

            printf("Rappresentazione binaria di B:\n");
            for (int i = 31; i >= 0; i--) { 
                printf("%d", B[i]);
            }
            printf("\n");

            printf("----------------------------------------------------------------------------------------------\n");
            printf("| SELECTION               | M = H           | M = L; ARITHMETIC OPERATIONS                  |\n");
            printf("|(S3 S2 S1 S0)            | LOGIC FUNCTIONS | Cn' = H (no carry) | Cn' = L (with carry)     |\n");
            printf("----------------------------------------------------------------------------------------------\n");
            printf("| L   L   L   L           | F = A           | F = A              | F = A PLUS 1             |\n");
            printf("| L   L   L   H           | F = A + B       | F = A + B          | F = (A + B) PLUS 1       |\n");
            printf("| L   L   H   L           | F = A'B         | F = A + B'         | F = (A + B') PLUS 1      |\n");
            printf("| L   L   H   H           | F = 0           | F = MINUS 1 (2's COMPL) | F = ZERO            |\n");
            printf("| L   H   L   L           | F = A'B'        | F = A PLUS B'      | F = A PLUS B' PLUS 1     |\n");
            printf("| L   H   L   H           | F = B           | F = (A + B') + AB' | F = (A + B') + AB' PLUS 1|\n");
            printf("| L   H   H   L           | F = A XOR B     | F = A MINUS B MINUS 1 | F = A MINUS B         |\n");
            printf("| L   H   H   H           | F = A'B'        | F = A'B' MINUS 1   | F = A'B'                 |\n");
            printf("| H   L   L   L           | F = A' + B      | F = A' + B         | F = A' + B PLUS 1        |\n");
            printf("| H   L   L   H           | F = A XOR B     | F = A PLUS B       | F = A PLUS B PLUS 1      |\n");
            printf("| H   L   H   L           | F = B           | F = (A + B') + AB' | F = (A + B') + AB' PLUS 1|\n");
            printf("| H   L   H   H           | F = A'B         | F = A'B' MINUS 1   | F = A'B'                 |\n");
            printf("| H   H   L   L           | F = 1           | F = A PLUS A       | F = A PLUS A PLUS 1      |\n");
            printf("| H   H   L   H           | F = A' + B'     | F = (A + B') + A   | F = (A + B') + A PLUS 1  |\n");
            printf("| H   H   H   L           | F = A' + B      | F = (A + B') + A   | F = (A + B') + A PLUS 1  |\n");
            printf("| H   H   H   H           | F = A           | F = A              | F = A                    |\n");
            printf("----------------------------------------------------------------------------------------------\n");

            printf("INSERISCI S (S3 S2 S1 S0)\n"); 
            scanf("%d %d %d %d", &S3, &S2, &S1, &S0);
            printf("M="); 
            scanf("%d", &M);
            printf("Cn="); 
            printf("Cn (Carry-in iniziale per il blocco LSB)="); scanf("%d", &Cn);

            if ((S0 == 0 || S0 == 1) && (S1 == 0 || S1 == 1) && (S2 == 0 || S2 == 1) && (S3 == 0 || S3 == 1) &&
                (M == 0 || M == 1) && (Cn == 0 || Cn == 1)) {

                
                ALU_32_BIT_Corrected(A, B, S0, S1, S2, S3, M, Cn,
                                     F, &G_32, &P_32, &Cn_plus_32, &A_equals_B_32);

                printf("\n\nI risultati della ALU a 32 BIT sono:\n\n");
                printf("F (32 bit):\n");
                for (int i = 31; i >= 0; i--) { 
                    printf("%d", F[i]);
                    if (i % 4 == 0 && i != 0) printf(" "); 
                }
                printf("\n");

                printf("G: %d\n", G_32);
                printf("P: %d\n", P_32);
                printf("Cn+32: %d\n", Cn_plus_32);
                printf("A = B? %d\n", A_equals_B_32);

                
                uint32_t F_decimal = 0;
                for (int i = 0; i < 32; i++) {
                    if (F[i] == 1) {
                        F_decimal |= (1U << i);
                    }
                }
                printf("Il risultato di F (decimale): %u\n", F_decimal);

            } else {
                printf("ERRORE. PUOI INSERIRE SOLO 0 O 1\n");
            }
        }
        printf("\nVuoi uscire dal programma? 1 = no 0 = si: ");
        scanf("%d", &s);
        if (s == 0) {
            u = 0; 
        } else if (s != 1) {
            printf("Valore non valido, riavviare il programma\n");
            break; 
        }
    }

    return 0;
}

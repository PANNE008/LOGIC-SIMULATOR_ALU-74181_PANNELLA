#include <stdio.h>

// Simula un ritardo
void ritardo(int cicli) {
    for (volatile int i = 0; i < cicli; i++) {
        // loop vuoto per consumare tempo
    }
}

typedef struct {
    int valore; // 4 bit (0-15)
} Registro4bit;

// Simula comportamento flip-flop D a 4 bit
void aggiornaRegistro(Registro4bit* reg, int CLR, int CLOCK, int S1, int S0, int ingressoParallelo,
                      int serialBit, int direzione /* 0 = sinistra, 1 = destra */) {
    if (CLR == 0) {
        reg->valore = 0;
    } else if (CLOCK == 0) {
        // Mantiene stato
    } else if (S1 == 1 && S0 == 1) {
        reg->valore = ingressoParallelo & 0xF;
    } else if (S1 == 1 && S0 == 0) {
        reg->valore = ((reg->valore << 1) | (serialBit & 1)) & 0xF;
    } else if (S1 == 0 && S0 == 1) {
        reg->valore = ((serialBit << 3) | (reg->valore >> 1)) & 0xF;
    }
}

// Divide un numero 32 bit in 8 registri da 4 bit
void dividiInRegistri(unsigned int val, Registro4bit reg[8]) {
    for (int i = 0; i < 8; i++) {
        reg[i].valore = (val >> ((7 - i) * 4)) & 0xF;
    }
}

// Ricostruisce numero da registri
unsigned int unisciRegistri(Registro4bit reg[8]) {
    unsigned int val = 0;
    for (int i = 0; i < 8; i++) {
        val |= (reg[i].valore & 0xF) << ((7 - i) * 4);
    }
    return val;
}

// Stampa binario 32 bit
void stampaBinario(unsigned int num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0) printf(" ");
    }
    printf("\n");
}

int main() {
    Registro4bit regA[8], regB[8], regOUT[8];
    int CLR, S1, S0, CLOCK, serialLeft, serialRight;

    unsigned int A, B, F = 0;
    printf("=== VALORI IN INGRESSO ===\n");
    printf("Inserire il CLOCK (0 o 1): ");
    scanf("%d", &CLOCK);
    ritardo(400000000);
    printf("Inserisci il valore CLR (0 o 1): "); scanf("%d", &CLR);
    ritardo(400000000);
int M;
    printf("Inserire la modalità di calcolo (1=logico, 0=aritmetico): "); scanf("%d", &M);
    ritardo(400000000);
    if(M==1){
    printf("Attenzione, i valori a e b in modalità logica devono essere 0 o 1 \n");
    ritardo(400000000);
    }
    printf("Inserisci A: ");
    scanf("%x", &A);
    ritardo(400000000);
    if(M==1 && (A<0 || A>1)){
      printf("Valore non valido, riprova");
      return 0;
    }
    printf("Inserisci B: ");
    scanf("%x", &B);
    ritardo(400000000);
    if(M==1 && (B<0 || B>1)){
      printf("Valore non valido, riprova");
      return 0;
    }

    printf("Inserisci S1 dei registri (0 o 1): "); scanf("%d", &S1);
    ritardo(400000000);
    printf("Inserisci S0 dei registri (0 o 1): "); scanf("%d", &S0);
    ritardo(400000000);
    printf("Inserisci serialLeft (0 o 1): "); scanf("%d", &serialLeft);
    ritardo(400000000);
    printf("Inserisci serialRight (0 o 1): "); scanf("%d", &serialRight);
    ritardo(400000000);
    // Divide A e B in registri da 4 bit
    dividiInRegistri(A, regA);
    dividiInRegistri(B, regB);

    // Simula caricamento/shift dei registri
    for (int i = 0; i < 8; i++) {
        aggiornaRegistro(&regA[i], CLR, CLOCK, S1, S0, regA[i].valore, serialRight, 0);
        aggiornaRegistro(&regB[i], CLR, CLOCK, S1, S0, regB[i].valore, serialRight, 0);
    }

    // Ricostruisci A e B dopo il comportamento del registro
    A = unisciRegistri(regA);
    B = unisciRegistri(regB);

    // ALU input
    int S3, S2, S1_alu, S0_alu, Cn;
    printf("\n=== OPERANDI ALU ===\n");
    printf("Inserisci S3 (0 o 1): "); scanf("%d", &S3);
    ritardo(400000000);
    printf("Inserisci S2 (0 o 1): "); scanf("%d", &S2);
    ritardo(400000000);
    printf("Inserisci S1 (0 o 1): "); scanf("%d", &S1_alu);
    ritardo(400000000);
    printf("Inserisci S0 (0 o 1): "); scanf("%d", &S0_alu);
    ritardo(400000000);
    printf("Inserisci il valore del CARRY (0= senza carry, 1= con il carry): "); scanf("%d", &Cn);
    ritardo(400000000);
    printf("Calcolo in corso...");
    ritardo(400000000);
    // ALU (74181 simulata a 32 bit)
    if (M == 0 && Cn == 0) {
        if (S3==0 && S2==0 && S1_alu==0 && S0_alu==0)
            F = A - 1;
        else if (S3==0 && S2==0 && S1_alu==0 && S0_alu==1)
            F = A * B - 1;
        else if (S3==0 && S2==0 && S1_alu==1 && S0_alu==0)
            F = A * (1-B) - 1;
        else if (S3==0 && S2==0 && S1_alu==1 && S0_alu==1)
            F = 0xFFFFFFFF;
        else if (S3==0 && S2==1 && S1_alu==0 && S0_alu==0)
            F = A+(A+(1-B));
        else if (S3==0 && S2==1 && S1_alu==0 && S0_alu==1)
            F = A*B+(A+(1-B));
        else if (S3==0 && S2==1 && S1_alu==1 && S0_alu==0)
            F = A-B-1;
        else if (S3==0 && S2==1 && S1_alu==1 && S0_alu==1)
            F = A+(1-B);
        else if (S3==1 && S2==0 && S1_alu==0 && S0_alu==0)
            F = A+(A+B);
        else if (S3==1 && S2==0 && S1_alu==0 && S0_alu==1)
            F = A+B;
        else if (S3==1 && S2==0 && S1_alu==1 && S0_alu==0)
            F = A*(1-B)+(A+B);
        else if (S3==1 && S2==0 && S1_alu==1 && S0_alu==1)
            F = A*B;
        else if (S3==1 && S2==1 && S1_alu==0 && S0_alu==0)
            F = A+2*A;
        else if (S3==1 && S2==1 && S1_alu==0 && S0_alu==1)
            F = A*B+A;
        else if (S3==1 && S2==1 && S1_alu==1 && S0_alu==0)
            F = A*(1-B)+A;
        else if (S3==1 && S2==1 && S1_alu==1 && S0_alu==1)
            F = A;
            
            //Con il Carry
            
    } else if (M == 0 && Cn == 1) {
        if (S3==0 && S2==0 && S1_alu==0 && S0_alu==0)
            F = A;
        else if (S3==0 && S2==0 && S1_alu==0 && S0_alu==1)
            F = A*B;
        else if (S3==0 && S2==0 && S1_alu==1 && S0_alu==0)
            F = A*(1-B);
        else if (S3==0 && S2==0 && S1_alu==1 && S0_alu==1)
            F = 0;
        else if (S3==0 && S2==1 && S1_alu==0 && S0_alu==0)
            F = A+(A+(1-B))+1;
        else if (S3==0 && S2==1 && S1_alu==0 && S0_alu==1)
            F = A*B+(A+(1-B))+1;
        else if (S3==0 && S2==1 && S1_alu==1 && S0_alu==0)
            F = A-B;
        else if (S3==0 && S2==1 && S1_alu==1 && S0_alu==1)
            F = (A+B)+1;
        else if (S3==1 && S2==0 && S1_alu==0 && S0_alu==0)
            F = A+(A+B)+1;
        else if (S3==1 && S2==0 && S1_alu==0 && S0_alu==1)
            F = A+B+1;
        else if (S3==1 && S2==0 && S1_alu==1 && S0_alu==0)
            F = A*(1-B)+(A+B)+1;
        else if (S3==1 && S2==0 && S1_alu==1 && S0_alu==1)
            F = (A+B)+1;
        else if (S3==1 && S2==1 && S1_alu==0 && S0_alu==0)
            F = A+A+1;
        else if (S3==1 && S2==1 && S1_alu==0 && S0_alu==1)
            F = A*B+A+1;
        else if (S3==1 && S2==1 && S1_alu==1 && S0_alu==0)
            F = A*(1-B)+A+1;
        else if (S3==1 && S2==1 && S1_alu==1 && S0_alu==1)
            F = A+1;
            
            //Operazioni Logiche
            
    } else if (M == 1) {
        if (S3==0 && S2==0 && S1_alu==0 && S0_alu==0)
            F = 1-A;
        else if (S3==0 && S2==0 && S1_alu==0 && S0_alu==1)
            F = (1-A)*(1-B);
        else if (S3==0 && S2==0 && S1_alu==1 && S0_alu==0)
            F = (1-A) + B;
        else if (S3==0 && S2==0 && S1_alu==1 && S0_alu==1)
            F = 1;
        else if (S3==0 && S2==1 && S1_alu==0 && S0_alu==0)
            F = (1-A)+(1-B);
        else if (S3==0 && S2==1 && S1_alu==0 && S0_alu==1)
            F = 1-B;
        else if (S3==0 && S2==1 && S1_alu==1 && S0_alu==0)
            F = (1-A)*B+A*(1-B);
        else if (S3==0 && S2==1 && S1_alu==1 && S0_alu==1)
            F = A+(1-B);
        else if (S3==1 && S2==0 && S1_alu==0 && S0_alu==0)
            F = (1-A)*B;
        else if (S3==1 && S2==0 && S1_alu==0 && S0_alu==1)
            F = A*(1-B)+(1-A)*B;
        else if (S3==1 && S2==0 && S1_alu==1 && S0_alu==0)
            F = B;
        else if (S3==1 && S2==0 && S1_alu==1 && S0_alu==1)
            F = A+B;
        else if (S3==1 && S2==1 && S1_alu==0 && S0_alu==0)
            F = 0;
        else if (S3==1 && S2==1 && S1_alu==0 && S0_alu==1)
            F = A*(1-B);
        else if (S3==1 && S2==1 && S1_alu==1 && S0_alu==0)
            F = A*B;
        else if (S3==1 && S2==1 && S1_alu==1 && S0_alu==1)
            F = A;
    }

    dividiInRegistri(F, regOUT);

    // Output finale
    printf("\n=== RISULTATI ===\n");
    printf("input A  in binario:       "); stampaBinario(A);
    ritardo(400000000);
    printf("input B in binario:       "); stampaBinario(B);
    ritardo(400000000);
    printf("\nRisultati dei registri in uscita (4 bit ciascuno):\n");
    for (int i = 0; i < 8; i++) {
        ritardo(400000000);
        printf("Registro [%d] = %d\n", i, regOUT[i].valore);
    }

    ritardo(400000000);
    printf("\nRisultato dell'operazione in binario: ");
    stampaBinario(F);
    ritardo(400000000);
    printf("Risultato dell'operazione in decimale: %u\n", F);

    return 0;
}

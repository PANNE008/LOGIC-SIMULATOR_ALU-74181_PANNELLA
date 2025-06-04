ritardo(int cicli):
Funzione che simula un'attesa tramite loop vuoto.

Registro4bit:
Struttura dati che rappresenta 8 registri da 4 bit.

aggiornaRegistro(...):
Simula un flip-flop D per registri a 4 bit con supporto a caricamento parallelo, shift a sinistra e a destra.

dividiInRegistri(unsigned int val, Registro4bit reg[8]):
Divide un numero a 32 bit in 8 registri da 4 bit.

unisciRegistri(Registro4bit reg[8]):
Ricompone un intero da 32 bit a partire dagli 8 registri da 4 bit.

stampaBinario(unsigned int num):
Stampa un numero a 32 bit in formato binario (separato ogni 4 bit).

main():
Contiene l'intera logica:
Input da tastiera: A, B, modalità operativa, segnali S1/S0, segnali della ALU.
Comportamento dei registri (clear, caricamento, shift).
Simulazione dell’ALU in modalità logica o aritmetica.
Output dei registri e del risultato finale.

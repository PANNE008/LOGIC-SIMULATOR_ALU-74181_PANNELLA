# Funzioni del simulatore

In questo testo sono presenti tutte le funzioni del simulatore:

- **Ritardo(int cicli)**: Funzione che simula un'attesa tramite loop vuoto.
- **Registro4bit**: Struttura dati che rappresenta 8 registri da 4 bit.
- **AggiornaRegistro(...)**: Simula un flip-flop D per registri a 4 bit con supporto a caricamento parallelo, shift a sinistra e a destra.
- **DividiInRegistri(unsigned int val, Registro4bit reg[8])**: Divide un numero a 32 bit in 8 registri da 4 bit.
- **UnisciRegistri(Registro4bit reg[8])**: Ricompone un intero da 32 bit a partire dagli 8 registri da 4 bit.
- **StampaBinario(unsigned int num)**: Stampa un numero a 32 bit in formato binario (separato ogni 4 bit).
- **Main()**: Contiene l'intera logica:
  - Input da tastiera: A, B, modalità operativa, segnali S1/S0, segnali della ALU.
  - Comportamento dei registri (clear, caricamento, shift).
  - Simulazione dell’ALU in modalità logica o aritmetica.
  - Output dei registri e del risultato finale.


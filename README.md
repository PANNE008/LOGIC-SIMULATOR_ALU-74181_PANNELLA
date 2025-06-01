GUIDA AL CODICE SIMULAZIONE ALU + REGISTRI 4-BIT
================================================

DESCRIZIONE GENERALE:
------------------------------
Questo codice C simula il comportamento di una ALU (Unità Aritmetico Logica) 74181 a 32 bit e di registri a 4 bit basati su flip-flop D. L'intero processo è orientato all'elaborazione di due input A e B, divisi in 8 registri da 4 bit ciascuno, e ad eseguire operazioni logiche o aritmetiche su di essi, restituendo un risultato F anch'esso distribuito su 8 registri a 4 bit.

STRUTTURA PRINCIPALE:
------------------------------
1. **ritardo(int cicli)**:
   - Funzione che simula un'attesa tramite loop vuoto.

2. **Registro4bit**:
   - Struttura dati che rappresenta 8 registri da 4 bit.

3. **aggiornaRegistro(...)**:
   - Simula un flip-flop D per registri a 4 bit con supporto a caricamento parallelo, shift a sinistra e a destra.

4. **dividiInRegistri(unsigned int val, Registro4bit reg[8])**:
   - Divide un numero a 32 bit in 8 registri da 4 bit.

5. **unisciRegistri(Registro4bit reg[8])**:
   - Ricompone un intero da 32 bit a partire dagli 8 registri da 4 bit.

6. **stampaBinario(unsigned int num)**:
   - Stampa un numero a 32 bit in formato binario (separato ogni 4 bit).

7. **main()**:
   - Contiene l'intera logica:
     - Input da tastiera: A, B, modalità operativa, segnali S1/S0, segnali della ALU.
     - Comportamento dei registri (clear, caricamento, shift).
     - Simulazione dell’ALU in modalità logica o aritmetica.
     - Output dei registri e del risultato finale.

INPUT UTENTE:
------------------------------
- CLOCK: segnale di clock (0 o 1)
- CLR: clear (0 per azzerare i registri)
- M: modalità operativa (1 = logica, 0 = aritmetica)
- A, B: valori in esadecimale (se M=1, devono essere 0 o 1)
- S1, S0: controllano il comportamento dei registri
- serialLeft, serialRight: bit per operazioni di shift
- S3, S2, S1, S0: selettori operazione ALU
- Cn: Carry in (0 o 1)

MODALITÀ OPERATIVE:
------------------------------
- M = 0 (Aritmetica):
  Include operazioni su A e B, con e senza carry: somma, sottrazione, prodotti e combinazioni.

- M = 1 (Logica):
  A e B sono trattati come bit logici.
  Supporta operazioni booleane: NOT, AND, OR, XOR, etc.

FUNZIONAMENTO REGISTRI:
------------------------------
S1 | S0 | Operazione
---|----|-------------
 0 |  0 | Mantieni valore
 0 |  1 | Shift a destra
 1 |  0 | Shift a sinistra
 1 |  1 | Caricamento parallelo

OUTPUT:
------------------------------
- Stato binario di A e B dopo caricamento/shift.
- Valori dei registri in uscita (8 registri da 4 bit).
- Risultato F in binario e decimale.

NOTE UTILI:
------------------------------
- Il sistema accetta input in esadecimale per A e B (tranne in modalità logica).
- Il codice usa ritardi artificiali per simulare operazioni hardware.
- Ogni registrazione, shift o operazione ALU agisce a livello di registri da 4 bit.

TABELLA DEGLI OPERANDI S3,S2,S1,S0 PER TUTTE LE OPERAZIONI POSSIBILI DELL'ALU:

------------------------------

SELECTION       | M = H                    | M = L; ARITHMETIC OPERATIONS
S3 S2 S1 S0     | LOGIC FUNCTIONS          | Cn = L (no carry)         | Cn = H (with carry)
----------------------------------------------------------------------------------------------
L  L  L  L      | F = A̅                    | F = A MINUS 1             | F = A
L  L  L  H      | F = A̅B                   | F = AB MINUS 1            | F = AB
L  L  H  L      | F = A + B                | F = AB̅ MINUS 1            | F = A̅B
L  L  H  H      | F = 1                    | F = MINUS 1 (2’s COMP)    | F = ZERO
L  H  L  L      | F = A + B                | F = A PLUS (A + B̅)        | F = A PLUS (A + B̅) PLUS 1
L  H  L  H      | F = B̅                    | F = AB PLUS (A + B)       | F = AB PLUS (A + B) PLUS 1
L  H  H  L      | F = A ⊕ B               | F = A MINUS B MINUS 1     | F = A MINUS B
L  H  H  H      | F = A + B̅                | F = A + B̅                 | F = (A + B̅) PLUS 1
H  L  L  L      | F = A̅B                   | F = A PLUS (A + B)        | F = A PLUS (A + B) PLUS 1
H  L  L  H      | F = A̅ ⊕ B               | F = A PLUS B              | F = A PLUS B PLUS 1
H  L  H  L      | F = B                    | F = AB PLUS (A + B)       | F = AB PLUS (A + B) PLUS 1
H  L  H  H      | F = A + B                | F = (A + B)               | F = (A + B) PLUS 1
H  H  L  L      | F = 0                    | F = A PLUS A‡             | F = A PLUS A PLUS 1
H  H  L  H      | F = AB                   | F = AB PLUS A             | F = AB PLUS A PLUS 1
H  H  H  L      | F = A̅B                   | F = A̅B PLUS A             | F = A̅B PLUS A PLUS 1
H  H  H  H      | F = A                    | F = A                     | F = A PLUS 1

‡ Each bit is shifted to the next more significant position.

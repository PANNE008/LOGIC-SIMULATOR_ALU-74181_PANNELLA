
# Guida all’uso del programma ALU (Unità Logico-Aritmetica) in C

Questo programma simula un’**ALU (Arithmetic Logic Unit)** a **4 bit** e **32 bit**, come quelle usate nei processori reali (es. il famoso chip **74181**).  
Permette di eseguire **operazioni logiche** (AND, OR, XOR, ecc.) e **aritmetiche** (somma, sottrazione, complemento a 2, ecc.) su numeri binari.

---

## 🔧 **Funzionalità principali**

Il programma offre un **menu interattivo** con 5 opzioni:

| Opzione | Funzione |
|--------|---------|
| **1** | Simula un’**ALU a 4 bit** (ingressi manuali bit per bit) |
| **2** | Simula un’**ALU a 32 bit** (inserisci numeri decimali → convertiti in binario) |
| **3** | Esegue **somma o sottrazione** tra due numeri interi (solo aritmetica base) |
| **4** | **Converte un numero decimale** in **binario a 32 bit** |
| **5** | **Converte una stringa binaria a 32 bit** in **numero decimale** |

---

## ⏱️ **Tempo di ritardo**
All’avvio, ti chiede un **tempo di ritardo** (in secondi).  
> **Nota**: Questo valore **non influisce sul funzionamento** dell’ALU — è solo un’opzione storica o didattica (forse per simulare un “ritardo di elaborazione”). Puoi inserire **0** per andare veloce.

---

## 📌 **Opzione 1: ALU a 4 BIT**

### ✅ Cosa fa?
Simula un’ALU a 4 bit. Devi inserire **manualmente ogni bit** di due numeri A e B (da 0 a 1), più i segnali di controllo.

### 🔢 Input richiesti:
1. **A3 A2 A1 A0** → i 4 bit del primo numero (A), **dal più significativo (A3) al meno (A0)**  
   Esempio: per il numero `5` (`0101`), inserisci: `0 1 0 1`
2. **B3 B2 B1 B0** → i 4 bit del secondo numero (B)
3. **S3 S2 S1 S0** → **segnali di selezione** (definiscono l’operazione)
4. **M** → modalità:
   - `1` = **Logica** (AND, OR, XOR, ecc.)
   - `0` = **Aritmetica** (somma, sottrazione, ecc.)
5. **Cn** → **carry-in** (solo per operazioni aritmetiche):
   - `1` = **senza carry iniziale** (es. `A + B`)
   - `0` = **con carry iniziale** (es. `A + B + 1`)

### 📊 Tabella delle operazioni
Dopo aver inserito i dati, il programma mostra una **tabella di riferimento** con tutte le operazioni possibili in base a **S3-S0, M e Cn**.

> 📝 **Esempio pratico**:  
> Vuoi calcolare `A - B`?  
> Usa: **S = 0 1 1 0**, **M = 0**, **Cn = 1** → Risultato: `F = A - B`

### 🖨️ Output:
- `F3 F2 F1 F0`: risultato dell’operazione (4 bit)
- `G`: **Generate** (segnale di propagazione del carry)
- `P`: **Propagate**
- `Cn+4`: carry-out dopo il 4° bit
- `A=B`: `1` se A == B, `0` altrimenti

---

## 📌 **Opzione 2: ALU a 32 BIT**

### ✅ Cosa fa?
Simula un’ALU a **32 bit** usando **8 blocchi di ALU a 4 bit** collegati in cascata (carry look-ahead).

### 🔢 Input richiesti:
1. **Primo numero**: un intero **senza segno** da `0` a `4294967295` (2³² - 1)
2. **Secondo numero**: stesso range
3. **S3 S2 S1 S0**, **M**, **Cn**: stessi significati della ALU a 4 bit

> Il programma converte automaticamente i numeri in binario (LSB = bit 0).

### 🖨️ Output:
- **F (32 bit)**: risultato in binario, mostrato **dal bit 31 al bit 0** (MSB → LSB), con spazi ogni 4 bit per leggibilità
- **F (decimale)**: valore decimale del risultato
- **G, P, Cn+32**: segnali globali dell’ALU a 32 bit
- **A = B?**: `1` se i due numeri sono uguali

> ✅ **Ideale per testare operazioni su numeri grandi** senza dover inserire 32 bit manualmente!

---

## 📌 **Opzione 3: Operazioni aritmetiche semplici**
- **1**: Somma due numeri interi
- **2**: Sottrae due numeri interi  
> Utile per confronto rapido, ma **non usa l’ALU simulata**.

---

## 📌 **Opzioni 4 e 5: Conversioni binario/decimale**
- **Opzione 4**: Inserisci un numero decimale → ottieni la sua rappresentazione **binaria a 32 bit**.
- **Opzione 5**: Inserisci una stringa di **32 caratteri** (`0` o `1`) → ottieni il valore **decimale**.

> ⚠️ Attenzione: la stringa deve essere **esattamente di 32 bit** (es. `00000000000000000000000001010101`).

---

## 🛑 **Regole importanti**
- Tutti i valori di input **devono essere 0 o 1** per i bit e i segnali (S, M, Cn).
- I numeri per la ALU a 32 bit devono essere **interi senza segno** (≥ 0).
- Se inserisci valori non validi, il programma mostra **"ERRORE"**.

---

## 💡 **Consigli per l’uso**
1. **Per imparare il funzionamento dell’ALU**: usa prima l’**opzione 1** con numeri piccoli (es. A=5, B=3).
2. **Per operazioni reali**: usa l’**opzione 2** con numeri decimali.
3. **Per verificare conversioni**: usa opzioni 4 e 5 in coppia.
4. **Per sottrarre**: ricorda che `A - B = A + (~B) + 1`, quindi usa **M=0, Cn=1, S=0110**.

---

## 🎯 **Esempi pratici**

### Esempio 1: Somma A + B (4 bit)
- A = 6 → `0 1 1 0`
- B = 3 → `0 0 1 1`
- S = `0 0 0 1` (somma)
- M = `0` (aritmetica)
- Cn = `1` (nessun carry iniziale)
- Risultato: `F = 1 0 0 1` → **9**

### Esempio 2: A - B (32 bit)
- A = 100
- B = 25
- S = `0 1 1 0`
- M = `0`
- Cn = `1`
- Risultato: `F = 75` (in decimale)

---

## ❓ **Domande frequenti**

**Q: Perché il risultato a volte è negativo?**  
R: Il programma usa **numeri senza segno**, quindi non mostra valori negativi. Se il risultato è troppo grande, va in **overflow** (es. 4000000000 + 4000000000 → numero grande, ma positivo).

**Q: Cosa sono G e P?**  
R: Sono segnali usati nei **circuiti carry-lookahead** per accelerare il calcolo del carry. Non influenzano direttamente F, ma sono importanti per l’architettura hardware.

**Q: Posso usare numeri negativi?**  
R: No, il programma lavora solo con **interi senza segno**. Per i negativi, dovresti usare il **complemento a 2**, ma non è supportato direttamente.

---

## ✅ **Conclusione**

Questo programma è uno **strumento didattico potente** per:
- Capire come funziona un’ALU reale
- Sperimentare con operazioni logiche e aritmetiche
- Imparare la rappresentazione binaria e il ruolo dei segnali di controllo

> 🚀 **Suggerimento finale**: stampa la tabella delle operazioni (mostrata nel menu) e usala come riferimento durante i test!

---

Se hai dubbi su un’operazione specifica o vuoi capire meglio un risultato, chiedi pure! 



# Line Follower Robot – Olimpiadi Robotiche 2019

Arduino powered autonomous line follower developed for the Italian ["Olimpiadi Robotiche"](https://www.makerslab.it/olimpiadi-robotiche/)
## 🇮🇹 Descrizione (Italiano)
Questo progetto documenta il robot sviluppato per la disciplina **Line Follower** delle *Olimpiadi Robotiche*, organizzate da Makerslab.it e Blu Nautilus. Il robot utilizza tre sensori IR per rilevare una pista nera su fondo chiaro e due servi (trattati come motori) per muoversi e correggere la traiettoria. L'algoritmo è stato ottimizzato per gestire:
- avvio controllato (fase di posizionamento prima di `partito = 1`)
- riconoscimento di pattern di curva (011 / 110 / 001 / 100)
- stabilizzazione dopo angoli a 90° (gestione sequenza di 000)
- semplice "switch" correttivo quando i tre sensori vedono nero (111)

Il codice attuale è volutamente chiaro e didattico, pensato come base per successive migliorie (PID, filtraggio, calibrazione dinamica, Bluetooth, ecc.).

## 🇬🇧 Overview (English)
This repository showcases an **Arduino line follower** built for the *Olimpiadi Robotiche* competition in Italy. It uses three infrared sensors to detect a black track and two servo motors for differential movement. The control logic handles:
- controlled start phase (waiting to be correctly aligned)
- curve pattern detection (011 / 110 / 001 / 100)
- 90° corner recovery after repeated 000 readings
- corrective switch when all sensors detect black (111)

The implementation favors readability for future enhancement (PID control, signal smoothing, dynamic calibration, Bluetooth remote, etc.).

---
## Hardware / Componenti
| Component | Qty | Notes |
|----------|-----|-------|
| Arduino Uno / Nano | 1 | Main MCU |
| Servo (continua rotazione o modificato) | 2 | Collegati a pin `11` (sx) e `12` (dx) |
| Sensori IR riflessione | 3 | Pin digitali `4` (SX), `3` (CT), `2` (DX) |
| Telaio + Ruote | 1 | Struttura meccanica |
| Batteria (LiPo / NiMH) | 1 | Alimentazione stabile |
| Cavi / Breadboard | - | Collegamenti |

> Assicurarsi che i servi siano alimentati in modo adeguato (possibilmente linea separata con GND comune) per evitare brown-out dell'Arduino.

## Pin Mapping
```
IR_SX -> D4
IR_CT -> D3
IR_DX -> D2
MOTORE_SX (Servo) -> D11
MOTORE_DX (Servo) -> D12
Serial Monitor -> 9600 baud
```

## Code Structure / Struttura del Codice
File principale: `Seguilinea_01.ino`

Key functions:
- `setup()` – inizializza seriale e pin.
- `muoviMotori(int motoreSinistro, int motoreDestro)` – converte valori servo e gestisce attach/detach per ridurre jitter quando in posizione neutra (`90`).
- `testMotori()` – routine diagnostica per verificare direzioni e velocità.
- `loop()` – stato di avvio e poi logica di inseguimento linea.

Main state variables (estratto):
| Variabile | Funzione |
|-----------|----------|
| `partito` | Passa a 1 dopo corretta sequenza di posizionamento |
| `rilievato011` / `rilievato110` | Memoria ultima curva rilevata |
| `i`, `j` | Contatori per stabilizzazione pattern (000 e 010) |
| `switchWait` | Previene switch ripetuti nel caso 111 |
| `stavoFacendoCurva` | Flag per capire se eravamo in una fase di curva |

### Sensor Patterns / Pattern Sensori
Rappresentiamo i tre sensori come `SX CT DX`:
| Pattern | Significato | Azione tipica |
|---------|-------------|---------------|
| `010` | Centro sulla linea | Progredire dritto |
| `011` | Curva verso destra | Leggera rotazione / memorizzazione stato |
| `110` | Curva verso sinistra | Leggera rotazione / memorizzazione stato |
| `001` / `100` | Ingresso curva accentuata | Rotazione più marcata |
| `000` | Nessuna linea (forse angolo) | Recupero usando stato memorizzato |
| `111` | Artefatto / incrocio / mis-lettura | Possibile switch di variabili |

### Corner Recovery / Recupero Angoli
Quando `000` persiste per 3 cicli (`i == 3`), il codice verifica se l'ultima curva memorizzata era `rilievato011` o `rilievato110` e ruota fino a ritrovare `010`, poi effettua un piccolo riassestamento.

## Getting Started / Avvio
1. Montare sensori IR: distanza da terra costante; testare output (nero = HIGH?).
2. Collegare servi ai pin 11 e 12 (verificare direzione: invertire se necessario.)
3. Caricare `Seguilinea_01.ino` su Arduino.
4. Aprire Serial Monitor a `9600` baud.
5. Posizionare il robot con tutti i sensori sul nero (`111`) per attivare il posizionamento iniziale.
6. Muovere finché legge pattern intermedi (es. `010` ripetutamente) e parte automaticamente (`partito = 1`).
7. Osservare log per debug su sequenze curve.

### Motor Test / Test Motori
Decommentare ed eseguire `testMotori();` (chiamandolo manualmente dentro `loop()`) per verificare configurazione e polarità.

## Enhancements / Miglioramenti Futuri
| Idea | Beneficio |
|------|-----------|
| PID control | Maggior precisione e fluidità |
| Filtraggio letture (media mobile) | Riduzione rumore su superfici irregolari |
| Calibrazione automatica in setup | Adattamento a diverse piste |
| Modalità gara vs. debug | Parametri ottimizzati / logging ridotto |
| Bluetooth (SoftwareSerial) | Start remoto e telemetria |
| Odometria / encoder | Misura distanza / analisi performance |
| Safety timeout | Recupero da loop bloccati |

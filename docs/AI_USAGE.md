
# AI_USAGE.md

Dieses Dokument beschreibt den Einsatz von KI-Werkzeugen im Rahmen des Projekts.

## Werkzeuge

Siemensgpt (Claude und Chat.gpt)

## Nutzen der Werkezeuge

Verwendung der KI in der `Formel.md` Datei in den Bereichen:

- Verwendung für die Erstellung der folgenden Formeln: Geschwindigkeitsfaktor pro Segment, Windfaktor und Höhenfaktor
- Überprüfen der selbsterstellten Formeln  
- Schreibweisehilfen in einer .md Datei (Beispiel: $Formel$, > für Hinweise, **Druck**, $E_{Basis}$, $\text{Schreibstil}$, Case-Aufbau,\times (Multiplikation)...)

Verwendung der KI in der `rechnerTest.cpp`:

- Kontrolle des Codes --> Approx Schreibweise bei double Vergleich (Flüchtigkeitsfehler)
- Allgemeine Git-Bash Befehle für das Testen

Verwendung der KI in der `readJson.cpp`:

- SiemensGPT wurde zur Fehlerbehandlung genutzt
- die Ideen für die Absicherung des Codes mit try-catch, sowie für die Verwendung des std::optional-Datentyps kamen von SiemensGPT

Verwendung der KI in der `readJson.h`:

- die Information, dass Strukturen Operatoren hinzugefügt werden können kam von SiemensGPT

Verwendung der KI in der `ReadJsonTest.h`:

- Hilfe bei der genauen Abfrage der Nachrichten im Fehlerfall

Verwendung der KI in der `README.md`:

- Hilfe bei Synthax eines Klassendiagramms (mermaid...)
- Erklärung der KI, wie man Bilder in eine .md Datei einfügt
- Synthax für Bash-Anzeige

Allgemeine Verwendung:

- C++ Synthaxhilfen
- Allgemeine GIT fragen

## Überprüfung der erzeugten Ergebnisse

- Bei KI generierten Formeln wurde versucht die Formel herzuleiten oder stichpunktartig Werte eingefügt und nach Plausabilität der Ergebnisse geguckt.  

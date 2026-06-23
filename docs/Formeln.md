# Berechnungen und Formeln

## Übersicht

Dieses Dokument beschreibt alle mathematischen Formeln und Berechnungen

## 1.Fahrzeugprofil

Dauerhafte Eigenschaften eines Elektrofahrzeugs, z. B

- Name
- Batteriekapazität
- durchschnittlichen Basisverbrauch.

### Fahrzeugparameter

| Parameter         | Symbol      | Einheit   | Beschreibung                 |
|---------------    |--------     |---------  |--------------                |
| Batteriekapazität | $E_{bat}$   | kWh       | Gesamte Batteriekapazität    |
| Basisverbrauch    | $V_{basis}$ | kWh/100km | Durchschnittlicher Verbrauch |

## 2.Streckenprofil

beschreibt eine vereinfachte Fahrtstrecke:

- Name
- Gesamtdistanz
- Strecke mit mehreren Segmenten z. B. Stadt, Landstraße und Autobahn
- Jedes Segment besitzt eine Distanz und eine Durchnittsgeschwindigkeit
- Höhenmeter bergauf und bergab

### Distanz-Berechnung

$$D_{gesamt} = \sum_{i=1}^{n} D_i$$

wobei $D_i$ die Distanz des i-ten Segments ist.

**Fahrtzeit pro Segment:**

$$t_i = \frac{D_i}{v_i}$$

wobei $v_i$ die Durchschnittsgeschwindigkeit des Segments ist.

**Gesamtfahrtzeit:**

$$t_{gesamt} = \sum_{i=1}^{n} t_i$$

## 3. Wetterprofil

beschreibt vereinfachte Wetterbedingungen für die Fahrt, z. B.

- Temperatur
- Regen
- Windgeschwindigkeit

### Wetterparameter

| Parameter              | Symbol    | Einheit | Bereich      | Beschreibung                     |
|------------------------|-----------|---------|--------------|----------------------------------|
| Temperatur             | $T$       | °C      | -20 bis +50  | Außentemperatur                  |
| Regen                  | $R$       | bool    | true/false   | Regen ja/nein                    |
| Windgeschwindigkeit    | $W$       | km/h    | 0 bis 100    | Gegenwind/Rückenwind             |

## 4. Energieberechnung

beschreibt die Berechnung des Energieverbrauchs basierend auf Fahrzeug, Strecke und Wetter, z. B.

- Basisenergieverbrauch
- Wetter-Einflussfaktoren (Temperatur, Regen, Wind)
- Höhen-Einflussfaktoren (Steigungen, Gefälle)
- Gesamtenergieverbrauch
  
### 4.1 Basisenergieverbrauch

**Energieverbrauch für Segment i:**

$$E_{basis,i} = \frac{D_i}{100} \times V_{basis}$$

**Gesamter Basisverbrauch:**

$$E_{basis} = \sum_{i=1}^{n} E_{basis,i} = \frac{D_{gesamt}}{100} \times V_{basis}$$

### 4.2 Geschwindigkeits-Einflussfaktor

Der Energieverbrauch hängt von der Fahrgeschwindigkeit ab. Höhere Geschwindigkeiten führen zu höherem Verbrauch.

**Geschwindigkeitsfaktor pro Segment:**

$$f_{v,i} = 1 + 0.01 \times (v_i - 50)^2 / 100$$

**Annahmen:**

- Referenzgeschwindigkeit: 50 km/h (Basisverbrauch)
- Bei 50 km/h: $f_{v} = 1.0$ (kein Zusatzverbrauch)
- Bei 100 km/h: $f_{v} \approx 1.25$ (25% mehr Verbrauch)
- Bei 130 km/h: $f_{v} \approx 1.64$ (64% mehr Verbrauch)

### 4.3 Temperatur-Einflussfaktor

Niedrige Temperaturen erhöhen den Energieverbrauch durch Heizung und reduzierte Batterieleistung.

**Temperaturabhängiger Faktor:**

$$f_{T} = \begin{cases}
1.0 + 0.03 \times (20 - T) & \text{wenn } T < 20°C \\
1.0 & \text{wenn } 20°C \leq T \leq 25°C \\
1.0 + 0.02 \times (T - 25) & \text{wenn } T > 25°C
\end{cases}$$

**Annahmen:**
- Optimale Temperatur: 20-25°C
- Bei 0°C: $f_{T} = 1.6$ (60% mehr Verbrauch)
- Bei -20°C: $f_{T} = 2.2$ (120% mehr Verbrauch)
- Bei 35°C: $f_{T} = 1.2$ (20% mehr Verbrauch durch Klimaanlage)

### 4.4 Regen-Einflussfaktor

Regen erhöht den Rollwiderstand und den Luftwiderstand.

**Regen-Faktor:**

$$f_{R} = \begin{cases}
1.05 & \text{wenn Regen = true} \\
1.0 & \text{wenn Regen = false}
\end{cases}$$

**Annahmen:**
- Regen führt zu ca. 5% mehr Verbrauch

### 4.5 Wind-Einflussfaktor

Gegenwind erhöht den Luftwiderstand quadratisch.

**Wind-Faktor:**

$$f_{W} = 1 + 0.001 \times W^2 / 100$$

wobei $W$ die Windgeschwindigkeit in km/h ist.

**Annahmen:**
- Bei 20 km/h Gegenwind: $f_{W} \approx 1.04$ (4% mehr Verbrauch)
- Bei 40 km/h Gegenwind: $f_{W} \approx 1.16$ (16% mehr Verbrauch)

### 4.6 Höhen-Einflussfaktor

Steigungen erhöhen den Energieverbrauch, Gefälle reduzieren ihn (Rekuperation).

**Höhenfaktor:**

$$f_{H} = 1 + \frac{(H_{auf} - 0.5 \times H_{ab}) \times 10}{D_{gesamt}}$$

wobei:
- $H_{auf}$ = Höhenmeter bergauf (m)
- $H_{ab}$ = Höhenmeter bergab (m)
- $D_{gesamt}$ = Gesamtdistanz (km)

**Annahmen:**
- Bergauf: ca. 10 Wh/m Höhe pro 100 km Strecke
- Bergab: ca. 50% Rekuperation (Rückgewinnung)
- Beispiel: 500 m auf, 500 m ab über 100 km: $f_{H} = 1 + \frac{(500 - 250) \times 10}{100} = 1.25$ (25% mehr)

### 4.7 Streckentypabhängiger Faktor

Verschiedene Streckentypen haben unterschiedliche Verbrauchsprofile.

**Streckentypfaktor:**

$$f_{S,i} = \begin{cases}
1.15 & \text{wenn Typ = "Stadt"} \\
1.0 & \text{wenn Typ = "Landstraße"} \\
0.95 & \text{wenn Typ = "Autobahn"}
\end{cases}$$

**Annahmen:**
- Stadt: Häufiges Bremsen und Beschleunigen → 15% mehr Verbrauch
- Landstraße: Durchschnittlicher Verbrauch (Referenz)
- Autobahn: Konstante Geschwindigkeit, weniger Bremsenergie → 5% weniger (aber Geschwindigkeitsfaktor wirkt sich aus)

### 4.8 Gesamtenergieverbrauch

**Energieverbrauch pro Segment:**

$$E_i = E_{basis,i} \times f_{v,i} \times f_{T} \times f_{R} \times f_{W} \times f_{H} \times f_{S,i} $$

**Gesamtenergieverbrauch:**

$$E_{gesamt} = \sum_{i=1}^{n} E_i$$

**Vereinfachte Formel (wenn alle Segmente ähnlich sind):**

$$E_{gesamt} = E_{basis} \times f_{v,avg} \times f_{T} \times f_{R} \times f_{W} \times f_{H} \times f_{S,avg} $$

wobei $f_{v,avg}$ und $f_{S,avg}$ Durchschnittswerte sind.
## 5. Reichweitenberechnung

beschreibt die Berechnung der verfügbaren Reichweite, z. B.

- Verfügbare Energie (basierend auf Ladezustand)
- Puffer-Energie (Reserve)
- Nutzbare Energie
- Maximale Reichweite
- Vergleich: Erforderliche Energie vs. Verfügbare Energie

### 5.1 Verfügbare Energie

**Verfügbare Energie basierend auf Ladezustand:**

$$E_{verfügbar} = \frac{SoC}{100} \times E_{bat}$$

wobei $SoC$ der State of Charge (Ladezustand in %) ist.

### 5.2 Puffer-Energie (Reserve)

Eine Reserve wird empfohlen, um Sicherheit zu gewährleisten.

**Puffer-Energie:**

$$E_{puffer} = 0.1 \times E_{bat}$$

**Annahmen:**
- Mindestens 10% der Batteriekapazität sollte als Reserve verbleiben
- Dies entspricht typischen Herstellerempfehlungen

### 5.3 Nutzbare Energie

**Nutzbare Energie für die Fahrt:**

$$E_{nutzbar} = E_{verfügbar} - E_{puffer}$$

### 5.4 Maximale Reichweite

**Theoretische maximale Reichweite:**

$$R_{max} = \frac{E_{nutzbar}}{V_{basis} / 100}$$

**Realistische Reichweite unter aktuellen Bedingungen:**

$$R_{real} = \frac{E_{nutzbar}}{(V_{basis} \times f_{v,avg} \times f_{T} \times f_{R} \times f_{W} \times f_{H} \times f_{S,avg}) / 100}$$

### 5.5 Vergleich: Erforderliche vs. Verfügbare Energie

**Energiedefizit (falls Fahrt nicht möglich):**

$$\Delta E = E_{gesamt} - E_{nutzbar}$$

**Erforderlicher Ladezustand:**

$$SoC_{erforderlich} = \frac{(E_{gesamt} + E_{puffer})}{E_{bat}} \times 100$$

**Verbleibende Reserve (falls Fahrt möglich):**

$$E_{reserve} = E_{nutzbar} - E_{gesamt}$$

## 6. Machbarkeit und Empfehlungen

beschreibt die Bewertung, ob eine Fahrt möglich ist und gibt Empfehlungen, z. B.

- Fahrt möglich: Ja/Nein
- Sicherhehitsmarge
- Notwendiger Ladezustand
- Empfohlene Ladestationen
- Fahrstil-Empfehlungen
- Wetterwarnungen
  
  ### 6.1 Fahrtmachbarkeit

**Bedingung für machbare Fahrt:**

$$\text{Fahrt möglich} = \begin{cases}
\text{Ja} & \text{wenn } E_{gesamt} \leq E_{nutzbar} \\
\text{Nein} & \text{wenn } E_{gesamt} > E_{nutzbar}
\end{cases}$$

### 6.2 Sicherheitsmarge

**Empfohlene Sicherheitsmarge:**

$$E_{sicherheit} = 0.15 \times E_{nutzbar}$$

**Sichere Fahrtmachbarkeit:**

$$\text{Fahrt sicher möglich} = \begin{cases}
\text{Ja} & \text{wenn } E_{gesamt} \leq (E_{nutzbar} - E_{sicherheit}) \\
\text{Nein} & \text{sonst}
\end{cases}$$

### 6.3 Warnstufen

| Bedingung                                                           | Status       | Empfehlung |
|-----------                                                          |--------      |------------|
| $E_{reserve} > 0.2 \times E_{nutzbar}$                              | Grün      | Fahrt problemlos möglich |
| $0.05 \times E_{nutzbar} < E_{reserve} \leq 0.2 \times E_{nutzbar}$ | Gelb      | Fahrt möglich, aber Vorsicht |
| $E_{reserve} \leq 0.05 \times E_{nutzbar}$                          | Rot       | Fahrt nicht empfohlen |
| $E_{reserve} < 0$                                                   | Unmöglich | Fahrt nicht möglich |

## 7. Fahrstil-Anpassung

beschreibt den Einfluss des Fahrstils auf den Energieverbrauch, z. B.

- Eco-Modus (weniger Verbrauch)
- Normal-Modus (Standard-Verbrauch)
- Sport-Modus (mehr Verbrauch)
  
### 7.1 Verbrauchsreduktion durch Fahrstil

**Energieeinsparung durch Eco-Modus:**

$$E_{Eco} = E_{Normal} \times 0.85$$

$$\text{Einsparung} = E_{Normal} \times (1 - 0.85) = 0.15 \times E_{Normal}$$

**Zusatzverbrauch durch Sport-Modus:**

$$E_{Sport} = E_{Normal} \times 1.15$$

$$\text{Zusatz} = E_{Normal} \times (1.15 - 1) = 0.15 \times E_{Normal}$$

### 7.2 Reichweitenverbesserung durch Fahrstil

**Maximale Reichweite im Eco-Modus:**

$$R_{Eco} = \frac{E_{nutzbar}}{(V_{basis} \times 0.85 \times \text{andere Faktoren}) / 100}$$

**Reichweitenreduktion im Sport-Modus:**

$$R_{Sport} = \frac{E_{nutzbar}}{(V_{basis} \times 1.15 \times \text{andere Faktoren}) / 100}$$

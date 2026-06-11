# Semesterbegleitendes Projekt Elektrofahrzeug

## Beschreibung

In diesem File werden die Berechnungen für das Elektrofahrzeug ausgegeben.

## Ausgabe

Um das Programm auszuführen, geben Sie folgende Befehle ein:

```bash
g++ -o rechner rechner.cpp
./rechner
```

## Beispiel Ausgabe

```bash

===Elektrofahrzeug Energieberechnung=== 

--- EINGABEPARAMETER ---
Batteriekapazität: 90 kWh
Basisverbrauch: 18 kWh/100km

Streckensegmente:
Stadt: 20 km  und 40 km/h
Landstraße: 100 km und 80 km/h
Autobahn: 80 km und 120 km/h
GESAMT: 200 km

Temperatur: 5 °C
Regen: Ja
Wind: 20 km/h
Ladezustand: 100%

9. Fahrtzeiten
   Stadt:      t_stadt       = 0.5 h
   Landstraße: t_landstrasse = 1.25 h
   Autobahn:   t_autobahn    = 0.666667 h
   GESAMT:     t_gesamt      = 2.41667 h

1. Basisenergieverbrauch
   Gesamt:     E_basis          = 36 kWh
   Stadt:      E_basis_stadt    = 3.6 kWh
   Landstraße: E_basis_land     = 18 kWh
   Autobahn:   E_basis_autobahn = 14.4 kWh

2. Geschwindigkeitsfaktoren
   Stadt:      f_v_stadt       = 1.01
   Landstraße: f_v_landstrasse = 1.09
   Autobahn:   f_v_autobahn    = 1.49

3. Temperaturfaktor
   f_T = 1.45

4. Regenfaktor
   f_R = 1.05

5. Windfaktor
   f_W = 1.04

6. Höhenfaktoren
   Stadt:      f_H_stadt       = 1.01
   Landstraße: f_H_landstrasse = 1.05
   Autobahn:   f_H_autobahn    = 1.025

7. Streckentypfaktoren
   Stadt:      f_S_stadt       = 1.15
   Landstraße: f_S_landstrasse = 1
   Autobahn:   f_S_autobahn    = 0.95

8. Gesamtenergieverbrauch pro Segment
   Stadt:      E_stadt       = 6.68704 kWh
   Landstraße: E_landstrasse = 32.6196 kWh
   Autobahn:   E_autobahn    = 33.0816 kWh
   GESAMT:     E_gesamt      = 72.3883 kWh

9. Reichweitenberechnung
    Verfügbare Energie:    E_verfügbar = 90 kWh
    Puffer-Energie:        E_puffer    = 9 kWh
    Nutzbare Energie:      E_nutzbar   = 81 kWh
    Max. Reichweite:       R_max       = 450 km
    Realistische Reichweite: R_real    = 221.982 km

10. Machbarkeit und Empfehlungen
    Erforderliche Energie:      E_gesamt        = 72.3883 kWh
    Verbleibende Reserve:       E_reserve       = 8.61171 kWh
    Erforderlicher Ladezustand: SoC_erforderlich= 90.4314 %
    Energiedefizit (falls neg.): delta_E        = -8.61171 kWh

    Fahrt möglich:       JA
    Fahrt sicher möglich: NEIN

    Warnstufe: [GELB]   Fahrt möglich, aber Vorsicht.

```

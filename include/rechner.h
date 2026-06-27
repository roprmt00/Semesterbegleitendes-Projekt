#ifndef RECHNER_H
#define RECHNER_H

#include "include/readJson.h" 

//Struktur für die Ausgabe

struct BerechnungsErgebnis {
    double E_verfuegbar;         // Verfügbare Energie [kWh]          
    bool   fahrt_moeglich;       // Ob die Fahrt möglich ist          
 
    // Wenn Fahrt möglich, dann:
    double E_reserve;            // Verbleibende Reserve [kWh]
 
    // Wenn Fahrt nicht möglich, dann:
    double fehlende_Energie;     // Fehlende Energie [kWh]
    double SoC_erforderlich; 
        // Mindest-Ladezustand [%]
};

// Funktionsdeklaration

BerechnungsErgebnis berechneReichweite(
    const CarData&  fahrzeug,
    const RouteData&   strecke,
    const WeatherData&    wetter,
    const double SoC
);

#endif 
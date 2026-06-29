#ifndef RECHNER_H
#define RECHNER_H

#include "readJson.h" 

//Struktur für die Ausgabe
struct BerechnungsErgebnis {
    double E_verfuegbar;                 
    bool   fahrt_moeglich;               
 
    // Wenn Fahrt möglich
    double E_reserve;            
 
    // Wenn Fahrt nicht möglich
    double fehlende_Energie;     
    double SoC_erforderlich; 
};

// Funktionsdeklaration
BerechnungsErgebnis berechneReichweite(
    const CarData&  fahrzeug,
    const RouteData&   strecke,
    const WeatherData&    wetter,
    const double SoC
);

#endif 
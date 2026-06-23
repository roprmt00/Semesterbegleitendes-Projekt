#ifndef RECHNER_H
#define RECHNER_H

//Eingabe Structs

struct FahrzeugDaten {
    double Batteriekapazitaet;   // [kWh]
    double Basisverbrauch;       // [kWh/100km]
    double SoC;                  // State of Charge [%]
};
 
struct StreckeDaten {
    double D_stadt;
    double D_landstrasse;
    double D_autobahn;
 
    double v_stadt;
    double v_landstrasse;
    double v_autobahn;
 
    double H_auf_stadt;
    double H_ab_stadt;
    double H_auf_landstrasse;
    double H_ab_landstrasse;
    double H_auf_autobahn;
    double H_ab_autobahn;
};
 
struct WetterDaten {
    double Temperatur;           // [°C]
    bool   Regen;
    double Windgeschwindigkeit;  // [km/h]
};

//Ausgabe Structs

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
    const FahrzeugDaten&  fahrzeug,
    const StreckeDaten&   strecke,
    const WetterDaten&    wetter
);

#endif // RECHNER_H
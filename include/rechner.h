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


#endif // RECHNER_H
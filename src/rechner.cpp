#include "rechner.h" 
#include <cmath> 
using namespace std;

// Funktion zur Berechnung der Fahrzeugreichweite
BerechnungsErgebnis berechneReichweite( 
    const CarData&  fahrzeug,
    const RouteData&   strecke,
    const WeatherData&    wetter,
    const double SoC
    ) {

    // Basisenergieverbrauch

    const double E_basis_stadt    = (strecke.Distanz_Stadt       / 100.0) * fahrzeug.Durchschn_Verbrauch;
    const double E_basis_land     = (strecke.Distanz_Land / 100.0) * fahrzeug.Durchschn_Verbrauch;
    const double E_basis_autobahn = (strecke.Distanz_Autobahn    / 100.0) * fahrzeug.Durchschn_Verbrauch;

    // Geschwindigkeitsfaktoren
    
    const double f_v_stadt       = 1.0 + 0.01 * pow((strecke.Durchschnitt_Stadt       - 50.0), 2) / 100.0;
    const double f_v_landstrasse = 1.0 + 0.01 * pow((strecke.Durchschnitt_Land - 50.0), 2) / 100.0;
    const double f_v_autobahn    = 1.0 + 0.01 * pow((strecke.Durchschnitt_Autobahn    - 50.0), 2) / 100.0;

    // Temperaturfaktor
    double f_T;
    if      (wetter.Temp < 20.0)  f_T = 1.0 + 0.015 * (20.0 - wetter.Temp);
    else if (wetter.Temp <= 25.0) f_T = 1.0;
    else                                f_T = 1.0 + 0.01  * (wetter.Temp - 25.0);

    // Regen-Einflussfaktor
    const double f_R = wetter.Regen ? 1.05 : 1.0;

    // Windfaktor
    const double f_W = 1.0 + 0.01 * pow(wetter.Windgeschw, 2) / 100.0;

    // Höhenmeterfaktor
    const double D_gesamt       = strecke.Distanz_Stadt + strecke.Distanz_Land + strecke.Distanz_Autobahn;
    const double E_basis_gesamt = (D_gesamt / 100.0) * fahrzeug.Durchschn_Verbrauch;
    double f_H = 1.0;
    if (E_basis_gesamt > 0.0) { 
        f_H = 1.0 + (2000.0 * 9.81 * (strecke.Hoehenmeter_bergauf - 0.5 * strecke.Hoehenmeter_bergab)) / (0.90 * E_basis_gesamt * 3600000.0);
    }
    
    // Streckentypfaktor
    const double f_S_stadt       = 1.15;
    const double f_S_landstrasse = 1.0;
    const double f_S_autobahn    = 0.95;

    // Gesamtenergieverbrauch
    const double E_gesamt =
        (E_basis_stadt    * f_v_stadt       * f_H       * f_S_stadt) +
        (E_basis_land     * f_v_landstrasse * f_H * f_S_landstrasse) +
        (E_basis_autobahn * f_v_autobahn    * f_H    * f_S_autobahn);

    const double E_gesamt_final = E_gesamt * f_T * f_R * f_W;

    // Energiebetrachtung
    const double E_verfuegbar = (SoC / 100.0) * fahrzeug.Batteriekapazitaet;
    const double E_puffer     = 0.1 * fahrzeug.Batteriekapazitaet;
    const double E_nutzbar    = E_verfuegbar - E_puffer;

   // Ergebnis
    BerechnungsErgebnis ergebnis;
    ergebnis.E_verfuegbar     = E_verfuegbar;
    ergebnis.fahrt_moeglich   = (E_gesamt_final <= E_nutzbar);
    ergebnis.SoC_erforderlich = ((E_gesamt_final + E_puffer) / fahrzeug.Batteriekapazitaet) * 100.0;
 
    if (ergebnis.fahrt_moeglich) {
        ergebnis.E_reserve         = E_nutzbar - E_gesamt_final;
        ergebnis.fehlende_Energie  = 0.0;   

    } else {
        ergebnis.E_reserve         = 0.0;   
        ergebnis.fehlende_Energie  = E_gesamt_final - E_nutzbar;
    }

    return ergebnis;

}

    

    
 
    





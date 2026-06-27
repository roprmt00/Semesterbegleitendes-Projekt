// Berechnungen

//In diesem File werden die Berechnungen mithilfe den Formeln aus der Formel.md Datei durchgeführt und dargestellt.

#include "rechner.h" 
#include <cmath> 
using namespace std;


BerechnungsErgebnis berechneReichweite( 
    const CarData&  fahrzeug,
    const RouteData&   strecke,
    const WeatherData&    wetter,
    const double SoC
    ) {

    //1 Basisenergieverbrauch

    const double E_basis_stadt    = (strecke.Distanz_Stadt       / 100.0) * fahrzeug.Durchschn_Verbrauch;
    const double E_basis_land     = (strecke.Distanz_Land / 100.0) * fahrzeug.Durchschn_Verbrauch;
    const double E_basis_autobahn = (strecke.Distanz_Autobahn    / 100.0) * fahrzeug.Durchschn_Verbrauch;

    //2 Geschwindigkeitsfaktoren
    
    const double f_v_stadt       = 1.0 + 0.01 * pow((strecke.Durchschnitt_Stadt       - 50.0), 2) / 100.0;
    const double f_v_landstrasse = 1.0 + 0.01 * pow((strecke.Durchschnitt_Land - 50.0), 2) / 100.0;
    const double f_v_autobahn    = 1.0 + 0.01 * pow((strecke.Durchschnitt_Autobahn    - 50.0), 2) / 100.0;

    // 3. Temperaturfaktor
    // f_T: abhängig von Außentemperatur T in °C und wichtiger Einflussfaktor

    double f_T;
    if      (wetter.Temp < 20.0)  f_T = 1.0 + 0.03 * (20.0 - wetter.Temp);
    else if (wetter.Temp <= 25.0) f_T = 1.0;
    else                                f_T = 1.0 + 0.02 * (wetter.Temp - 25.0);

    //4. Regen-Einflussfaktor
    //F_R: 1.05 wenn Regen, sonst 1.0
    const double f_R = wetter.Regen ? 1.05 : 1.0;

    //5. Windfaktor
    //f_W = 1 + 0.01 * W^2 
    const double f_W = 1.0 + 0.01 * pow(wetter.Windgeschw, 2) / 100.0;

    //6. Höhenmeterfaktor
    //f_H,i = 1 + (H_auf,i - 0.5 * H_ab,i) * 10 / D_i
    
    const double f_H =
        1.0 + ((strecke.Hoehenmeter_bergauf       - 0.5 * strecke.Hoehenmeter_bergab)       / 1000.0);
    
    //7. Streckentypfaktor
    //Stadt=1.15 | Landstraße=1.0 | Autobahn=0.95
    const double f_S_stadt       = 1.15;
    const double f_S_landstrasse = 1.0;
    const double f_S_autobahn    = 0.95;

    //8. Gesamtenergieverbrauch
    //E_i = E_basis,i * f_v,i * f_T * f_R * f_W * f_H,i * f_S,i
    const double E_gesamt =
        (E_basis_stadt    * f_v_stadt       * f_H       * f_S_stadt)       +
        (E_basis_land     * f_v_landstrasse * f_H * f_S_landstrasse) +
        (E_basis_autobahn * f_v_autobahn    * f_H    * f_S_autobahn);
    // Gemeinsame Faktoren (T, R, W) gelten für alle Segmente
    // dahenm außen multiplizieren:

    const double E_gesamt_final = E_gesamt * f_T * f_R * f_W;

    //9. Energiebetrachtung
    const double E_verfuegbar = (SoC / 100.0) * fahrzeug.Batteriekapazitaet;
    const double E_puffer     = 0.1 * fahrzeug.Batteriekapazitaet;
    const double E_nutzbar    = E_verfuegbar - E_puffer;

   //10,Ergebnis:
    BerechnungsErgebnis ergebnis;
    ergebnis.E_verfuegbar   = E_verfuegbar;
    ergebnis.fahrt_moeglich = (E_gesamt_final <= E_nutzbar);
 
    if (ergebnis.fahrt_moeglich) {
        ergebnis.E_reserve         = E_nutzbar - E_gesamt_final;
        ergebnis.fehlende_Energie  = 0.0;   // nicht notig
        ergebnis.SoC_erforderlich  = 0.0;   // nicht nötig

    } else {
        ergebnis.E_reserve         = 0.0;   // nicht nötig
        ergebnis.fehlende_Energie  = E_gesamt_final - E_nutzbar;
        ergebnis.SoC_erforderlich  =
            ((E_gesamt_final + E_puffer) / fahrzeug.Batteriekapazitaet) * 100.0;
    }

    return ergebnis;

    }
    

    

    
 
    





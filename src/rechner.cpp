// Berechnungen

//In diesem File werden die Berechnungen mithilfe den Formeln aus der Formel.md Datei durchgeführt und dargestellt.

#include "rechner.h" 
#include <cmath> //Hier binde Ich die cmath Bibliothek ein, damit Ich die pow Funktion verwenden kann
using namespace std;


BerechnungsErgebnis berechneReichweite( 
    const FahrzeugDaten&  fahrzeug,
    const StreckeDaten&   strecke,
    const WetterDaten&    wetter){

    //1 Basisenergieverbrauch

    const double E_basis_stadt    = (strecke.D_stadt       / 100.0) * fahrzeug.Basisverbrauch;
    const double E_basis_land     = (strecke.D_landstrasse / 100.0) * fahrzeug.Basisverbrauch;
    const double E_basis_autobahn = (strecke.D_autobahn    / 100.0) * fahrzeug.Basisverbrauch;

    //2 Geschwindigkeitsfaktoren
    
    const double f_v_stadt       = 1.0 + 0.01 * pow((strecke.v_stadt       - 50.0), 2) / 100.0;
    const double f_v_landstrasse = 1.0 + 0.01 * pow((strecke.v_landstrasse - 50.0), 2) / 100.0;
    const double f_v_autobahn    = 1.0 + 0.01 * pow((strecke.v_autobahn    - 50.0), 2) / 100.0;

    // 3. Temperaturfaktor
    // f_T: abhängig von Außentemperatur T in °C und wichtiger Einflussfaktor

    double f_T;
    if      (wetter.Temperatur < 20.0)  f_T = 1.0 + 0.03 * (20.0 - wetter.Temperatur);
    else if (wetter.Temperatur <= 25.0) f_T = 1.0;
    else                                f_T = 1.0 + 0.02 * (wetter.Temperatur - 25.0);

    //4. Regen-Einflussfaktor
    //F_R: 1.05 wenn Regen, sonst 1.0
    const double f_R = wetter.Regen ? 1.05 : 1.0;

    //5. Windfaktor
    //f_W = 1 + 0.01 * W^2 
    const double f_W = 1.0 + 0.01 * pow(wetter.Windgeschwindigkeit, 2) / 100.0;

    //6. Höhenmeterfaktor
    //f_H,i = 1 + (H_auf,i - 0.5 * H_ab,i) * 10 / D_i
    
    const double f_H_stadt =
        1.0 + ((strecke.H_auf_stadt       - 0.5 * strecke.H_ab_stadt)       / 1000.0);
    const double f_H_landstrasse =
        1.0 + ((strecke.H_auf_landstrasse - 0.5 * strecke.H_ab_landstrasse) / 1000.0);
    const double f_H_autobahn =
        1.0 + ((strecke.H_auf_autobahn    - 0.5 * strecke.H_ab_autobahn)    / 1000.0);

    //7. Streckentypfaktor
    //Stadt=1.15 | Landstraße=1.0 | Autobahn=0.95
    const double f_S_stadt       = 1.15;
    const double f_S_landstrasse = 1.0;
    const double f_S_autobahn    = 0.95;

    //8. Gesamtenergieverbrauch
    //E_i = E_basis,i * f_v,i * f_T * f_R * f_W * f_H,i * f_S,i
    const double E_gesamt =
        (E_basis_stadt    * f_v_stadt       * f_H_stadt       * f_S_stadt)       +
        (E_basis_land     * f_v_landstrasse * f_H_landstrasse * f_S_landstrasse) +
        (E_basis_autobahn * f_v_autobahn    * f_H_autobahn    * f_S_autobahn);
    // Gemeinsame Faktoren (T, R, W) gelten für alle Segmente
    // dahenm außen multiplizieren:

    const double E_gesamt_final = E_gesamt * f_T * f_R * f_W;

    //9. Energiebetrachtung
    const double E_verfuegbar = (fahrzeug.SoC / 100.0) * fahrzeug.Batteriekapazitaet;
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
    

    

    
 
    





// Berechnungen

//In diesem File werden die Berechnungen mithilfe den Formeln aus der Formel.md Datei durchgeführt und dargestellt.

#include <iostream> //Hier binde Ich die Standardbibliotheken ein für Ein und Augabe
#include <cmath> //Hier binde Ich die cmath Bibliothek ein, damit Ich die pow Funktion verwenden kann
using namespace std;

int main (){

    cout << " ===Elektrofahrzeug Energieberechnung=== " << endl << endl;
     
     // ========== FAHRZEUGPARAMETER ==========
    double E_bat = 75.0;           // Batteriekapazität [kWh]
    double V_basis = 18.0;         // Basisverbrauch [kWh/100km]

    // ========== STRECKEPARAMETER - SEGMENTIERT ==========
    double D_stadt = 20.0;         // Stadt [km]
    double D_landstrasse = 100.0;  // Landstraße [km]
    double D_autobahn = 80.0;      // Autobahn [km]

    // ========== STRECKEPARAMETER ==========
    double D_gesamt = D_stadt + D_landstrasse + D_autobahn;    // Gesamtdistanz [km]

    // ======== Durchschnittsgeschwindigkeiten pro Segment ========
    double v_stadt = 40.0;         // Stadt [km/h]
    double v_landstrasse = 80.0;   // Landstraße [km/h]
    double v_autobahn = 120.0;     // Autobahn [km/h]

    // ======== Höhenmeter pro Segment ========
    double H_auf_stadt = 20.0;       // Höhenmeter auf Stadt [m]
    double H_ab_stadt = 20.0;        // Höhenmeter ab Stadt [m]
    double H_auf_landstrasse = 100.0; // Höhenmeter auf Landstraße [m]
    double H_ab_landstrasse = 100.0;  // Höhenmeter ab Landstraße [m]
    double H_auf_autobahn = 50.0;    // Höhenmeter auf Autobahn [m]
    double H_ab_autobahn = 50.0;     // Höhenmeter ab Autobahn [m]

    // ========== WETTERPARAMETER ==========
    double T = 5.0;                // Temperatur [°C]
    bool R = true;                 // Regen [true/false]
    double W = 20.0;               // Windgeschwindigkeit [km/h]

    // ========== LADEZUSTAND ==========
    double SoC = 80.0;             // State of Charge [%]


    // ======== Eingabeparameter ausgeben ========

    cout << "--- EINGABEPARAMETER ---" << endl;
    cout << "Batteriekapazität: " << E_bat << " kWh" << endl;
    cout << "Basisverbrauch: " << V_basis << " kWh/100km" << endl;
    cout << "\nStreckensegmente:" << endl;
    cout << "Stadt: " << D_stadt << " km  und " << v_stadt << " km/h" << endl;
    cout << "Landstraße: " << D_landstrasse << " km und " << v_landstrasse << " km/h" << endl;
    cout << "Autobahn: " << D_autobahn << " km und " << v_autobahn << " km/h" << endl;
    cout << "GESAMT: " << D_gesamt << " km" << endl;
    cout << "\nTemperatur: " << T << " °C" << endl;
    cout << "Regen: " << (R ? "Ja" : "Nein") << endl;
    cout << "Wind: " << W << " km/h" << endl;
    cout << "Ladezustand: " << SoC << "%" << endl << endl;

    // ========== Berechnungen==========

    //0 Fahrtzeiten
    //t_i = D_i / v_i

    double t_stadt       = D_stadt       / v_stadt;
    double t_landstrasse = D_landstrasse / v_landstrasse;
    double t_autobahn    = D_autobahn    / v_autobahn;
    double t_gesamt      = t_stadt + t_landstrasse + t_autobahn;
 
    cout << "9. Fahrtzeiten" << endl;
    cout << "   Stadt:      t_stadt       = " << t_stadt       << " h" << endl;
    cout << "   Landstraße: t_landstrasse = " << t_landstrasse << " h" << endl;
    cout << "   Autobahn:   t_autobahn    = " << t_autobahn    << " h" << endl;
    cout << "   GESAMT:     t_gesamt      = " << t_gesamt      << " h" << endl << endl;

    //1 Basisenergieverbrauch

    double E_basis = (D_gesamt / 100.0) * V_basis;
    double E_basis_stadt    = (D_stadt       / 100.0) * V_basis;
    double E_basis_land     = (D_landstrasse / 100.0) * V_basis;
    double E_basis_autobahn = (D_autobahn    / 100.0) * V_basis;
 
    cout << "1. Basisenergieverbrauch" << endl;
    cout << "   Gesamt:     E_basis          = " << E_basis          << " kWh" << endl;
    cout << "   Stadt:      E_basis_stadt    = " << E_basis_stadt    << " kWh" << endl;
    cout << "   Landstraße: E_basis_land     = " << E_basis_land     << " kWh" << endl;
    cout << "   Autobahn:   E_basis_autobahn = " << E_basis_autobahn << " kWh" << endl << endl;

    //2 Geschwindigkeitsfaktoren

    double f_v_stadt       = 1.0 + 0.01 * pow((v_stadt       - 50.0), 2) / 100.0;
    double f_v_landstrasse = 1.0 + 0.01 * pow((v_landstrasse - 50.0), 2) / 100.0;
    double f_v_autobahn    = 1.0 + 0.01 * pow((v_autobahn    - 50.0), 2) / 100.0;

    cout << "2. Geschwindigkeitsfaktoren" << endl;
    cout << "   Stadt:      f_v_stadt       = " << f_v_stadt       << endl;
    cout << "   Landstraße: f_v_landstrasse = " << f_v_landstrasse << endl;
    cout << "   Autobahn:   f_v_autobahn    = " << f_v_autobahn    << endl << endl;

    // 3. Temperaturfaktor
    // f_T: abhängig von Außentemperatur T in °C und wichtiger Einflussfaktor 

    double f_T;

    if (T < 20.0)
        f_T = 1.0 + 0.03 * (20.0 - T);
    else if (T <= 25.0)
        f_T = 1.0;
    else
        f_T = 1.0 + 0.02 * (T - 25.0);
 
    cout << "3. Temperaturfaktor" << endl;
    cout << "   f_T = " << f_T << endl << endl;

    //4. Regen-Einflussfaktor
    //F_R: 1.05 wenn Regen, sonst 1.0

    double f_R = R ? 1.05 : 1.0;
 
    cout << "4. Regenfaktor" << endl;
    cout << "   f_R = " << f_R << endl << endl;

    //5. Windfaktor
    //f_W = 1 + 0.001 * W^2 / 100

    double f_W = 1.0 + 0.001 * pow(W, 2) / 100.0;

    cout << "5. Windfaktor" << endl;
    cout << "   f_W = " << f_W << endl << endl;

    //6. Höhenmeterfaktor
    //f_H,i = 1 + (H_auf,i - 0.5 * H_ab,i) * 10 / D_i

    double f_H_stadt       = 1.0 + ((H_auf_stadt       - 0.5 * H_ab_stadt)       * 1.0) / (D_stadt*1000.0);
    double f_H_landstrasse = 1.0 + ((H_auf_landstrasse - 0.5 * H_ab_landstrasse) * 1.0) / (D_landstrasse*1000.0);
    double f_H_autobahn    = 1.0 + ((H_auf_autobahn    - 0.5 * H_ab_autobahn)    * 1.0) / (D_autobahn*1000.0);
 
    cout << "6. Höhenfaktoren" << endl;
    cout << "   Stadt:      f_H_stadt       = " << f_H_stadt       << endl;
    cout << "   Landstraße: f_H_landstrasse = " << f_H_landstrasse << endl;
    cout << "   Autobahn:   f_H_autobahn    = " << f_H_autobahn    << endl << endl;

    //7. Streckentypfaktor
    //Stadt=1.15 | Landstraße=1.0 | Autobahn=0.95

    double f_S_stadt       = 1.15;
    double f_S_landstrasse = 1.0;
    double f_S_autobahn    = 0.95;
 
    cout << "7. Streckentypfaktoren" << endl;
    cout << "   Stadt:      f_S_stadt       = " << f_S_stadt       << endl;
    cout << "   Landstraße: f_S_landstrasse = " << f_S_landstrasse << endl;
    cout << "   Autobahn:   f_S_autobahn    = " << f_S_autobahn    << endl << endl;

    //8. Gesamtenergieverbrauch
    //E_i = E_basis,i * f_v,i * f_T * f_R * f_W * f_H,i * f_S,i

    double E_stadt       = E_basis_stadt    * f_v_stadt       * f_T * f_R * f_W * f_H_stadt       * f_S_stadt;
    double E_landstrasse = E_basis_land     * f_v_landstrasse * f_T * f_R * f_W * f_H_landstrasse * f_S_landstrasse;
    double E_autobahn    = E_basis_autobahn * f_v_autobahn    * f_T * f_R * f_W * f_H_autobahn    * f_S_autobahn;
    double E_gesamt      = E_stadt + E_landstrasse + E_autobahn;
 
    cout << "8. Gesamtenergieverbrauch pro Segment" << endl;
    cout << "   Stadt:      E_stadt       = " << E_stadt       << " kWh" << endl;
    cout << "   Landstraße: E_landstrasse = " << E_landstrasse << " kWh" << endl;
    cout << "   Autobahn:   E_autobahn    = " << E_autobahn    << " kWh" << endl;
    cout << "   GESAMT:     E_gesamt      = " << E_gesamt      << " kWh" << endl << endl;

    // 9. Reichweitenberechnung

    // 9.1 Verfügbare Energie

    double E_verfügbar = (SoC / 100.0) * E_bat;

    // 9.2 Puffer-Energie / Reserve 
    double E_puffer = 0.1 * E_bat;
 
    // 9.3 Nutzbare Energie (5.3)
    double E_nutzbar = E_verfügbar - E_puffer;
 
    // 9.4 Theoretische maximale Reichweite 
    double R_max = E_nutzbar / (V_basis / 100.0);
 
    // Durchschnittliche Faktoren für realistische Reichweite
    double f_v_avg = (f_v_stadt * D_stadt + f_v_landstrasse * D_landstrasse + f_v_autobahn * D_autobahn) / D_gesamt;
    double f_H_avg = (f_H_stadt * D_stadt + f_H_landstrasse * D_landstrasse + f_H_autobahn * D_autobahn) / D_gesamt;
    double f_S_avg = (f_S_stadt * D_stadt + f_S_landstrasse * D_landstrasse + f_S_autobahn * D_autobahn) / D_gesamt;
 
    double R_real = E_nutzbar / ((V_basis * f_v_avg * f_T * f_R * f_W * f_H_avg * f_S_avg) / 100.0);
 
    cout << "9. Reichweitenberechnung" << endl;
    cout << "    Verfügbare Energie:    E_verfügbar = " << E_verfügbar << " kWh" << endl;
    cout << "    Puffer-Energie:        E_puffer    = " << E_puffer    << " kWh" << endl;
    cout << "    Nutzbare Energie:      E_nutzbar   = " << E_nutzbar   << " kWh" << endl;
    cout << "    Max. Reichweite:       R_max       = " << R_max       << " km"  << endl;
    cout << "    Realistische Reichweite: R_real    = " << R_real      << " km"  << endl << endl;

    // 10. MACHBARKEIT 

    double E_reserve          = E_nutzbar - E_gesamt;
    double delta_E            = E_gesamt - E_nutzbar;
    double SoC_erforderlich   = ((E_gesamt + E_puffer) / E_bat) * 100.0;
    double E_sicherheit       = 0.15 * E_nutzbar;
 
    bool fahrt_moeglich        = (E_gesamt <= E_nutzbar);
    bool fahrt_sicher          = (E_gesamt <= (E_nutzbar - E_sicherheit));
 
     cout << "11. Machbarkeit und Empfehlungen" << endl;
    cout << "    Erforderliche Energie:      E_gesamt        = " << E_gesamt        << " kWh" << endl;
    cout << "    Verbleibende Reserve:       E_reserve       = " << E_reserve       << " kWh" << endl;
    cout << "    Erforderlicher Ladezustand: SoC_erforderlich= " << SoC_erforderlich<< " %"   << endl;
    cout << "    Energiedefizit (falls neg.): delta_E        = " << delta_E         << " kWh" << endl << endl;
 
    cout << "    Fahrt möglich:       " << (fahrt_moeglich ? "JA"  : "NEIN") << endl;
    cout << "    Fahrt sicher möglich: " << (fahrt_sicher   ? "JA"  : "NEIN") << endl << endl;
 
    // Warnstufen 
    
    cout << "    Warnstufe: ";
    if (E_reserve < 0.0)
        cout << "[UNMOEGLICH] Fahrt nicht möglich - Energie reicht nicht aus." << endl;
    else if (E_reserve <= 0.05 * E_nutzbar)
        cout << "[ROT]    Fahrt nicht empfohlen - Reserve sehr gering." << endl;
    else if (E_reserve <= 0.2 * E_nutzbar)
        cout << "[GELB]   Fahrt möglich, aber Vorsicht." << endl;
    else
        cout << "[GRUEN]  Fahrt problemlos möglich." << endl;
 
    cout << endl;
 
    return 0;

}



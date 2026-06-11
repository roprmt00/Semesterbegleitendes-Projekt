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
    double D_stadt = 50.0;         // Stadt [km]
    double D_landstrasse = 100.0;  // Landstraße [km]
    double D_autobahn = 50.0;      // Autobahn [km]

    // ========== STRECKEPARAMETER ==========
    double D_gesamt = D_stadt + D_landstrasse + D_autobahn;    // Gesamtdistanz [km]

    // ======== Durchschnittsgeschwindigkeiten pro Segment ========
    double v_stadt = 40.0;         // Stadt [km/h]
    double v_landstrasse = 80.0;   // Landstraße [km/h]
    double v_autobahn = 120.0;     // Autobahn [km/h]

    // ======== Höhenmeter pro Segment ========
    double H_auf_stadt = 100.0;       // Höhenmeter auf Stadt [m]
    double H_ab_stadt = 100.0;        // Höhenmeter ab Stadt [m]
    double H_auf_landstrasse = 300.0; // Höhenmeter auf Landstraße [m]
    double H_ab_landstrasse = 300.0;  // Höhenmeter ab Landstraße [m]
    double H_auf_autobahn = 100.0;    // Höhenmeter auf Autobahn [m]
    double H_ab_autobahn = 100.0;     // Höhenmeter ab Autobahn [m]

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
    cout << "  Stadt: " << D_stadt << " km  und " << v_stadt << " km/h" << endl;
    cout << "  Landstraße: " << D_landstrasse << " km und" << v_landstrasse << " km/h" << endl;
    cout << "  Autobahn: " << D_autobahn << " km und " << v_autobahn << " km/h" << endl;
    cout << "  GESAMT: " << D_gesamt << " km" << endl;
    cout << "\nTemperatur: " << T << " °C" << endl;
    cout << "Regen: " << (R ? "Ja" : "Nein") << endl;
    cout << "Wind: " << W << " km/h" << endl;
    cout << "Ladezustand: " << SoC << "%" << endl << endl;

    // ========== Berechnungen==========

    //1 Basisenergieverbrauch

     double E_basis = (D_gesamt / 100.0) * V_basis;
     cout << "Basisenergieverbrauch allgemein: E_basis = " << E_basis << " kWh" << endl;


     //1.1 Basisenergieverbrauch Stadt

     double E_basis_stadt = (D_stadt / 100.0) * V_basis;
     cout << "Basisenergieverbrauch Stadt: E_basis_stadt = " << E_basis_stadt << " kWh" << endl;

    //1.2 Geschwindigkeitsfaktor Stadt

    double f_v_stadt = 1.0 + 0.01 * pow((v_stadt - 50.0), 2) / 100.0;
    cout << "Geschwindigkeitsfaktor Stadt: f_v_stadt = " << f_v_stadt << endl;

    //1.3 Höhenfaktor Stadt

    double f_H_stadt = 1.0 + ((H_auf_stadt - 0.5 * H_ab_stadt) * 10.0) / D_stadt;
    cout << " Höhenfaktor Stadt: f_H_stadt = " << f_H_stadt << endl;

    //5.4 Gesamtenergieverbrauch Stadt

    double E_stadt = E_basis_stadt * f_v_stadt * f_H_stadt;
    cout << "5.4 Gesamtenergieverbrauch Stadt: E_stadt = " << E_stadt << " kWh" << endl << endl;





}


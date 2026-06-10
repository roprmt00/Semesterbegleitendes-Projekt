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

    // ========== STRECKEPARAMETER ==========
    double D_gesamt = 200.0;       // Gesamtdistanz [km]
    double v_avg = 80.0;           // Durchschnittsgeschwindigkeit [km/h]
    double H_auf = 500.0;          // Höhenmeter bergauf [m]
    double H_ab = 500.0;           // Höhenmeter bergab [m]

    // ========== WETTERPARAMETER ==========
    double T = 5.0;                // Temperatur [°C]
    bool R = true;                 // Regen [true/false]
    double W = 20.0;               // Windgeschwindigkeit [km/h]

    // ========== LADEZUSTAND ==========
    double SoC = 80.0;             // State of Charge [%]


    // Die Eingabeparameter ausgeben

    cout << "=== EINGABEPARAMETER ===" << endl;
    cout << "Batteriekapazität: " << E_bat << " kWh" << endl;
    cout << "Basisverbrauch: " << V_basis << " kWh/100km" << endl;
    cout << "Distanz: " << D_gesamt << " km" << endl;
    cout << "Durchschnittsgeschwindigkeit: " << v_avg << " km/h" << endl;
    cout << "Höhenmeter auf/ab: " << H_auf << "m / " << H_ab << "m" << endl;
    cout << "Temperatur: " << T << " °C" << endl;
    cout << "Regen: " << (R ? "Ja" : "Nein") << endl;
    cout << "Wind: " << W << " km/h" << endl;
    cout << "Ladezustand: " << SoC << "%" << endl << endl;

    // ========== Berechnungen==========

    //1.1 Basisenergieverbrauch

     double E_basis = (D_gesamt / 100.0) * V_basis;
    cout << "=== BERECHNUNGEN ===" << endl;
    cout << "Basisenergieverbrauch: " << E_basis << " kWh" << endl; //Test 

}


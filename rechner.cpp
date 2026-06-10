// Berechnungen

//In diesem File werden die Berechnungen mithilfe den Formeln aus der Formel.md Datei durchgeführt und dargestellt.

#include <iostream> //Hier binde Ich die Standardbibliotheken ein für Ein und Augabe
#include <cmath> //Hier binde Ich die cmath Bibliothek ein, damit Ich die pow Funktion verwenden kann

int main (){

    std::cout << " ===Elektrofahrzeug Energieberechnung=== " << std::endl << std::endl;
     
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

}


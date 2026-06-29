#include "readJson.h" 
#include "rechner.h"
#include <iostream>
#include <filesystem> 
#include <sstream>

using string = std::string;

int main() {
    string Json_WeatherData;
    string Json_RouteData;
    string Json_CarData;
    string SoC_input;
    double SoC;
    bool valid_input = false;
    int w = 1;
    int r = 1;
    int c = 1;

    std::optional<WeatherData> weather;
    std::optional<RouteData> route;
    std::optional<CarData> car;
    std::optional<BerechnungsErgebnis> result;
    
    std::cout << "Starte das Programm zum Lesen der JSON-Daten..." << std::endl;

    // Abfrage der JSON-Datei für die Wetterdaten
    std::cout << "Bitte geben Sie den Namen der Datei fuer die Wetterdaten ein" << std::endl;
    while(w == 1) {
    std::cin >> Json_WeatherData;
    Json_WeatherData = "data/" + Json_WeatherData; 

    if (Json_WeatherData == "data/end") {
        std::cout << "Das Programm wird abgebrochen und beendet." << std::endl;
        return 0;
    }

    // Wetterdaten lesen
    std::cout << "\nVersuche Wetterdaten zu lesen..." << std::endl;

    weather = getWeatherData(Json_WeatherData);
    if (weather) { 
        std::cout << "Wetterdaten erfolgreich geladen:" << std::endl;
        std::cout << "  Temperatur: " << weather->Temp << " Grad Celsius" << std::endl;
        std::cout << "  Windgeschwindigkeit: " << weather->Windgeschw << " km/h" << std::endl;
        std::cout << "  Regen: " << (weather->Regen ? "Ja" : "Nein") << std::endl;
        std::cout << "  Gegenwind: " << (weather->Gegenwind ? "Ja" : "Nein") << std::endl;
        std::cout << "  Rückenwind: " << (weather->Rueckenwind ? "Ja" : "Nein") << std::endl;
        w = 0;
    } 
    else {
        std::cout << "Bitte geben Sie den Namen der Datei fuer die Wetterdaten erneut ein" << std::endl;
        w = 1;
    }
    }

    // Abfrage der JSON-Datei für die Streckenprofildaten
    std::cout << "Bitte geben Sie den Namen der Datei fuer das Streckenprofil ein" << std::endl;
    while(r == 1) {
    std::cin >> Json_RouteData; 
    Json_RouteData = "data/" + Json_RouteData;

    if (Json_RouteData == "data/end") {
        std::cout << "Das Programm wird abgebrochen und beendet." << std::endl;
        return 0;
    }

    // Streckenprofildaten lesen
    std::cout << "\nVersuche Streckenprofildaten zu lesen..." << std::endl;

    route = getRouteData(Json_RouteData);
    if (route) { 
        std::cout << "Streckenprofildaten erfolgreich geladen:" << std::endl;
        std::cout << "  Name: " << route->Name << std::endl;
        std::cout << "  Distanz: " << route->Distanz << " km" << std::endl;
        std::cout << "  Distanz Land: " << route->Distanz_Land << " km" << std::endl;
        std::cout << "  Distanz Stadt: " << route->Distanz_Stadt << " km" << std::endl;
        std::cout << "  Distanz Autobahn: " << route->Distanz_Autobahn << " km" << std::endl;
        std::cout << "  Durchschnitt Land: " << route->Durchschnitt_Land << " km" << std::endl;
        std::cout << "  Durchschnitt Stadt: " << route->Durchschnitt_Stadt << " km" << std::endl;
        std::cout << "  Durchschnitt Autobahn: " << route->Durchschnitt_Autobahn << " km" << std::endl;
        std::cout << "  Hoehenmeter bergauf: " << route->Hoehenmeter_bergauf << " km" << std::endl;
        std::cout << "  Hoehenmeter bergab: " << route->Hoehenmeter_bergab << " km" << std::endl;
        r = 0;

    } else {
        std::cerr << "Bitte geben Sie den Namen der Datei fuer das Streckenprofil erneut ein ." << std::endl;
        r = 1;
    }
    }

    // Abfrage der JSON-Datei für die Fahrzeugparameter
    std::cout << "Bitte geben Sie den Namen der Datei fuer die Fahrzeugparameter ein" << std::endl;
    while(c == 1) {
    std::cin >> Json_CarData; 
    Json_CarData = "data/" + Json_CarData;

    if (Json_CarData == "data/end") {
        std::cout << "Das Programm wird abgebrochen und beendet." << std::endl;
        return 0;
    }
    
    // Fahrzeugparameter lesen
    std::cout << "\nVersuche Fahrzeugparameter zu lesen..." << std::endl;

    car = getCarData(Json_CarData);
    if (car) { 
        std::cout << "Fahrzeugparameter erfolgreich geladen:" << std::endl;
        std::cout << "  Name: " << car->Name << std::endl;
        std::cout << "  Batteriekapazitaet: " << car->Batteriekapazitaet << " kWh" << std::endl;
        std::cout << "  Durchschnittlicher Verbrauch: " << car->Durchschn_Verbrauch << " kWh/100km" << std::endl;
        c = 0;
    } else {
        std::cerr << "Bitte geben Sie den Namen der Datei fuer die Fahrzeugparameter erneut ein" << std::endl;
        c = 1;
    }
    }

    // Abfrage des aktuellen Ladezustands
    while(!valid_input) {
    std::cout << "\nBitte geben Sie zuletzt den aktuellen Ladezustand (SoC) ihres Autos ein. Der Wert muss zwischen 0.0 und 100.0 liegen." << std::endl;
    std::cin >> SoC_input;

    if(SoC_input == "end") {
        std::cout << "Das Programm wird abgebrochen und beendet." << std::endl;
        return 0;
    }

    std::istringstream iss(SoC_input);
    if(iss >> SoC && iss.eof()) {
        if(SoC >= 0 && SoC <= 100) {
            std::cout << "\nDie Eingabe war erfolgreich!" << std::endl;
            valid_input = true;
        }
        else{
            std::cout << "\nBitte geben Sie nur Werte zwischen 0 und 100 ein." << std::endl;
        }
    }
    else{
        std::cout << "\nBitte geben Sie einen gueltigen float Wert ein." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    } 

    // Funktion zur Berechnung wird aufgerufen
    std::cout << "\nBerechnungen werden durchgefuehrt..." << std::endl;

    result = berechneReichweite(car.value(), route.value(), weather.value(), SoC);
    if (result) { 
        std::cout << "Reichweite erfolgreich berechnet:" << std::endl;
        std::cout << "  Verfuegbare Energie: " << result->E_verfuegbar << " kWh" << std::endl;
        if(result->fahrt_moeglich == true) {
            std::cout << "  Die Fahrt ist moeglich." << std::endl;
        }
        else{
            std::cout << "  Die Fahrt ist nicht moeglich." << std::endl;
        }
        std::cout << "  Verbleibende Reserve: " << result->E_reserve << " kWh" << std::endl;
        std::cout << "  Fehlende Energie: " << result->fehlende_Energie << " kWh" << std::endl;
        std::cout << "  Mindest-Ladezustand: " << result->SoC_erforderlich << " %" << std::endl;
    } else {
        std::cerr << "Fehler bei den Berechnungen." << std::endl;
    }

    std::cout << "\nProgramm beendet." << std::endl;
    return 0;
}
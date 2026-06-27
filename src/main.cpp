#include "include/readJson.h" 
#include "include/rechner.h"
#include <iostream>
#include <filesystem> // Für std::filesystem::path
#include <sstream>

using string = std::string;

int main() {
    string Json_WeatherData;
    string Json_RouteData;
    string Json_CarData;
    string SoC_input;
    double SoC;
    bool valid_input = false;

    std::optional<WeatherData> weather;
    std::optional<RouteData> route;
    std::optional<CarData> car;
    std::optional<BerechnungsErgebnis> result;
    
    std::cout << "Starte das Programm zum Lesen der JSON-Daten..." << std::endl;

    std::cout << "Bitte geben Sie den Namen der Datei fuer die Wetterdaten ein" << std::endl;
    std::cin >> Json_WeatherData; 

    // --- Wetterdaten lesen ---
    std::cout << "\nVersuche Wetterdaten zu lesen..." << std::endl;

    weather = getWeatherData(Json_WeatherData);
    if (weather) { // Annahme: Datei für Wetterdaten liegt im selben Verzeichnis wie die ausführbare Datei
        std::cout << "Wetterdaten erfolgreich geladen:" << std::endl;
        std::cout << "  Temperatur: " << weather->Temp << " Grad Celsius" << std::endl;
        std::cout << "  Windgeschwindigkeit: " << weather->Windgeschw << " km/h" << std::endl;
        std::cout << "  Regen: " << (weather->Regen ? "Ja" : "Nein") << std::endl;
        std::cout << "  Gegenwind: " << (weather->Gegenwind ? "Ja" : "Nein") << std::endl;
        std::cout << "  Rückenwind: " << (weather->Rueckenwind ? "Ja" : "Nein") << std::endl;
    } else {
        std::cerr << "Fehler beim Laden der Wetterdaten." << std::endl;
    }


    std::cout << "Bitte geben Sie den Namen der Datei fuer das Streckenprofil ein" << std::endl;
    std::cin >> Json_RouteData; 

    // --- Streckenprofildaten lesen ---
    std::cout << "\nVersuche Streckenprofildaten zu lesen..." << std::endl;

    route = getRouteData(Json_RouteData);
    if (route) { // Annahme: Datei für Streckenprofil liegt im selben Verzeichnis wie die ausführbare Datei
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

    } else {
        std::cerr << "Fehler beim Laden der Streckenprofildaten." << std::endl;
    }

    std::cout << "Bitte geben Sie den Namen der Datei fuer die Fahrzeugparameter ein" << std::endl;
    std::cin >> Json_CarData; 
    
    // --- Fahrzeugparameter lesen ---
    std::cout << "\nVersuche Fahrzeugparameter zu lesen..." << std::endl;

    car = getCarData(Json_CarData);
    if (car) { // Annahme: Datei für Fahrzeugparameter liegt im selben Verzeichnis wie die ausführbare Datei
        std::cout << "Fahrzeugparameter erfolgreich geladen:" << std::endl;
        std::cout << "  Name: " << car->Name << std::endl;
        std::cout << "  Batteriekapazitaet: " << car->Batteriekapazitaet << " kWh" << std::endl;
        std::cout << "  Durchschnittlicher Verbrauch: " << car->Durchschn_Verbrauch << " kWh/100km" << std::endl;
    } else {
        std::cerr << "Fehler beim Laden der Fahrzeugparameter." << std::endl;
    }

    while(!valid_input) {
    std::cout << "\nBitte geben Sie zuletzt den aktuellen Ladezustand (SoC) ihres Autos ein. Der Wert muss zwischen 0.0 und 100.0 liegen." << std::endl;
    std::cin >> SoC_input;
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
        std::cout << "\nBitte geben Sie einen gültigen gültigen float Wert ein." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    } 

    std::cout << "\nBerechnungen werden durchgeführt..." << std::endl;

    result = berechneReichweite(car.value(), route.value(), weather.value(), SoC);
    if (result) { // Annahme: Datei für Fahrzeugparameter liegt im selben Verzeichnis wie die ausführbare Datei
        std::cout << "Fahrzeugparameter erfolgreich geladen:" << std::endl;
        std::cout << "  Name: " << car->Name << std::endl;
        std::cout << "  Batteriekapazitaet: " << car->Batteriekapazitaet << " kWh" << std::endl;
        std::cout << "  Durchschnittlicher Verbrauch: " << car->Durchschn_Verbrauch << " kWh/100km" << std::endl;
    } else {
        std::cerr << "Fehler bei den Berechnungen." << std::endl;
    }

    std::cout << "\nProgramm beendet." << std::endl;
    return 0;
}
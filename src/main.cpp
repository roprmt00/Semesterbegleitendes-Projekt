#include "include/readJson.h" 
#include <iostream>
#include <filesystem> // Für std::filesystem::path

using string = std::string;

int main() {
    std::string Json_WeatherData;
    std::string Json_RouteData;
    std::string Json_CarData;
    
    std::cout << "Starte das Programm zum Lesen der JSON-Daten..." << std::endl;

    std::cout << "Bitte geben Sie den Namen der Datei fuer die Wetterdaten ein" << std::endl;
    std::cin >> Json_WeatherData; 

    // --- Wetterdaten lesen ---
    std::cout << "\nVersuche Wetterdaten zu lesen..." << std::endl;
    if (auto weather = getWeatherData(Json_WeatherData)) { // Annahme: Datei für Wetterdaten liegt im selben Verzeichnis wie die ausführbare Datei
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
    if (auto route = getRouteData(Json_RouteData)) { // Annahme: Datei für Streckenprofil liegt im selben Verzeichnis wie die ausführbare Datei
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
    if (auto car = getCarData(Json_CarData)) { // Annahme: Datei für Fahrzeugparameter liegt im selben Verzeichnis wie die ausführbare Datei
        std::cout << "Fahrzeugparameter erfolgreich geladen:" << std::endl;
        std::cout << "  Name: " << car->Name << std::endl;
        std::cout << "  Batteriekapazitaet: " << car->Batteriekapazitaet << " kWh" << std::endl;
        std::cout << "  Durchschnittlicher Verbrauch: " << car->Durchschn_Verbrauch << " kWh/100km" << std::endl;
    } else {
        std::cerr << "Fehler beim Laden der Fahrzeugparameter." << std::endl;
    }

    std::cout << "\nProgramm beendet." << std::endl;
    return 0;
}
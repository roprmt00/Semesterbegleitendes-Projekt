#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <optional>
#include "json.hpp"

using json = nlohmann::json;
using string = std::string;

struct WetterDaten
    {
      bool Regen;
      double Temp;
      double Windgeschw;
      bool Gegenwind; 
    };

struct Streckenprofil
    {
      string Name;
      double Distanz;
      double Distanz_Land;
      double Distanz_Stadt;
      double Distanz_Autobahn;
      double Durchschnitt_Land;
      double Durchschnitt_Stadt;
      double Durchschnitt_Autobahn;
      double Hoehenmeter_bergauf;
      double Hoehenmeter_bergab;
    };

    struct Fahrzeugparameter
    {
      string Name;
      double Batteriekapazitaet;
      double Durchschn_Verbrauch;   
    };
    

std::optional<WetterDaten> getWeatherData(const std::filesystem::path& filepath) {
    
    // Datei zum Lesen öffnen
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Error: File " << filepath
            << " could not be opened for reading\n";
        return std::nullopt;
    }

    // JSON aus Datei parsen
    json weatherData = json::parse(inFile);
    inFile.close();

    // Wetterdaten in Variablen schreiben
    
    WetterDaten Daten;
    Daten.Windgeschw = weatherData["Windgeschwindigkeit"].get<double>();
    Daten.Temp = weatherData["Temperatur"].get<double>();
    Daten.Regen = weatherData["Regen"].get<bool>();
    Daten.Gegenwind = weatherData["Gegenwind"].get<bool>();

    return Daten;
}

std::optional<Streckenprofil> getRouteData(const std::filesystem::path& filepath) {
    
    // Datei zum Lesen öffnen
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Error: File " << filepath
            << " could not be opened for reading\n";
        return std::nullopt;
    }

    // JSON aus Datei parsen
    json routeData = json::parse(inFile);
    inFile.close();

    // Wetterdaten in Variablen schreiben
    
    Streckenprofil Daten;
    Daten.Name = routeData["Name"].get<string>();
    Daten.Distanz = routeData["Distanz"].get<double>();
    Daten.Distanz_Land = routeData["Distanz Land"].get<double>();
    Daten.Distanz_Stadt = routeData["Distanz Stadt"].get<double>();
    Daten.Distanz_Autobahn = routeData["Distanz Autobahn"].get<double>();
    Daten.Durchschnitt_Land = routeData["Durchschnitt Land"].get<double>();
    Daten.Durchschnitt_Stadt = routeData["Durchschnitt Stadt"].get<double>();
    Daten.Durchschnitt_Autobahn = routeData["Durchschnitt Autobahn"].get<double>();
    Daten.Hoehenmeter_bergauf = routeData["Hoehenmeter bergauf"].get<double>();
    Daten.Hoehenmeter_bergab = routeData["Hoehenmeter bergab"].get<double>();

    return Daten;
}

std::optional<Fahrzeugparameter> getCarData(const std::filesystem::path& filepath) {
    
    // Datei zum Lesen öffnen
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Error: File " << filepath
            << " could not be opened for reading\n";
        return std::nullopt;
    }

    // JSON aus Datei parsen
    json carData = json::parse(inFile);
    inFile.close();

    // Wetterdaten in Variablen schreiben
    
    Fahrzeugparameter Daten;
    Daten.Name = carData["Name"].get<string>();
    Daten.Batteriekapazitaet = carData["Batteriekapazitaet (netto)"].get<double>();
    Daten.Durchschn_Verbrauch = carData["Durchschnittlicher Verbrauch"].get<double>();

    return Daten;
}

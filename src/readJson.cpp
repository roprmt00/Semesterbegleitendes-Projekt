#include "readJson.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <optional>
#include "json.hpp"

using json = nlohmann::json;
using string = std::string;
    

std::optional<WeatherData> getWeatherData(const std::filesystem::path& filepath) {
    
    // Datei zum Lesen öffnen
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Datei " << filepath
            << " konnte nicht zum Lesen geoeffnet werden\n";
        return std::nullopt;
    }

    // JSON aus Datei parsen
    json weatherData = json::parse(inFile);
    inFile.close();

    // Wetterdaten in Variablen schreiben
    
    WeatherData Daten;
    Daten.Windgeschw = weatherData["Windgeschwindigkeit"].get<double>();
    Daten.Temp = weatherData["Temperatur"].get<double>();
    Daten.Regen = weatherData["Regen"].get<bool>();
    Daten.Gegenwind = weatherData["Gegenwind"].get<bool>();
    Daten.Rueckenwind = weatherData["Rueckenwind"].get<bool>();


    return Daten;
}

std::optional<RouteData> getRouteData(const std::filesystem::path& filepath) {
    
    // Datei zum Lesen öffnen
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Datei " << filepath
            << " konnte nicht zum Lesen geoeffnet werden\n";
        return std::nullopt;
    }

    // JSON aus Datei parsen
    json routeData = json::parse(inFile);
    inFile.close();

    // Wetterdaten in Variablen schreiben
    
    RouteData Daten;
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

std::optional<CarData> getCarData(const std::filesystem::path& filepath) {
    
    // Datei zum Lesen öffnen
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Datei " << filepath
            << " konnte nicht zum Lesen geoeffnet werden\n";
        return std::nullopt;
    }

    // JSON aus Datei parsen
    json carData = json::parse(inFile);
    inFile.close();

    // Wetterdaten in Variablen schreiben
    
    CarData Daten;
    Daten.Name = carData["Name"].get<string>();
    Daten.Batteriekapazitaet = carData["Batteriekapazitaet (netto)"].get<double>();
    Daten.Durchschn_Verbrauch = carData["Durchschnittlicher Verbrauch"].get<double>();

    return Daten;
}

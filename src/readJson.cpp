#include "readJson.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <optional>
#include "json.hpp"

using json = nlohmann::json;
using string = std::string;
    
// Funktion zum Auslesen der Wetterdaten
std::optional<WeatherData> getWeatherData(const std::filesystem::path& filepath) {
    
    // Datei zum Lesen öffnen
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Datei " << filepath
            << " konnte nicht zum Lesen geoeffnet werden. Bitte ueberpruefen Sie, ob die Datei existiert und im data-Ordner gespeichert ist. Der Dateiname muss zwingend mit .json enden.\n";
        return std::nullopt;
    }

    // JSON aus Datei parsen
    json weatherData;
    try {
        weatherData = json::parse(inFile);
    } catch (const json::parse_error& e) {
        std::cerr << "Error: JSON-Parsing fehlgeschlagen fuer Datei " << filepath << ". Fehler: " << e.what() << '\n';
        inFile.close(); 
        return std::nullopt;
    }
    inFile.close();

    // Wetterdaten in Variablen schreiben
    WeatherData Daten;
    try {
        Daten.Windgeschw = weatherData.at("Windgeschwindigkeit").get<double>();
        Daten.Temp = weatherData.at("Temperatur").get<double>();
        Daten.Regen = weatherData.at("Regen").get<bool>();
        Daten.Gegenwind = weatherData.at("Gegenwind").get<bool>();
        Daten.Rueckenwind = weatherData.at("Rueckenwind").get<bool>();
    } catch (const json::out_of_range& e) {
        std::cerr << "Error: Ein erforderliches Wetterdatenfeld wurde in der Datei " << filepath << " nicht gefunden oder ist ungueltig. Fehler: " << e.what() << '\n';
        return std::nullopt;
    } catch (const json::type_error& e) {
        std::cerr << "Error: Unerwarteter Datentyp fuer ein Wetterdatenfeld in der Datei " << filepath << ". Fehler: " << e.what() << '\n';
        return std::nullopt;
    }


    return Daten;
}

// Funktion zum Auslesen des Streckenprofils
std::optional<RouteData> getRouteData(const std::filesystem::path& filepath) {
    
    // Datei zum Lesen öffnen
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Datei " << filepath
            << " konnte nicht zum Lesen geoeffnet werden. Bitte ueberpruefen Sie, ob die Datei existiert und im data-Ordner gespeichert ist. Der Dateiname muss zwingend mit .json enden.\n";
        return std::nullopt;
    }

     // JSON aus Datei parsen
    json routeData;
    try {
        routeData = json::parse(inFile);
    } catch (const json::parse_error& e) {
        std::cerr << "Error: JSON-Parsing fehlgeschlagen fuer Datei " << filepath << ". Fehler: " << e.what() << '\n';
        inFile.close(); 
        return std::nullopt;
    }
    inFile.close();

    // Wetterdaten in Variablen schreiben
    
    RouteData Daten;
    try{
    Daten.Name = routeData.at("Name").get<std::string>(); 
    Daten.Distanz = routeData.at("Distanz").get<double>();
    Daten.Distanz_Land = routeData.at("Distanz Land").get<double>();
    Daten.Distanz_Stadt = routeData.at("Distanz Stadt").get<double>();
    Daten.Distanz_Autobahn = routeData.at("Distanz Autobahn").get<double>();
    Daten.Durchschnitt_Land = routeData.at("Durchschnitt Land").get<double>();
    Daten.Durchschnitt_Stadt = routeData.at("Durchschnitt Stadt").get<double>();
    Daten.Durchschnitt_Autobahn = routeData.at("Durchschnitt Autobahn").get<double>();
    Daten.Hoehenmeter_bergauf = routeData.at("Hoehenmeter bergauf").get<double>();
    Daten.Hoehenmeter_bergab = routeData.at("Hoehenmeter bergab").get<double>();
    } catch (const json::out_of_range& e) {
        std::cerr << "Error: Ein erforderliches Streckenprofilfeld wurde in der Datei " << filepath << " nicht gefunden oder ist ungueltig. Fehler: " << e.what() << '\n';
        return std::nullopt;
    } catch (const json::type_error& e) {
        std::cerr << "Error: Unerwarteter Datentyp fuer ein Streckenprofilfeld in der Datei " << filepath << ". Fehler: " << e.what() << '\n';
        return std::nullopt;
    }

    return Daten;
}

// Funktion zum Auslesen der Fahrzeugparameter
std::optional<CarData> getCarData(const std::filesystem::path& filepath) {
    
    // Datei zum Lesen öffnen
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Datei " << filepath
            << " konnte nicht zum Lesen geoeffnet werden. Bitte ueberpruefen Sie, ob die Datei existiert und im data-Ordner gespeichert ist. Der Dateiname muss zwingend mit .json enden.\n";
        return std::nullopt;
    }

     // JSON aus Datei parsen
    json carData;
    try {
        carData = json::parse(inFile);
    } catch (const json::parse_error& e) {
        std::cerr << "Error: JSON-Parsing fehlgeschlagen fuer Datei " << filepath << ". Fehler: " << e.what() << '\n';
        inFile.close(); 
        return std::nullopt;
    }
    inFile.close();

    // Wetterdaten in Variablen schreiben
    CarData Daten;
    try{
    Daten.Name = carData.at("Name").get<string>();
    Daten.Batteriekapazitaet = carData.at("Batteriekapazitaet (netto)").get<double>();
    Daten.Durchschn_Verbrauch = carData.at("Durchschnittlicher Verbrauch").get<double>();
    } catch (const json::out_of_range& e) {
        std::cerr << "Error: Ein erforderliches Fahrzeugparameterfeld wurde in der Datei " << filepath << " nicht gefunden oder ist ungueltig. Fehler: " << e.what() << '\n';
        return std::nullopt;
    } catch (const json::type_error& e) {
        std::cerr << "Error: Unerwarteter Datentyp fuer ein Fahrzeugparameterfeld in der Datei " << filepath << ". Fehler: " << e.what() << '\n';
        return std::nullopt;
    }

    return Daten;
}

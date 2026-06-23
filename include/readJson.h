#ifndef JSON_READER_H
#define JSON_READER_H

#include <string>
#include <vector>
#include <optional>
#include <filesystem> 



struct WetterDaten {
    bool Regen;
    double Temp;
    double Windgeschw;
    bool Gegenwind;
    bool Rueckenwind;
};


struct Streckenprofil {
    std::string Name;
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


struct Fahrzeugparameter {
    std::string Name;
    double Batteriekapazitaet;
    double Durchschn_Verbrauch;
};


std::optional<WetterDaten> getWeatherData(const std::filesystem::path& filepath);
std::optional<Streckenprofil> getRouteData(const std::filesystem::path& filepath);
std::optional<Fahrzeugparameter> getCarData(const std::filesystem::path& filepath);

#endif 
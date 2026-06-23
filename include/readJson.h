#ifndef JSON_READER_H
#define JSON_READER_H

#include <string>
#include <vector>
#include <optional>
#include <filesystem> 



struct WeatherData {
    bool Regen;
    double Temp;
    double Windgeschw;
    bool Gegenwind;
    bool Rueckenwind;

    bool operator==(const WeatherData& other) const {
        return Regen == other.Regen &&
               Temp == other.Temp &&
               Windgeschw == other.Windgeschw &&
               Gegenwind == other.Gegenwind &&
               Rueckenwind == other.Rueckenwind;
    }
};


struct RouteData {
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

    bool operator==(const RouteData& other) const {
        return Name == other.Name &&
               Distanz == other.Distanz &&
               Distanz_Land == other.Distanz_Land &&
               Distanz_Stadt == other.Distanz_Stadt &&
               Distanz_Autobahn == other.Distanz_Autobahn &&
               Durchschnitt_Land == other.Durchschnitt_Land &&
               Durchschnitt_Stadt == other.Durchschnitt_Stadt &&
               Durchschnitt_Autobahn == other.Durchschnitt_Autobahn &&
               Hoehenmeter_bergauf == other.Hoehenmeter_bergauf &&
               Hoehenmeter_bergab == other.Hoehenmeter_bergab;
    }
};


struct CarData {
    std::string Name;
    double Batteriekapazitaet;
    double Durchschn_Verbrauch;

    bool operator==(const CarData& other) const {
        return Name == other.Name &&
               Batteriekapazitaet == other.Batteriekapazitaet &&
               Durchschn_Verbrauch == other.Durchschn_Verbrauch;
    }
};


std::optional<WeatherData> getWeatherData(const std::filesystem::path& filepath);
std::optional<RouteData> getRouteData(const std::filesystem::path& filepath);
std::optional<CarData> getCarData(const std::filesystem::path& filepath);

#endif 
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "include/readJson.h"


TEST_CASE("Äquivalenzklassen und Randwertanalysen für readJson-Funktion") {
    SECTION("Auslesen korrekter Werte") {
        
        WeatherData expectedWeatherData;
        expectedWeatherData.Regen = true;
        expectedWeatherData.Temp = 10.5;
        expectedWeatherData.Windgeschw = 20;
        expectedWeatherData.Gegenwind = true;
        expectedWeatherData.Rueckenwind = false;

        RouteData expectedRouteData;
        expectedRouteData.Name = "HS Esslingen - Frankfurt Flughafen";
        expectedRouteData.Distanz = 200;
        expectedRouteData.Distanz_Land = 20.7;
        expectedRouteData.Distanz_Stadt = 1.5;
        expectedRouteData.Distanz_Autobahn = 177.8;
        expectedRouteData.Durchschnitt_Land = 75;
        expectedRouteData.Durchschnitt_Stadt = 25;
        expectedRouteData.Durchschnitt_Autobahn = 125;
        expectedRouteData.Hoehenmeter_bergauf = 550;
        expectedRouteData.Hoehenmeter_bergab = 680;

        CarData expectedCarData;
        expectedCarData.Name = "Tesla Model 3 Long Range";
        expectedCarData.Batteriekapazitaet = 75;
        expectedCarData.Durchschn_Verbrauch = 14.7;

        REQUIRE(getWeatherData("Wetterdaten.json").has_value());
        REQUIRE(getWeatherData("Wetterdaten.json").value() == expectedWeatherData);

        REQUIRE(getRouteData("Streckenprofil.json").has_value());
        REQUIRE(getRouteData("Streckenprofil.json").value() == expectedRouteData);

        REQUIRE(getCarData("Fahrzeugparameter.json").has_value());
        REQUIRE(getCarData("Fahrzeugparameter.json").value() == expectedCarData);
    }
    SECTION("Auslesen korrekter Werte aus größeren Json-Dateien") {
        
        WeatherData expectedWeatherData;
        expectedWeatherData.Regen = true;
        expectedWeatherData.Temp = 10.5;
        expectedWeatherData.Windgeschw = 20;
        expectedWeatherData.Gegenwind = true;
        expectedWeatherData.Rueckenwind = false;

        RouteData expectedRouteData;
        expectedRouteData.Name = "HS Esslingen - Frankfurt Flughafen";
        expectedRouteData.Distanz = 200;
        expectedRouteData.Distanz_Land = 20.7;
        expectedRouteData.Distanz_Stadt = 1.5;
        expectedRouteData.Distanz_Autobahn = 177.8;
        expectedRouteData.Durchschnitt_Land = 75;
        expectedRouteData.Durchschnitt_Stadt = 25;
        expectedRouteData.Durchschnitt_Autobahn = 125;
        expectedRouteData.Hoehenmeter_bergauf = 550;
        expectedRouteData.Hoehenmeter_bergab = 680;

        CarData expectedCarData;
        expectedCarData.Name = "Tesla Model 3 Long Range";
        expectedCarData.Batteriekapazitaet = 75;
        expectedCarData.Durchschn_Verbrauch = 14.7;

        REQUIRE(getWeatherData("Wetterdaten_Zusatz.json").has_value());
        REQUIRE(getWeatherData("Wetterdaten_Zusatz.json").value() == expectedWeatherData);

        REQUIRE(getRouteData("Streckenprofil_Zusatz.json").has_value());
        REQUIRE(getRouteData("Streckenprofil_Zusatz.json").value() == expectedRouteData);

        REQUIRE(getCarData("Fahrzeugparameter_Zusatz.json").has_value());
        REQUIRE(getCarData("Fahrzeugparameter_Zusatz.json").value() == expectedCarData);
    }
    SECTION("Reaktion bei ungültigen Werten") {
        
        REQUIRE_FALSE(getWeatherData("Wetterdaten_fehlerhaft.json").has_value());
        REQUIRE_FALSE(getRouteData("Streckenprofil_fehlerhaft.json").has_value());
        REQUIRE_FALSE(getCarData("Fahrzeugparameter_fehlerhaft.json").has_value());
    }
}

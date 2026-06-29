#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "readJson.h"


TEST_CASE("Aequivalenzklassen und Randwertanalysen fuer readJson-Funktion") {

    // Test bei korrekten Werten 
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

        REQUIRE(getWeatherData("data/Wetterdaten_1.json").has_value());
        REQUIRE(getWeatherData("data/Wetterdaten_1.json").value() == expectedWeatherData);

        REQUIRE(getRouteData("data/Streckenprofil_1.json").has_value());
        REQUIRE(getRouteData("data/Streckenprofil_1.json").value() == expectedRouteData);

        REQUIRE(getCarData("data/Fahrzeugparameter_1.json").has_value());
        REQUIRE(getCarData("data/Fahrzeugparameter_1.json").value() == expectedCarData);
    }

    // Test bei zusätzlichen Werten
    SECTION("Auslesen korrekter Werte aus groeßeren Json-Dateien") {
        
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

        REQUIRE(getWeatherData("data/Wetterdaten_Zusatz.json").has_value());
        REQUIRE(getWeatherData("data/Wetterdaten_Zusatz.json").value() == expectedWeatherData);

        REQUIRE(getRouteData("data/Streckenprofil_Zusatz.json").has_value());
        REQUIRE(getRouteData("data/Streckenprofil_Zusatz.json").value() == expectedRouteData);

        REQUIRE(getCarData("data/Fahrzeugparameter_Zusatz.json").has_value());
        REQUIRE(getCarData("data/Fahrzeugparameter_Zusatz.json").value() == expectedCarData);
    }

    // Test bei fehlenden/ ungültigen Werten
    SECTION("Pruefen der Fehlermeldungen bei ungueltigen Werten") {
        
        std::stringstream ss;
        std::streambuf* oldCerr = std::cerr.rdbuf();

        // Testfall: Datei existiert nicht
        {            
            std::cerr.rdbuf(ss.rdbuf());
            getWeatherData("data/nicht_existierend.json");
            std::cerr.rdbuf(oldCerr);

            std::string errorMessage = ss.str();
            REQUIRE(errorMessage.find("Error: Datei \"data/nicht_existierend.json\" konnte nicht zum Lesen geoeffnet werden. Bitte ueberpruefen Sie, ob die Datei existiert und im data-Ordner gespeichert ist. Der Dateiname muss zwingend mit .json enden.\n") != std::string::npos);
            ss.str(""); ss.clear(); 
        }

        // Testfall: Leere JSON-Datei
        {
            std::cerr.rdbuf(ss.rdbuf()); 
            getWeatherData("data/leere_datei.json");
            std::cerr.rdbuf(oldCerr); 

            std::string errorMessage = ss.str();
            REQUIRE(errorMessage.find("Error: JSON-Parsing fehlgeschlagen fuer Datei \"data/leere_datei.json\".") != std::string::npos);
            ss.str(""); ss.clear();
        }

        // Testfall: Ungültige JSON-Syntax 
        {
            std::cerr.rdbuf(ss.rdbuf()); 
            getCarData("data/Fahrzeugparameter_ungültig.json");
            std::cerr.rdbuf(oldCerr); 

            std::string errorMessage = ss.str();
            REQUIRE(errorMessage.find("Error: JSON-Parsing fehlgeschlagen fuer Datei \"data/Fahrzeugparameter_ungültig.json\".") != std::string::npos);
            ss.str(""); ss.clear();
        }

        // Testfall: Fehlender Schlüssel 
        {
            std::cerr.rdbuf(ss.rdbuf()); 
            getRouteData("data/Streckenprofil_fehlender_schluessel.json");
            std::cerr.rdbuf(oldCerr); 

            std::string errorMessage = ss.str();
            REQUIRE(errorMessage.find("Error: Ein erforderliches Streckenprofilfeld wurde in der Datei \"data/Streckenprofil_fehlender_schluessel.json\" nicht gefunden oder ist ungueltig.") != std::string::npos);
            ss.str(""); ss.clear();
        }

        // Testfall: Falscher Datentyp 
        {
            std::cerr.rdbuf(ss.rdbuf()); 
            getCarData("data/Fahrzeugparameter_falscher_datentyp.json");
            std::cerr.rdbuf(oldCerr); 

            std::string errorMessage = ss.str();
            REQUIRE(errorMessage.find("Error: Unerwarteter Datentyp fuer ein Fahrzeugparameterfeld in der Datei \"data/Fahrzeugparameter_falscher_datentyp.json\".") != std::string::npos);
            ss.str(""); ss.clear();
        }
    }
}

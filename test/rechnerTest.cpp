#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "rechner.h"

// Meine Werte 

CarData standardFahrzeug() {
    CarData f;
    f.Batteriekapazitaet = 90.0;
    f.Durchschn_Verbrauch = 18.0;
    return f;
}
 
RouteData standardStrecke() {
    RouteData s;
    s.Distanz_Stadt        = 20.0;   s.Durchschnitt_Stadt        = 40.0;
    s.Distanz_Land         = 100.0;  s.Durchschnitt_Land         = 80.0;
    s.Distanz_Autobahn     = 80.0;   s.Durchschnitt_Autobahn     = 120.0;
    s.Hoehenmeter_bergauf  = 170.0;  s.Hoehenmeter_bergab        = 170.0;
    return s;
}
 
WeatherData standardWetter() {
    WeatherData w;
    w.Temp        = 22.0;   // Optimalbereich → f_T = 1.0
    w.Regen       = false;  // f_R = 1.0
    w.Windgeschw  = 0.0;    // f_W = 1.0
    return w;
}


// Testfall 1: Normalfall - Fahrt möglich

TEST_CASE("Normalfall: Fahrt ist möglich") {

    SECTION("Standardwerte: Fahrt soll möglich sein!!") {
        CarData     f = standardFahrzeug();
        RouteData   s = standardStrecke();
        WeatherData w = standardWetter();
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w, 100.0);
 
        REQUIRE(res.E_verfuegbar == Approx(90.0)); // SoC=100% → E_verfuegbar = 90 kWh
        REQUIRE(res.fahrt_moeglich == true);
        REQUIRE(res.E_reserve > 0.0);
    }
 
    SECTION("SoC = 100%, kurze Strecke, große Reserve erwartet") {
        CarData     f = standardFahrzeug();
        WeatherData w = standardWetter();
 
        RouteData s = standardStrecke();
        s.Distanz_Stadt      = 5.0;
        s.Distanz_Land       = 10.0;
        s.Distanz_Autobahn   = 10.0;
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w, 100.0);
 
        REQUIRE(res.fahrt_moeglich == true);
        REQUIRE(res.E_reserve > 50.0);
    }
 
    SECTION("Optimales Wetter: kein Regen, 22°C, kein Wind") {
        CarData     f = standardFahrzeug();
        RouteData   s = standardStrecke();
        WeatherData w = standardWetter();
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w, 100.0);
 
        REQUIRE(res.fahrt_moeglich == true);
        REQUIRE(res.E_verfuegbar == Approx(90.0));
    }
}

// Testfall 2 – Fahrt nicht möglich

TEST_CASE("Normalfall: Fahrt ist nicht möglich") {

    SECTION("Sehr niedriger SoC (5%): Fahrt soll scheitern") {
        CarData     f = standardFahrzeug();
        RouteData   s = standardStrecke();
        WeatherData w = standardWetter();
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w, 5.0);
 
        REQUIRE(res.E_verfuegbar == Approx(4.5)); // 5% von 90 kWh = 4.5 kWh
        REQUIRE(res.fahrt_moeglich == false);
        REQUIRE(res.fehlende_Energie > 0.0);
        REQUIRE(res.SoC_erforderlich > 5.0);
        REQUIRE(res.SoC_erforderlich <= 100.0);
    }
 
    SECTION("Sehr lange Strecke: Energie reicht nicht") {
        CarData     f = standardFahrzeug();
        WeatherData w = standardWetter();
 
        RouteData s = standardStrecke();
        s.Distanz_Stadt      = 100.0;
        s.Distanz_Land       = 300.0;
        s.Distanz_Autobahn   = 300.0;
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w, 100.0);
 
        REQUIRE(res.fahrt_moeglich == false);
        REQUIRE(res.fehlende_Energie > 0.0);
        REQUIRE(res.SoC_erforderlich > res.E_verfuegbar / f.Batteriekapazitaet * 100.0);
    }
}

// Testfall 3: Wetterbedingungen

TEST_CASE("Wettereinflüsse auf das Ergebnis") {
 
    SECTION("Regen erhöht den Verbrauch, Reserve sinkt") {
        CarData   f = standardFahrzeug();
        RouteData s = standardStrecke();
 
        WeatherData ohneRegen = standardWetter();
        WeatherData mitRegen  = standardWetter();
        mitRegen.Regen = true;
 
        BerechnungsErgebnis resOhne = berechneReichweite(f, s, ohneRegen, 100.0);
        BerechnungsErgebnis resMit  = berechneReichweite(f, s, mitRegen,  100.0);
 
        REQUIRE(resOhne.fahrt_moeglich == true);
        REQUIRE(resMit.fahrt_moeglich  == true);
        REQUIRE(resMit.E_reserve < resOhne.E_reserve);
    }
 
    SECTION("Kälte (T = -10°C) erhöht Verbrauch") {
        CarData   f = standardFahrzeug();
        RouteData s = standardStrecke();
 
        WeatherData optimal = standardWetter();
        WeatherData kalt    = standardWetter();
        kalt.Temp = -10.0;
 
        BerechnungsErgebnis resOptimal = berechneReichweite(f, s, optimal, 100.0);
        BerechnungsErgebnis resKalt    = berechneReichweite(f, s, kalt,    100.0);
 
        if (resKalt.fahrt_moeglich)
            REQUIRE(resKalt.E_reserve < resOptimal.E_reserve);
        else
            REQUIRE(resKalt.fahrt_moeglich == false);
    }
 
    SECTION("Starker Wind (100 km/h) erhöht Verbrauch") {
        CarData   f = standardFahrzeug();
        RouteData s = standardStrecke();
 
        WeatherData ohneWind = standardWetter();
        WeatherData mitWind  = standardWetter();
        mitWind.Windgeschw = 100.0;
 
        BerechnungsErgebnis resOhne = berechneReichweite(f, s, ohneWind, 100.0);
        BerechnungsErgebnis resMit  = berechneReichweite(f, s, mitWind,  100.0);
 
        if (resMit.fahrt_moeglich)
            REQUIRE(resMit.E_reserve < resOhne.E_reserve);
        else
            REQUIRE(resMit.fahrt_moeglich == false);
    }
}

// Testfall 4: Randwerte

TEST_CASE("Randwertanalyse") {
 
    SECTION("SoC = 0%: keine Energie verfügbar") {
        CarData     f = standardFahrzeug();
        RouteData   s = standardStrecke();
        WeatherData w = standardWetter();
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w, 0.0);
 
        REQUIRE(res.E_verfuegbar == Approx(0.0));
        REQUIRE(res.fahrt_moeglich == false);
        REQUIRE(res.fehlende_Energie > 0.0);
    }
 
    SECTION("SoC = 100%: maximale Energie verfügbar") {
        CarData     f = standardFahrzeug();
        RouteData   s = standardStrecke();
        WeatherData w = standardWetter();
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w, 100.0);
 
        REQUIRE(res.E_verfuegbar == Approx(90.0));
    }
 
    SECTION("Streckenlänge = 0 km: kein Verbrauch") {
        CarData     f = standardFahrzeug();
        WeatherData w = standardWetter();
 
        RouteData s = standardStrecke();
        s.Distanz_Stadt      = 0.0;
        s.Distanz_Land       = 0.0;
        s.Distanz_Autobahn   = 0.0;
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w, 100.0);
 
        REQUIRE(res.fahrt_moeglich == true);
        REQUIRE(res.E_reserve == Approx(81.0)); // 90 - 9 (Puffer) = 81 kWh
    }
 
    SECTION("Temperatur genau 20°C: Grenzwert Temperaturfaktor") {
        CarData   f = standardFahrzeug();
        RouteData s = standardStrecke();
 
        WeatherData w20 = standardWetter();
        w20.Temp = 20.0;

        WeatherData w25 = standardWetter();
        w25.Temp = 25.0;
 
        BerechnungsErgebnis res20 = berechneReichweite(f, s, w20, 100.0);
        BerechnungsErgebnis res25 = berechneReichweite(f, s, w25, 100.0);
 
        if (res20.fahrt_moeglich && res25.fahrt_moeglich)
            REQUIRE(res20.E_reserve == Approx(res25.E_reserve));
    }
 
}
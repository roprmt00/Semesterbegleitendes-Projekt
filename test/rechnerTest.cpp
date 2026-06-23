#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "rechner.h"

// Meine Werte 

FahrzeugDaten standardFahrzeug() {
    FahrzeugDaten f;   // ich benutze Kürzeln damit ich die Variablen nicht immer ausschreiben muss
    f.Batteriekapazitaet = 90.0;
    f.Basisverbrauch     = 18.0;
    f.SoC                = 100.0;
    return f;
}
 
StreckeDaten standardStrecke() {
    StreckeDaten s; // ich benutze Kürzeln damit ich die Variablen nicht immer ausschreiben muss
    s.D_stadt        = 20.0;   s.v_stadt        = 40.0;
    s.D_landstrasse  = 100.0;  s.v_landstrasse  = 80.0;
    s.D_autobahn     = 80.0;   s.v_autobahn     = 120.0;
    s.H_auf_stadt        = 20.0;  s.H_ab_stadt        = 20.0;
    s.H_auf_landstrasse  = 100.0; s.H_ab_landstrasse  = 100.0;
    s.H_auf_autobahn     = 50.0;  s.H_ab_autobahn     = 50.0;
    return s;
}
 
WetterDaten standardWetter() {
    WetterDaten w; // ich benutze Kürzeln damit ich die Variablen nicht immer ausschreiben muss
    w.Temperatur         = 22.0;   // Optimalbereich → f_T = 1.0
    w.Regen              = false;  // f_R = 1.0
    w.Windgeschwindigkeit = 0.0;   // f_W = 1.0
    return w;
}

// Im folgenden werden verschiedene Tesfälle vorgestellt, 
// die die funktionalität meiner rechner cpp Datei testen.

//--------------------------------------------------------

// Testfall 1: Normalfall - Fahrt möglich

TEST_CASE("Normalfall: Fahrt ist möglich") {

    SECTION("Standardwerte: Fahrt soll möglich sein") {
        FahrzeugDaten f = standardFahrzeug();
        StreckeDaten  s = standardStrecke();
        WetterDaten   w = standardWetter();
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w);
 
        
        REQUIRE(res.E_verfuegbar == Approx(90.0)); // Verfügbare Energie: SoC=100% → E_verfuegbar = 90 kWh
        REQUIRE(res.fahrt_moeglich == true); // Fahrt muss möglich sein
        REQUIRE(res.E_reserve > 0.0); // Reserve muss positiv sein
    }
 
    SECTION("SoC = 100%, kurze Strecke, große Reserve erwartet") {
        FahrzeugDaten f = standardFahrzeug();
        WetterDaten   w = standardWetter();
 
        StreckeDaten s = standardStrecke();
        s.D_stadt       = 5.0;
        s.D_landstrasse = 10.0;
        s.D_autobahn    = 10.0;
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w);
 
        REQUIRE(res.fahrt_moeglich == true);
        REQUIRE(res.E_reserve > 50.0);   // bei so kurzer Strecke muss viel Reserve bleiben
    }
 
    SECTION("Optimales Wetter: kein Regen, 22°C, kein Wind") {
        FahrzeugDaten f = standardFahrzeug();
        StreckeDaten  s = standardStrecke();
        WetterDaten   w = standardWetter();   // bereits optimal
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w);
 
        REQUIRE(res.fahrt_moeglich == true);
        REQUIRE(res.E_verfuegbar == Approx(90.0));
    }

}

// Testfall 2  Normalfall – Fahrt nicht möglich

TEST_CASE("Normalfall: Fahrt ist nicht möglich") {

    SECTION("Sehr niedriger SoC (5%):  Fahrt soll scheitern") {
        FahrzeugDaten f = standardFahrzeug();
        f.SoC = 5.0;
 
        StreckeDaten  s = standardStrecke();
        WetterDaten   w = standardWetter();
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w);
 
        
        REQUIRE(res.E_verfuegbar == Approx(4.5)); // Verfügbare Energie: 5% von 90 kWh = 4.5 kWh
        REQUIRE(res.fahrt_moeglich == false);
        REQUIRE(res.fehlende_Energie > 0.0);// Fehlende Energie muss positiv sein
        REQUIRE(res.SoC_erforderlich > 5.0); // Erforderlicher SoC muss über 5% liegen
        REQUIRE(res.SoC_erforderlich <= 100.0); // Erforderlicher SoC darf nicht über 100% liegen 
    }
 
    SECTION("Sehr lange Strecke: Energie reicht nicht") {
        FahrzeugDaten f = standardFahrzeug();
        WetterDaten   w = standardWetter();
 
        StreckeDaten s = standardStrecke();
        s.D_stadt       = 100.0;
        s.D_landstrasse = 300.0;
        s.D_autobahn    = 300.0;
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w);
 
        REQUIRE(res.fahrt_moeglich == false);
        REQUIRE(res.fehlende_Energie > 0.0);
        REQUIRE(res.SoC_erforderlich > res.E_verfuegbar / f.Batteriekapazitaet * 100.0);
    }
}

//Testfall 3 Wetterbeindungen

TEST_CASE("Wettereinflüsse auf das Ergebnis") {
 
    SECTION("Regen erhöht den Verbrauch, Reserve sinkt") {
        FahrzeugDaten f = standardFahrzeug();
        StreckeDaten  s = standardStrecke();
 
        WetterDaten ohneRegen = standardWetter();
        WetterDaten mitRegen  = standardWetter();
        mitRegen.Regen = true;
 
        BerechnungsErgebnis resOhne = berechneReichweite(f, s, ohneRegen);
        BerechnungsErgebnis resMit  = berechneReichweite(f, s, mitRegen);
 
        // Beide möglich, aber mit Regen weniger Reserve
        REQUIRE(resOhne.fahrt_moeglich == true);
        REQUIRE(resMit.fahrt_moeglich  == true);
        REQUIRE(resMit.E_reserve < resOhne.E_reserve);
    }
 
    SECTION("Kälte (T = -10°C) erhöht Verbrauch deutlich") {
        FahrzeugDaten f = standardFahrzeug();
        StreckeDaten  s = standardStrecke();
 
        WetterDaten optimal = standardWetter();
        WetterDaten kalt    = standardWetter();
        kalt.Temperatur = -10.0;
 
        BerechnungsErgebnis resOptimal = berechneReichweite(f, s, optimal);
        BerechnungsErgebnis resKalt    = berechneReichweite(f, s, kalt);
 
        // Bei Kälte muss Reserve kleiner sein (oder Fahrt gar nicht möglich)
        if (resKalt.fahrt_moeglich)
            REQUIRE(resKalt.E_reserve < resOptimal.E_reserve);
        else
            REQUIRE(resKalt.fahrt_moeglich == false);
    }
 
    SECTION("Starker Wind (100 km/h) erhöht Verbrauch") {
        FahrzeugDaten f = standardFahrzeug();
        StreckeDaten  s = standardStrecke();
 
        WetterDaten ohneWind = standardWetter();
        WetterDaten mitWind  = standardWetter();
        mitWind.Windgeschwindigkeit = 100.0;
 
        BerechnungsErgebnis resOhne = berechneReichweite(f, s, ohneWind);
        BerechnungsErgebnis resMit  = berechneReichweite(f, s, mitWind);
 
        if (resMit.fahrt_moeglich)
            REQUIRE(resMit.E_reserve < resOhne.E_reserve);
        else
            REQUIRE(resMit.fahrt_moeglich == false);
    }
}

//Testfall 4: Randwerte

TEST_CASE("Randwertanalyse") {
 
    SECTION("SoC = 0%: keine Energie verfügbar") {
        FahrzeugDaten f = standardFahrzeug();
        f.SoC = 0.0;
 
        StreckeDaten s = standardStrecke();
        WetterDaten  w = standardWetter();
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w);
 
        REQUIRE(res.E_verfuegbar == Approx(0.0));
        REQUIRE(res.fahrt_moeglich == false);
        REQUIRE(res.fehlende_Energie > 0.0);
    }
 
    SECTION("SoC = 100%: maximale Energie verfügbar") {
        FahrzeugDaten f = standardFahrzeug();
        f.SoC = 100.0;
 
        StreckeDaten s = standardStrecke();
        WetterDaten  w = standardWetter();
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w);
 
        REQUIRE(res.E_verfuegbar == Approx(90.0));
    }
 
    SECTION("Streckenlänge = 0 km:  kein Verbrauch") {
        FahrzeugDaten f = standardFahrzeug();
        WetterDaten   w = standardWetter();
 
        StreckeDaten s = standardStrecke();
        s.D_stadt       = 0.0;
        s.D_landstrasse = 0.0;
        s.D_autobahn    = 0.0;
 
        BerechnungsErgebnis res = berechneReichweite(f, s, w);
 
        REQUIRE(res.fahrt_moeglich == true);
        REQUIRE(res.E_reserve == Approx(81.0)); // Nutzbare Energie = 90 - 9 (Puffer) = 81 kWh, Verbrauch = 0
    }
 
    SECTION("Temperatur genau 20°C: Grenzwert Temperaturfaktor") {
        FahrzeugDaten f = standardFahrzeug();
        StreckeDaten  s = standardStrecke();
 
        WetterDaten w20 = standardWetter();
        w20.Temperatur = 20.0;   // f_T = 1.0  (Grenze unten)
 
        WetterDaten w25 = standardWetter();
        w25.Temperatur = 25.0;   // f_T = 1.0  (Grenze oben)
 
        BerechnungsErgebnis res20 = berechneReichweite(f, s, w20);
        BerechnungsErgebnis res25 = berechneReichweite(f, s, w25);
 
        // gleiches Ergebnis
        if (res20.fahrt_moeglich && res25.fahrt_moeglich)
            REQUIRE(res20.E_reserve == Approx(res25.E_reserve)); 
    }
 
    SECTION("SoC knapp ausreichend: Grenzfall fahrt_moeglich") {

        FahrzeugDaten f = standardFahrzeug();
        StreckeDaten  s = standardStrecke();
        WetterDaten   w = standardWetter();
 
        BerechnungsErgebnis resVoll = berechneReichweite(f, s, w);
        
        REQUIRE(resVoll.fahrt_moeglich == true); //teste mit 100% SoC, sollte möglich sein

        f.SoC = 10.0;// Mit sehr niedrigem SoC soll es scheitern
        BerechnungsErgebnis resKnapp = berechneReichweite(f, s, w);

        REQUIRE(resKnapp.fahrt_moeglich == false);
        REQUIRE(resKnapp.SoC_erforderlich > 10.0);
    }
}
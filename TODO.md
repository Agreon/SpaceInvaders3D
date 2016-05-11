#TODO


## Kollision
    + Kollision überprüfen
    -> Liegt an Y-Koordinate
    -> Wenn die gegner höher oder niedriger als 300 liegen, wird kollision nicht erkannt
    -> Also klappt es nur an der 0-Koordinate weil nur die 1. reihe recognized wird
    -> Sehr strange
        -> Kollisionsberechnung ist schon richtig.
            -> In der letzten Zeile wird auch richtig überprüft,
            -> Allerdings werden die Borders anders gedrawed als der rest
            -> Border mit y = 0 Hat ursprung oben im bildschirm
            -> Der rest in der mitte
    -> Liegt sehr wahrscheinlich daran das der Urpsrung der objekte in der Mitte dieser liegt -.-
## Enemy
    + dynamische Bewegung einbauen
        -> Fehler bei kollision
        -> MaximalVel
    +  Stufe nach unten setzen
        -> Tim


## Lichtklasse
    + Erbt von Entity
    + Extra-Direction->Vector
    + http://www.glprogramming.com/red/chapter05.html


## Allgemeine, statische Asset-Klasse
    + Lädt Sound und Texturen
        + Device closing läuft nicht so ganz
    + Texturen 
        + Laden
        + Anzeigen

## Animation-Klasse
   + Wenn Part -1 als frames bekommt,
   + Scary scale problem
    + Viel übdernken, wie die vererbung ist
   + Rotation klappt nur part-unabhängig 
      

## Player
    + Smoothe steuerung
        + Gebrauchte Komponenten
            + Velocity
            + MaxSpeed
            + incPerFrame
        -> Done
    + Neigung bei links/rechts
        -> Done
        
## Allgemeine Transformations-Klasse die Translate-Rotate-Scale zusammenfasst
    -> Done

## Entity
    + Part->Kollision wird falsch ausgeführt
    + Eigene Würfel-Funktion
        -> Done
    + Farben einstellbar
        + Wie?
    + Aus cfg. file loaden?

    
##Allgemein
+ Nochmal nachgucken wie man objekte richtig zerstört
+ Superklassen-Konstruktor funktioniert nicht.
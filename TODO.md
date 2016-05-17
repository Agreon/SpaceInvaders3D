#TODO

##Enemy-Wall Collision
    + Beides geht kaputt

## Sounds
    + Schuss-Sound

## Player
    + Tot
     
    
    
# Second Priority

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
      


## Entity
    + Wenn man Scale als Objektgröße nimmt, muss glScale selbst nochmal in glPush/PopMatrix mit drawBody() eingeschlossen sein
    + In unserem Anwendungsfall vlt. sinnvoll aber im allgemeinen gibt das .obj die größe eines Objektes vor
    + Farben einstellbar
        + Wie?
        
        
##Allgemein
+ Nochmal nachgucken wie man objekte richtig zerstört
+ Superklassen-Konstruktor funktioniert nicht.
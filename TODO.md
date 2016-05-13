#TODO

## Models
    + Player
    + Enemy

## Player
    + Schießen soll nur verzögert funktionieren
        -> Tim
    + Soll nicht aus Bildschirm raus
        -> Tim (Schau nach wie ich das bei den Gegnern gemacht habe ;) )
    + Rotation der Parts funktioniert nicht ganz
        -> Ich
        -> glPopMatrix wurde zu früh aufgerufen

## Enemy
    +  Stufe nach unten setzen
        -> Tim
        -> Schau nach wo die gegner die wand berühren
    + Balancing (Max. geschwindigkeit)
        -> Tim
    + Random schießen
        -> Tim?
        ->
        for every enemy
            if random % 10 (evaluieren)
                create laser at pos of enemy
                break;
        
## Animation
    + testen
     
## Sounds
    + Schuss-Sound
    
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
    + Farben einstellbar
        + Wie?
        
##Allgemein
+ Nochmal nachgucken wie man objekte richtig zerstört
+ Superklassen-Konstruktor funktioniert nicht.
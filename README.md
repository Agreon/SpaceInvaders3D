# SpaceInvaders3D

## Vorab

+ Überprüfen Sie ob die Audio-Bibliothek eingebunden ist!
+ Bitte stellen Sie den Ton an!

## Steuerung
#### Bewegung

+ Links: 'A'
+ Rechts: 'D'
+ Schuss: 'E'
+ Beenden: 'ESC'

## Funktionalität
+ Audio über AudioLibary (AL) eingebunden, Aufnahmen eigentständig durchgeführt.
+ GameOver Funktion --> Player hat 3 Leben, wird er 3 mal getroffen wird das Programm beendet.
+ Lichtquelle ist der Playerlaser, Abschusslicht (sieht man an den Barrikaden und am Cockpit aufleuchten).
+ Blöcke werden in weiter Entfernung zufällig platziert, um die Illusion eines Sternenhimmels zu erzeugen
+ Animation von Objekten
  + Das Spieler-Raumschiff neigt sich in die Flugrichtung.    
  + Die Kanone des Players rotiert beim Schuss.
  + Die Kanone der Gegner bewegen sich bei Abschuss druch den Rückschlag vor und zurück.

## Anhang
1. Objekt-Design
2. Szenegraph
3. Klassendiagramm

## Hinweise
+ Das Design wurde nicht zu 100% so umgesetzt wie bei dem Prototypen (siehe Anhang "Objekt-Design") geplant.
  + Barrikade: Leuchten nicht auf, weil wir ein Licht für das Projektil benutzen, es wird stattdessen der Destroy-Sound bei einem Treffer wiedergegeben.
+ Gegner
  + Haben keine sich bewegenden Arme, da die Kanone eine Bewegung besitzt und die Optik durch zu viel Bewegungen gestört wird.



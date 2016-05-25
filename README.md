# SpaceInvaders3D

## Vorab

+ Überprüfen Sie ob die Audio-Bibliothek eingebunden ist!
+ Bitte stellen Sie den Ton an!

## Steuerung
#### Bewegung

+ Rechts  --> Taste 'D'
+ Links --> Taste 'A'

#### Schuss

+ Taste 'E'

### Sonstiges

+ Beenden 'ESC'

## Zusatz
+ Audio über AudioLibary (AL) eingebunden, Aufnahmen eigentständig durchgeführt.
+ GameOver Funktion --> Player hat 3 Leben, wird er 3 mal getroffen wird das Programm beendet.
+ Lichtquelle ist der Playerlase, Abschusslicht (sieht man an den Barrikaden und am Cockpit aufleuchten).
+ Illusion eines Sternenhimmels (mehrere Wuerfel in der Entfernung).
+ Bewegung von Objekten: Die Kanone des Players rotiert, die Kanone der Gegner bewegen sich bei Abschuss hin und her.

## Anhang
1. Objekt-Design
2. Szenegraph
3. Klassendiagramm

## Hinweise
+ Design: Das Design wurde nicht zu 100% so umgesetzt wie bei dem Prototypen (siehe Anhang "Objekt-Design") geplant.
Barrikade: Leuchten nicht auf, weil wir ein Licht für das Projektil benutzen, es wird stattdessen der Destroy-Sound bei einem Treffer wiedergegeben.
Gegner: Haben keine sich bewegenden Arme, da die Kanone eine Bewegung besitzt und die Optik durch zu viel Bewegungen gestört wird.

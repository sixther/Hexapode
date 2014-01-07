# Le télémètre #

[Page d'accueil](../Rapport_Waquet-Dhalluin.html)

## Télémètre IR Sharp GP2D12 ##

\section Introduction

Le télémètre IR Sharp utilise les infrarouge pour déterminer la distance entre le robot et un objet. 

![telemetre2]

\section Description

Le capteur SHARP fonctionne en mesurant l'angle de réflexion d'une émission d'IR modulée, grâce à une rangée de récepteur.

![telemetre1] 

__Portée :__ La portée officielle est de 10 à 80cm.

__Directivité :__ La directivité est un cône de 5°.

__Précision :__ La précision du capteur dépend de la distance (simple conséquence trigonométrique).
Excellente à 10 cm, elle régresse de plus en plus jusqu'au 80cm.

__Fréquence :__ Le capteur en version analogique renvoit une mesure toutes les 40ms à peu près.


\section Documentation

La documentation constructeur du capteur est disponible [ici] (http://fribotte.free.fr/bdtech/distanceIR/gp2d12.pdf)





[telemetre1]: ..\img\telemetre1.png "Principe"
[telemetre2]: ..\img\telemetre2.jpg "Télémètre Sharp"
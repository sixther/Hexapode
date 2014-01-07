# Servo-moteurs #

[Page d'accueil](../Rapport_Waquet-Dhalluin.html)

\section Introduction 

Un _servomoteur_ (souvent abrégé en « servo », provenant du latin servus qui signifie « esclave ») est un moteur capable de maintenir une 
opposition à un effort statique et dont la position est vérifiée en continu et corrigée en fonction de la mesure. 
C'est donc un système asservi.

\section Fonctionnement 

Les servomoteurs sont commandés par l'intermédiaire d'un câble électrique à trois fils qui permettent d’alimenter le moteur et de 
lui transmettre des ordres de positions sous forme d’un signal codé en largeur d'impulsion plus communément appelés PWM ou RCO. 
Cela signifie que c'est la durée des impulsions qui détermine l'angle absolu de l'axe de sortie et donc la position du bras de commande 
du servomoteur. Le signal est répété périodiquement, en général toutes les 20 millisecondes, ce qui permet à l'électronique de contrôler 
et de corriger continuellement la position angulaire de l'axe de sortie, cette dernière étant mesurée par le potentiomètre.
Lorsque le moteur tourne, l'axe du servomoteur change de position, ce qui modifie la résistance du potentiomètre. Le rôle de l'électronique 
est de commander le moteur pour que la position de l'axe de sortie soit conforme à la consigne reçue : c'est un asservissement.

![servo1]

[servo1]: ..\img\servo1.png "Chronographe"


> Commande en largeur d'inpulsion avec  <B>T</B>  la durée du cycle complet (fixe) et  <B>t1</B>  la valeur commandée (variable) .
> <B>t1</B>/<B>T</B> = 25%
 
![servo2]

[servo2]: ..\img\servo2.png "Principe de fonctionnement"

> <B>t1</B> correspond au temps à l'état haut (Ton)
>
> <B>P</B> correspond à la période du signal périodique
 
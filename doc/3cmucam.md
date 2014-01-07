# La caméra #

[Page d'accueil](../Rapport_Waquet-Dhalluin.html)

## Carte de vision CMUCAM2 ##

\section Introduction

La carte CMUcam2 a été créés par l’institut de robotique de l’université Carnegie Mellon University.

Elle est composée d’un microcontrolleur SX52 créé, à l’origine, par la la société Ubicom et maintenu, 
pour les quelques pièces qu’il reste, par la société Parallax. Le CPU est interfacé d’un coté, avec une caméra CMOS OV7620 de chez Omnivision.
Il communique de l’autre coté avec l’hôte (type micro-contrôleur ou PC) au travers d’un port série RS-232 ou TTL (Les commandes disponibles 
sont détaillées dans la partie logiciel)

![cmucam1]



\section Fonctions

-	Suivi d’un bloc de couleur jusqu’à 50 images/seconde (la fréquence dépend de la résolution de l’image et de la taille de la fenêtre)
-	Suivi de mouvement en utilisant la différenciation image à 26 trames par seconde
-	Trouve le barycentre des données de suivi
-	Fournit des données de couleur et de variance
-	Fournit l’histogramme jusqu’à 28 bins pour chaque canal de couleur
-	Processus Horizontalement Edge images filtrées
-	Transfert en temps réel de pixels traqués dans une image
-	Possibilité de fenêtrage de l’image
-	Régler les propriétés de l’image
-	Dump une image brute (un ou plusieurs canaux)
-	Résolution max 176 x 255
-	Le port série supporte les vitesses : 
	+	115200 
	+	57600 
	+	38400 
	+	19200 
	+	9600 
	+	4800 
	+	2400 
	+	1200
-	5 sorties pour le contrôle de servomoteurs
-	Utilise automatiquement les servomoteurs de deux axes pour le suivi de la couleur
-	Sortie vidéo Noir et Blanc analogique (PAL ou NTSC)
-	Personnalisation de sortie de paquets
-	Mode basse consommation (Power down)
-	Traitement d’image multi-passe sur une image en mémoire.

\section Atouts

__Color Tracking :__  La CMUcam2 permet le pistage de couleurs. Un mode facultatif "bitmap line" transmet une image bitmap des pixels d’un suivi. 
Il y a aussi un "line mode" qui fournit des statistiques de pixels suivi pour chaque ligne, y compris les positions moyennes, minimum et 
maximum des pixels d’un suivi. Ceci est très utile pour le suivi en ligne. Il y a aussi un mode où l’interprétation des limites de suivi 
peut être inversée. Dans ce cas les pixels en dehors des limites de suivi sont considérés comme "bons". Ceci est utile pour suivre un objet 
sur un fond homogène. Il est également utile pour détecter les bords quand le mode différenciation de pixels (décrit ci-dessous) est activé. 
L’option de filtrage du bruit permet le réglage de la quantité de filtrage pour les situations bruyantes.

__Détection de mouvement :__ Les commandes de détection de mouvement (par différence d’image) permettent de capturer une version basse résolution 
de l’image courante et de la comparer en permanence les nouvelles images. La CMUcam 2 indique si une partie de l’image change plus que ce qui
a été spécifié. Ces paquets peuvent décrire le centre de gravité ou fournir une image bitmap des blocs d’images qui ont changé. Ce mode peut
aussi être combinée avec la différenciation de pixel (décrit ci-dessous) pour faire une détection de mouvement plus robuste aux changements 
d’illumination.

__Réduction des data à transmettre :__ En mode d’échantillonnage, le logiciel de CMUcam2 réduit la résolution de l’image de la caméra avant 
son traitement. L’avantage est qu’il y a beaucoup moins de pixels à traiter et à transmettre. Comme c’est fait par le logiciel, la réduction 
de la fréquence d’échantillonnage engendre seulement une très faible augmentation de la vitesse de traitement. Le principal avantage est de 
réduire la quantité de données transmises. Dans le cas d’un sous-échantillonnage dans une image fenêtrée, on peut facilement réduire la taille 
des données et donc de réduire le temps de transmission d’un facteur de 2 à 4 ou plus. De même, lorsque les modes en ligne bitmap sont 
utilisées, la taille de l’image bitmap peut être considérablement réduite, diminuant la quantité de données que le processeur doit recevoir 
et traiter.

__Power Saving :__ Entièrement nouveau dans le CMUcam2 sont les modes d’économie d’énergie. Dans certaines applications, la CMUcam2 n’est pas 
nécessaire pour traiter en permanence les données d’image. Dans ces cas, elle peut être commandé pour baisser sa consommation. Aucune commande 
de suivi ou d’asservissement qui se passera lorsque la CMUcam2 est dans un de ces modes. L’envoi d’une commande simple par la liaison série 
réveille la caméra en quelques millisecondes.

\section Manuel

Le manuel d'utilisation est disponible sur le site _www.cs.cmu.edu_.
Vous pouvez le consulter [ici](http://www.cs.cmu.edu/~cmucam2/CMUcam2_manual.pdf)

[cmucam1]: ..\img\cmucam1.jpg "CMUCAM2"
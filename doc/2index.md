Mini-projet 								{#mainpage}
========================================================
[Page d'accueil](../Rapport_Waquet-Dhalluin.html)
## Description ## 
### Firmware de contrôle d'un robot hexapode ###
<p>
La société _Insset Robotics_ souhaite commercialiser un kit robotique hexapode destiné au grand public. Le kit sera vendu en 2 versions :
</p>
- _basic kit_ : mécanique et éléctronique uniquement
- _advanced kit_ : comprenant en plus un firmware de contrôle préprogrammé

![hexapode]

En tant que concepteur logiciel embarqué la société _Insset Robotics_, vous êtes en charge du développement du firmware de la version _advanced kit_
, en binôme.

Fonctionnalités requises :

- contrôle des 20 servo-moteurs
- lecture des 6 TOR au niveau des pieds
- lecture du télémètre IR Sharp GP2D12 de la tête chercheuse
- récupération des informations de vision de la tête chercheuse
<p>
N'étant pas spécialisé en vision, la société _Insset Robotics_ s'appuie sur une solution déjà existante pour sa tête chercheuse : la CMUCAM2.

Le mode de contrôle envisagé est une communication de type protocole série over liaison sans fil de type Zigbee.

Une liaison CAN est disponible et permet le dialogue vers des cartes et capteurs/actionneurs d'extension. (option)
</p>
### Cadre de développement ###

En tant que concepteur logiciel embarqué de cette socité, vous êtes en charge de la concepton et du développement de ce firmware, en binôme.

Le responsable marketing souhaite que le firmware offre les fonctionnalités suivantes: 

- pilotage des servo-moteurs à partir d'un terminal série standard
- affichage des informations de contact des pieds (TOR)
- affichage des informations de la tête chercheuse ( télemètre + CMUCAM2 )

Les options qui pourraient être supportée sur ce robot :

- IHM graphique de pilotage/affichage 
- implémentation interne d'algorithmes de marches 
- implémentation interne d'un algorithme de suivi d'objet

Le responsable de l'équipe de développement impose également certaines contraintes :

- utilisation de FreeRTOS sur une cible lcp17xx
- utilisation de l'IDE Keil
- utilisation de git en tant que gestionnaire de version avec 2 exigences :
	+ granularité de commits importante
	+ commits renseignés
- documentation du code suivant avec une syntaxe compatible _Doxygen_
- fourniture d'un firmware fonctionnel

### Travail demandé ###
<p>
Le mini-projet a pour objectif la mise en oeuvre de FreeRTOS étudié en cours. Dans ce cadre, vous vous positionnez comme concepteurs logiciels
afin de répondre au besoin du client, conformément aux contraintes exprimées dans ce document. Il vous faut donc, dans un premier temps rédiger
un cahier des charges (en prenant des hypothèses sur les éléments matériels non spécifiés), faire ensuite les choix de conception, modéliser et
créer un prototype et le valider. Pour la mise au point et la validation, des simulateurs des cartes périphériques pourront être développés. 
Vous soutiendrez enfin votre projet dans une revue de réalisation, lors de la dernière scéance.
</p>
### Evaluation ###
<p>
L'évaluation portera autant sur la couverture du cahier des charges que sur la pertinance des solutions techniques choisies. Elle prendra aussi
en compte l'organisation du travail, et la qualité des documents associés produits.
</p>
[hexapode]: ..\img\hexapode.jpg "Hexapode"
[list]: ..\img\list.png 

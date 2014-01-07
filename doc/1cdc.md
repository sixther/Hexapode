# Rapport - Manuel d'utilisation #
[Page d'accueil](../Rapport_Waquet-Dhalluin.html)
\section Sommaire

<A HREF="#Concept">Conception</A><BR>
- <A HREF="#Intro">1. Introduction</A><BR>
- <A HREF="#Architecture">2. Architecture du projet</A><BR>
- <A HREF="#GestFeet">3. La gestion des pattes</A><BR>
- <A HREF="#GestHead">4. La gestion de la tête</A><BR>
- <A HREF="#Capteur">5. Les capteurs</A><BR>
- <A HREF="#Ordo">6. L'ordonnancement</A><BR>
- <A HREF="#Comm">7. La communication</A><BR>
- <A HREF="#IHM">8. L'Interface Homme-Machine</A><BR>

<A HREF="#Doc">Documentation</A><BR>

<HR>
\section Développement
<A NAME="Concept"></A>
\subsection Conception

### <A NAME="Intro">1. Introduction</A> ### 

<p>
Pour réaliser ce mini-projet, l'équipe de concepteur a tout d'abord analyser la demande du client, c'est à dire de concevoir un 
robot à __six pattes__ pouvant être __autonome__ et aussi diriger par un opérateur via une liaison sans fil, __Zigbee__ (demande du client). 
De plus, ce robot sera muni d'une carte NXP pouvant accueillir un système temps réel, __FreeRTOS__ (demande du client). 
Ce robot sera équipé aussi d'une caméra __CMUCAM2__ (demande du client) qui aura pour rôle de guider le robot pour "tracker" une couleur.
</p>

<p>
Chaque patte est équipée de trois servo-moteurs permettant de réaliser les mouvements nécessaires pour faire marcher le robot. Un télémètre
sera installé sur le devant du robot. Il aura pour but de faire éviter un obstacle au robot lorsqu'il sera en train de se déplacer.
</p>

<p>
Nous avons établi un ordre dans la conception du programme :
1. Création d'une PWM
2. Création de toute les PWM
3. Création d'un module pour l'UART
4. Gestion des PWM via l'UART (création de protocoles)
5. Mise en place des capteurs TOR
6. Utilisation et mise en place du télémètre
7. Mise en place de la CMUCAM2 (choix des modes, mise en place du protocole de la caméra)
8. Création d'une IHM permettant de visualiser la flux vidéo et la gestion du robot.
9. Mise en place d'algorithmes de marches
10. Mise en place d'un suivi d'objet
</p>

### <A NAME="Architecture">2. Architecture du projet</A> ###

 <p>
 Dans une idée de développer du bas vers le haut, nous avons donc utilisé plusieurs structures afin d'organiser notre code. Chaque
 éléments du robot est représenté par une structure. Nous nous sommes inspirés des développements réalisés en langage objet. De 
 cette manière, il est plus facile de ce repérer. De plus, chaque éléments (telementre,cmucam, servo-moteurs, ...) "possède" un
 fichier .c et un fichier .h où sont déclarés les structures. Voici un schéma qui permet de représenter le système :
 </p>
 
 ![archi]
 
 [archi]:..\img\archi.png "Architecture du projet"
 
<p>
Ensuite, l'équipe d'_Insset Robotics_ chargée de la conception logicielle de ce projet est parti dans le principe de découper
le robot en deux grandes parties:
</p>

-	La tête
	+	La caméra CMUCAM2
	+	Le télémètre 
	+	Le servo-moteur Axe X
	+	Le servo-moteur Axe Y
-	Les pattes
	+	Patte Avant Gauche (Feet Left Font)
	+	Patte Avant Droite (Feet Right Font)
	+	Patte Milieu Gauche (Feet Left Middle)
	+	Patte Milieu Droite (Feet Right Middle)
	+	Patte Arrière Gauche (Feet Left Back)
	+	Patte Arrière Droite (Feet Right Back)

Dont chaque patte est inspirée sur ce modèle suivant : 

-	Patte X
	+	Le servo-moteur	Axe X
	+	Le servo-moteur Axe Y
	+	Le servo-moteur Axe Z
	+	Le capteur Tout-Ou-Rien


### <A NAME="GestFeet">3. La gestion des pattes</A> ###

#### 3.1 La reflexion ####

<p>
L'équipe d'_Insset Robotics_ a décidé d'utiliser deux timers hardware pour gérer les 20 __PWM__ (Pulse Width Modulation) des 20 servo-
moteurs, dont 2 sont intégrés dans la tête du robot permettant de faire pivoter la tête chercheuse sur deux axes différents. Un Timer
sera utilisé pour gérer les toutes les PWM dans la même période de timer, donc dans une période de 20ms. L'autre timer permet quant à 
lui de mettre la sortie à l'état haut le temps voulu ( _t_ compris entre 1 et 2ms - _cf. Onglet Servo-moteurs_).
</p>

#### 3.2 Le protocole #### 

<p>
Dans le cahier des charges, il est stipulé que les pattes doivent être diriger dans un premier temps manuellement par l'intermédiaire
d'une liaison série entre un ordinateur et le robot. Pour ce faire, l'équipe d'_Insset Robotics_ a conçu un protocole de communication
permettant de changer la valeur de l'angle des servo-moteurs via une commande dans un terminal. Voici un exemple de trame pouvant être
envoyer au robot via le terminal. 
</p>

~~~~~~~~~~~~~~~~~~~~~~
$F,L,F,1,18\n
~~~~~~~~~~~~~~~~~~~~~~

> <B>$</B> correspond au début de la trame
>
> <B>L</B> correspond au coté du robot. Peut prendre comme valeur <B>L</B> pour _Left_ ou <B>R</B> pour _Right_
>
> <B>F</B> correspond à la position de la patte. Peut prendre comme valeur <B>F</B> pour _Font_ ou <B>M</B> pour _Middle_ ou  <B>B</B> pour _Back_
>
> <B>1</B> correspond au numéro du servo-moteur de la patte. Peut prendre comme valeur <B>1</B>,<B>2</B> ou <B>3</B>
>
> <B>18</B> correspond à l'angle en degrès. Peut prendre comme valeur un chiffre compris en chiffre compris entre 0 et 180. (* _uniquement des multiples de 9_)

<B>* Informations :</B> Nous avons décidé que le pas en degrés serait 9° par soucis de compatibilité avec notre configuration (seulement 2 timers utilisés)

~~~~~~~~~~~~~~~~~~~~~~
$TOR,L,F,5\n
~~~~~~~~~~~~~~~~~~~~~~ 

> <B>$</B> correspond au début de la trame
>
> <B>TOR</B> correspond aux trames des capteurs TOR
>
> <B>L</B> correspond au coté du robot. Les valeurs comprises sont L ou R pour _Left_ ou _Right_
>
> <B>F</B> correspond à l'emplacement de la pate. Les valeurs comprises sont F, M ou B pour _Font_, _Middle_ ou _Back_
>
> <B>5</B> correspond à la valeur du Time Out en seconde.

#### 3.3 Programmation ####

<p>
Comme nous l'avons expliqué ci-dessus, chaque élément est représenté par une structure de données. Les 6 pattes qui composent 
le robot sont représentées par cette structure :

~~~~~~~~~~~~~~~{.c}
typedef struct
{
	ServoMoteur xServo1;
	ServoMoteur xServo2;
	ServoMoteur xServo3;
	Tor xTor1;
	
}FeetHexapode;
~~~~~~~~~~~~~~~

Dans cette structure une patte est représentée par 3 servo-moteurs, ici avec la structure _ServoMoteur_. De plus, chaque patte 
est composée d'un capteur Tout-Ou-Rien permettant de savoir si la patte est en liaison avec le sol, d'où la variable de type Tor
qui est une structure représentant un capteur TOR. Voici, les deux structures évoquées ci-dessus : 
</p>

~~~~~~~~~~~~~~~{.c}
typedef struct
{
	unsigned char ucTorValue;
	unsigned char ucTorNum;
	
}Tor;
~~~~~~~~~~~~~~~

> <B>ucTorValue</B> correspond à la valeur du capteur (1 ou 0)
>
> <B>ucTorNum</B> correspond au masque du capteur (0x02, 0x04, 0x08, 0x10, 0x20)

~~~~~~~~~~~~~~~{.c}
typedef struct
{
	unsigned int ucAngle;
	unsigned int ucCount;
	unsigned char ucPwmNum;
	
}ServoMoteur;
~~~~~~~~~~~~~~~

> <B>ucAngle</B> correspond à la valeur de l'angle du servo-moteur
>
> <B>ucCount</B> correspond au compteur de pas
>
> <B>ucPwmNum</B> correspond au numéro de la PWM qui correspond au un servo-moteur (de 0 à 19)

### <A NAME="GestHead">4. La gestion de la tête</A> ###

#### 4.1 Réflexion ####

<p>
Dans le même esprit que pour les pattes, nous avons décidé de représenter la tête du robot sous forme d'une structure. La tête 
du robot est composé deux servo-moteurs permettant de la faire pivoter et bouger de droite à gauche et de haut en bas. Ensuite,
nous avons décidé d'intégrer dans la structure le télémètre IR de Sharp (_cf. Onglet Télémètre_). Pour la gestion des PWM des 2
servo-moteurs, elles sont gérées comme pour les pattes, par 2 timers hardware. La tête du robot est équipé d'une caméra de vision
CMUCAM2 permettant d'avoir un flux vidéo pour diriger le robot à distance ou de traquer une couleur par exemple (_cf. Onglet Caméra_)
</p>

#### 4.2 Le protocole ####

<p>
Dans le but de vérifier le bon fonctionnement de notre programme, nous testons via l'UART en simulant la valeur du télémètre par
exemple. Pour cela, nous faisions exactement pour la gestion des pattes par l'intermédiaire de trames.

~~~~~~~~~~~~~~~~~~~~~~
$TELE,x,10\n
~~~~~~~~~~~~~~~~~~~~~~ 

> <B>$</B> correspond au début de la trame
>
> <B>TELE</B> correspond aux trame des Telemètres. Dans notre cas, il n'y a qu'un mais nous avons penser à en rajouter pour l'évolution du produit
>
> <B>X</B> correspond au numéro du télémètre. Ici, 0 par défaut 
>
> <B>10</B> correspond à la distance de sécurité à ne pas dépasser pour pouvoir éviter l'objet.

~~~~~~~~~~~~~~~~~~~~~~
$CAM,MODE,R,G,B\n
~~~~~~~~~~~~~~~~~~~~~~

> <B>$</B> correspond au début de la trame
>
> <B>CAM</B> correspond à une trame de configuration pour la caméra
>
> <B>MODE</B> correspond aux modes de la caméra
>
> <B>R,G,B</B> correspond aux valeurs des 3 couleurs qui compose la couleur souhaité (uniquement pour le mode de "Color Tracking")

</p>

#### 4.3 Programmation ####

<p>
Pour la gestion de la tête du robot, nous avons penser à une structure contenant les deux servo-moteurs ainsi que le télémètre.
Pour des raisons de temps, nous n'avons pas encore intégrer les variables pour la caméra. Mais nous avons déjà penser à la 
manière dont nous allons l'intégrer. Plusieurs variables seront utiles selon l'utilisation de la caméra, mode tracking par exemple.

</p>
 
~~~~~~~~~~~~~~~{.c}
typedef struct
{
	ServoMoteur xServo1;
	ServoMoteur xServo2;
	Telemetre xTelemetre1;
	
}HeadHexapode;
~~~~~~~~~~~~~~~ 

> <B>xServo1</B> correspond au servo-moteur de l'axe X
>
> <B>xServo2</B> correspond au servo-moteur de l'axe Y
>
> <B>xTelemetre1</B> correspond au télémètre numéro 1.

Avec les modifications pour l'ajout de la caméra, voici à quoi pourrait ressembler la structure de la tête :

~~~~~~~~~~~~~~~{.c}
typedef struct
{
	ServoMoteur xServo1;
	ServoMoteur xServo2;
	Telemetre xTelemetre1;
	Color xColorTrack; //
	unsigned char ucMode;
	Flux xFluxCMUCAM;
	
}HeadHexapode;
~~~~~~~~~~~~~~~ 

> <B>xColorTrack</B> correspond aux valeurs des couleurs (Rouge, Vert et Bleu) de l'objet à "tracker"
>
> <B>ucMode</B> correspond au mode que nous voulons pour la caméra (_cf. Onglet Caméra_)
>
> <B>xFluxCMUCAM</B> correspond au flux vidéo de la caméra.

La structure __Color__ permettrait de mettre les valeurs, de 0 à 255, des couleurs composant la couleur à suivre.
~~~~~~~~~~~~~~~{.c}
typedef struct
{
	unsigned int Red;
	unsigned int Green;
	unsigned int Blue;
	
}Color;
~~~~~~~~~~~~~~~

### <A NAME="Capteur">5. Les capteurs</A> ###

Plusieurs capteurs équipent le robot : 

-	Les capteurs TOR
-	Le (ou les) télémètre(s) IR Sharp GP2D12

#### 5.1 Capteurs TOR ####

<p>
Pour l'utilisation de ces capteurs peut de choses sont à mettre en place. Il suffit de lire l'état présent sur la broche 
qui est reliée à capteur TOR pour avoir l'information :
</p>

-	Si la patte est en contact avec le sol, la valeur présente sur la broche vaut 1 (état logique haut).
-	Si la patte n'est pas en contact avec le sol, la valeur présente sur la broche vaut alors 0 (état logique bas).

<p>
Dans le second cas, après un certains temps ("Le Time Out" - _cf. 3.2 Protocole & Onglet Capteur TOR_) nous estimons qu'il y
a présence d'une erreur.
</p>
#### 5.2 Télémètre IR Sharp GP2D12 ####

<p>
Pour l'utiliser un tel capteur, il est nécessaire de mettre en place un convertisseur Analogique-Numérique (ADC). La valeur 
retournée par le télémètre est une valeur analogique comprise entre 0,6V et 3,1V correspondant respectivement à 80cm et à 10cm.
Le principe de fonctionnement est expliqué dans l'onglet _Le télémètre_. D'après la documentation du constructeur, qui est aussi 
disponible dans l'ongler _Le télémètre_, la courbe représentative du capteur est celle d'un système non-linéraire ce qui rend la
convertion plus difficile. Cela est du au phénomène du cône qui est formé par le faisceau InfraRouge. Dans ce cas nous avons simplifier
par mesure de simplicité et de temps et aussi par le manque du télémètre, linéariser le système. Le risque d'une telle manipulation
est de changer la précision, qui d'après nous serait au millimètre. Dans notre cas, la précision au millimètre près n'est pas forcément
utile car il est important d'esquiver un obstable bien avant d'arriver sur lui.
</p>
### <A NAME="Ordo">6. L'ordonnancement</A> ###

<p>
Le corps de ce projet est que le robot ne fonctionne pas sur un simple microcontrolleur. Nous utilisons un microcontrolleur ARM
Cortex M3 de chez NXP avec un système temps réel. Qui dit temps réel insinue le temps exact que prends une tâche ainsi qu'une notion
d'ordonnancement de tâches diverses. La difficulté d'un système dit temps réel est le nombre de tâche à executer. Plus le nombre
est grand plus la difficulté à ordonnancer est grande. C'est pour cela que l'équipe d'_Insset Robotics_ a essayer de minimiser ce
nombre de tâches tout en remplissant les demandes du client. Dans la configuration sans la caméra, nous n'avons que 3 tâches :
</p>

1. Tâche 1 : Lecture des différents capteurs (télémètre [__ADC__], TOR)
2. Tâche 2 : Gestion des PWM
3. Tâche 3 : Gestion des files de messages de la communication et le décodage des trames

<p>
Pour ordonnancer et définir les tâches prioritaires nous avons donc utiliser la méthode RM (__Rate Monotonic__) qui consiste  
a attribuer la priorité la plus forte à la tâche qui possède la plus petite période. La tâche la plus prioritaire de notre 
système est la tâche 2 ensuite la tâche 1 et la tâche la moins prioritaire est la tâche 3. Les priorités sont figées et ne varient
pas dans le temps ce qui serait incompatible avec la méthode d'ordonnancement choisie.
</p>

### <A NAME="Comm">7. La communication</A> ###

<p>
La communication qui a été choisi par le client afin de communiquer avec le robot depuis un ordinateur sous un OS de son choix est
une solution sans fil, le Zigbee. Le Zigbee est un protocole haut niveau de communication sans fil à très basse consommation. Ce
facteur a tout son importance pour un système qui doit être indépendant. Pour la mise en place d'un tel réseau sans fil, nous avons
besoin d'initialiser un port de communication à l'aide de l'UART qui est un des périphériques présents de la carte NXP LCP1761.
</p>

#### 7.1 L'émission ####

<p>
Pour l'émission des messages vers le PC qui commande le robot, l'équipe de développeur a décidé de mettre en place une pile FIFO (First
In First Out) qui permettra de stocker les messages à envoyer et se videra au fûr et à mesure que l'ordonnanceur donne la main à
la tâche s'occupant de l'envoi.
</p>

#### 7.2 La reception ####

<p>
Pour la réception des messages provenant du PC qui commande le robot, nous avons choisi de mettre également une queue de message
de type FIFO (First In First Out) qui stockera les message reçus et videra cette pile quand le message aura été décripté et traité.
</p>

#### 7.3 Schématisation ####

<p>
Voici à quoi ressemble le principe des files de messages que nous allons mettre en place au sein du projet.
</p>
</br>
![queue]
[queue]:../img/queue.png "Files de messages"

### <A NAME="IHM">8. L'Interface Homme-Machine</A> ###

Afin de garantir un confort d'utilisation, une IHM (_Interface Homme-Machine_) doit être réalisé. Cette IHM permettra à l'utilisateur
de configurer le robot, le choix du mode (Autonome ou Manuel), les choix pour la caméra (exemple : _tracking_ de couleur) mais aussi
de diriger le robot à l'aide de flèches permettant de faire avancer, reculer, se diriger vers la gauche ou la droite. Sur cette IHM,
nous pourrons aussi trouver, par exemple la présence ou non d'un obstable et de la distance qui sépare la tête du robot à ce dernier.
Lorsque le développement de la caméra sera achevé, l'interface donnera la possibilité de voir le flux vidéo de la caméra qui sera
une aide pour se déplacer avec le robot. Lorsque les algorithmes de marches seront réalisés ainsi que testés, il sera possible à
l'utilisateur de saisir le type de marche voulu, en crabe, 3 pattes par 3 pattes (en triangle), ...

Voici à quoi pourrait ressembler l'interface graphique :

![IHM]
[IHM]:../img/IHM.png "Interface graphique du logiciel HexaControl"
<A NAME="#Doc"></A>
\section Documentation



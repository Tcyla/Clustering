# Apprentissage non-supervisé : Clustering (Projet L3 S6)

## Introduction
Les problèmes de clustering visent à séparer un jeu de donner en plusieurs ensembles, appelés clusters, tel que les points ce trouvant à l'intérieur d'un cluster soit le plus proches possible les uns des autres et le plus éloigné possible de ceux des autres clusters. La proximité entre deux points est définie par l'utilisateur et dépand du type de donnée étudier. 

## K-Moyennes
L'algorithme des K-Moyennes est un algorithme de Clustering par optimisation. Le but est de trouver l'ensemble $S = (S_1, \dots, S_K)$ qui minimise la variation interne des clusters (*Total within cluster variation* ou TWCV)

$$TWCV  \overset{\Delta}{=} \sum_{i=1}^K\sum_{x\in S_i}{d(x, c_i)}$$

avec $K$ le nombre de clusters, $S_i$ l'ensemble des points du cluster $i\in\{1\dots K\}$, $d$ la distance et $c_i$ le centre du cluster $i$.  

### Algorithme utilisé

```
1. Inialiser les clusters avec des valeurs aléatoirement 
   choisie parmi les points. TWCV[0] = +∞, compte=0.
2. Assigner chaque point au cluster dont le centre lui est le 
   plus proche (ie trouver i* tel ||x-c_i*|| = min_i(||x-c_i||)).
3. Calculer TWCV[compte+1].
4. Si TWCV[compte+1] < TWCV[compte], incrémenter compte de 1
   puis reprendre à l'étape 2. 
   Sinon, terminer le programme.
```

#### Correction
L'algorithme ne converge pas vers le minimum global mais vers un minimum local. Ce minimum est fortement impacté par le choix des points d'initialisation qui est aléatoire. Il est donc conseillé de relancer plusieur fois l'algorithme et de choisir le résultat ayant la plus petite TWCV.


## DBSCAN

Contrairement à l'algorithme des K-Moyennes, DBSCAN  (*density-based spatial clustering of applications with noise*) est un algorithme de clustering à densité. On définie un cluster par un nombre de points minimum $n$ pour être un cluster et un paramètre $\varepsilon$. Ce dernier paramètre sert au calcul des $\varepsilon$-voisinages. 

L' $\varepsilon$-voisinages d'un point $x$ est l'ensemble des points distants d'au plus $\varepsilon$ de $x$. Un cluster est alors un ensemble de points de cardinal suppérieur ou égal à $n$ et qui verifie:

> Pour tous points $A$ et $B$ du cluster, il existe une suite de points du cluster $(x_i)$ avec $x_0= A$ et $x_{i+1} \in \varepsilon\text{-voisinage}(x_i)$ tel que $B$ appartient à l'ensemble
>$$ \bigcup_i \text{ $\varepsilon$-voisinage}(x_i). $$


### Algorithme utilisé

Voici la reproduction de l'algorithme DBSCAN, tel que proposé par
Kriegel et Xu dans leur article de 1996.

```
DBSCAN (SetOfPoints, Eps, MinPts)
   //  SetOfPoints is  UNCLASSIFIED
   ClusterId :=  nextId(NOISE);
   FOR  i  FROM 1  TO  SetOfPoints.size DO
      Point :=  SetOfPoints.get(i);
      IF  Point.CiId =  UNCLASSIFIED THEN
         IF  ExpandCluster(SetOfPoints, Point,
            ClusterId, Eps, MinPts) THEN
            ClusterId :=  nextId(ClusterId)
         END  IF
      END  IF
   END  FOR
END; 

ExpandCluster (SetOfPoints, Point,  CiId,  Eps,
               MinPts)  :  Boolean;
   seeds := SetOfPoints. regionQuery (Point, Eps ) 
   IF  seeds.size<MinPts THEN  //  no  core  point
      SetOfPoint. changeCl Id (Point, NOISE) 
      RETURN  False;
   ELSE //  all  points  in  seeds  are  density-
        //  reachable from  Point
      SetOfpoints. changeCiIds ( seeds, C1 Id) 
      seeds.delete (Point) 
      WHILE  seeds  <>  Empty  DO
         currentP  := seeds.first() 
         result  :=  setofPoints.regionQuery(currentP,Eps)
         IF  result.size >=  MinPts  THEN
            FOR  i FROM  1  TO  result.size DO
               resultP  := result.get(i) 
               IF  resultP.  CiId
                  IN  (UNCLASSIFIED, NOISE}  THEN
                  IF  resultP.CiId = UNCLASSIFIED THEN
                     seeds, append (resultP) 
                  END IF;
                  SetOfPoints. changeCiId ( resultP, CiId) 
               END  IF;  //  UNCLASSIFIED or  NOISE
            END FOR ;
         END IF;  //  result.size >=  MinPts
         seeds, delete (currentP) 
      END  WHILE;  //  seeds  <>  Empty
      RETURN True ;
   END  IF
END;
```

## Résutats et Discussion

![résultats](result.png)

Dans le premier exemple on est face a un exemple de clusters bien définie à la fois dense et séparé de l'autre cluster ainsi DBSCAN eT KMeans avec $K = 2$ donne le même résultat. Cela mais en evidence une

Dans le second example, on s'attendrait à avoir deux clusters le premier étant le cercle central et le second le cercle exterieur mai aucun des deux algorithmes ne parvient à se résultat.
KMeans sépare les points en deux groupes selon une droite. Ce comportant est du à la nature de Kmean qui cherche à diviser les points en $K$ groupes dont les points sont les plus proches possible de leur barycentre, la courone exterieur ayant le même barycentre que la courone intérieur et les points de la couronnes exterieur étant plus éloigné de leur barycentre que les points de la couronne intérieur, la couronne extérieur ne peux pas être considéré comme une cluster valable pour l'algorithme KMeans.
DBSCAN, au contraire, est conçu autour de la notion de densité, il identifie commme faisant partie d'un même cluster tous les points pouvant être relié par une chaine de points distant d'au plus $\varepsilon$ les uns des autres. C'est pourquoi la courone extérieur est classifié comme du bruit. S'il y avait eu plus de point utilisé l'algorithme aurait classifié la couronne extérieur comme un deuxième cluster. DBSCAN semble donc plus adapter à ce genre de données.

## Conclusion et pistes d'amélioration

Les algorithmes de clustering étant des algorithmes non supervisés, il est difficile de définir les résultats qui sont sensé être obtenu. La définition des clusters la plus approprié ainsi que celle de la norme utilisé et les paramètres de la méthodes influence grandement le résultat de la méthodes. Il s'agit donc d'utiliser ses algorithmes précautionneusement et de bien définir les objectifs fixés.

## Sources

### Général
*R. Xu and D. C. Wunsch, "Survey of Clustering Algorithms," IEEE Transactions on Neural Networks,
Institute of Electrical and Electronics Engineers (IEEE), May 2005.*

### KMeans
https://en.wikipedia.org/wiki/K-means_clustering, consulté le 5 mars 2021

### DBSCAN
https://en.wikipedia.org/wiki/DBSCAN, consulté le 8 mars 2021

*Ester, Kriegel, Sander, Xu. (1996). “A Density-Based Algorithm for Discovering Clusters
in Large Spatial Databaseswith Noise” in Proceedings of the 2nd International Conference on Knowledge Discovery and Data mining.*


## Annexe : Compiler et exécuter le programme

### Compiler

:warning: Pour pouvoir afficher les clusters le programme dépend de GNUPLOT. Vous pouvez télécharger la dernière version de gnuplot grâce à votre gestionnaire de paquets. 

#### Ubuntu

```bash
    apt install gnuplot-qt
```
En mode `RELEASE` cmake utilise la sortie graphique si GNUPLOT est disponible, en mode `DBG` , il faut affecter `TRUE` à la variable `USE_SCIPLOT`

```bash
    cmake -D USE_SCIPLOT=TRUE ..
    make
```

### Exécuter

Dans le dossier `.build/`, utiliser l'exécutable `./run` pour lancer le programme d'exemple ou `./test_clustering` pour effectuer les tests.

Le programme utilise une sortie graphique pour afficher les clusters ainsi que la sortie standard pour afficher le rapport d'exécution des algorithmes. Attention, ce rapport peut excéder la capacité d'affichage du terminal si le nombre de points est trop élévé.

Les tests utilisent la librairie Googletest, `./test_clustering` peut prendre en argument tous ceux définis par la librarie. 
En particulier `./test_clustering -h` permet de lister les argumements possibles et `./test_clustering --filter=<regex>` permet de n'exécuter qu'une partie des tests.
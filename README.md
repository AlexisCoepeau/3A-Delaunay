<table style="width:100%">
    <tr > <td> <h1> <a href="https://ccc.bordeaux-inp.fr/syllabus/index.php?annee=2022&mode=consultation&chemin=71125_71123_71122_71105_71104_71019_70340&langue=1">Projet 3A CHP 2022-2023</a> <br> Création d'un mailleur de Delaunay </h1> 
 </td> <td> <img src="./EMMK-logo.png" alt="Logo Enseirb-Matmeca"> </td> </tr>
</table>


## **Cadre du projet**
---------------------
### **Institution** 
- [Bordeaux-INP, Enseirb-Matmeca](https://enseirb-matmeca.bordeaux-inp.fr/fr)

### **Auteurs**

- [Alexis Coëpeau](https://www.linkedin.com/in/alexis-co%C3%ABpeau/)
- [Guillaume Damour](https://www.linkedin.com/in/guillaume-damour-5021331b7/)


### **Encadrants**
- [Nicolas Barral](https://nicolasbarral.fr/)

### **Sujet**

Le [sujet](./projet_delaunay.pdf) de projet est disponible au sein de cette archive.

### **Méthodes utilisées**

Le code de calcul a été programmé en `C++`.

## **Prise en main du code de calcul**
---------------------------------------------

### **Installation**

Ce projet est hébergé sur la plateforme [Thor](https://thor.enseirb-matmeca.fr/), interne à l'[Enseirb-Matmeca](https://enseirb-matmeca.bordeaux-inp.fr/fr).

L'ensemble du projet peut être téléchargé sous différents protocoles : 

- lien de clonage via protocole HTTP :  `git clone https://<LOGIN>@thor.enseirb-matmeca.fr/git/free-Maillage`

- Lien de clonage via protocole SSH :  `git clone ssh://git@thor.enseirb-matmeca.fr:2222/git/free-Maillage`

### **Génération d'un cas test et exécution du code de calcul**
Le code de calcul prend en entrée en ligne de commande un fichier au format [`.mesh`](./entrees.txt) constitué comme ci-dessous : 

```
MeshVersionFormatted 2

Dimension 2

Vertices
<nb_vertices>
x_1 y_1 label
 .   .    .
 .   .    .

Edges
<nb_edges>
V_1 V_2 label
 .   .    .
 .   .    .

End 
```

### **Analyse des résultats du code**
Le code de calcul déduit un maillage `sortie.mesh` et un fichier de mesure de qualité `sortie.sol` associés au domaine passé en argument de ligne de commande.

Le maillage peut être visualisé avec `gmsh` ou `medit`.

### **Génération de la documentation**

Dans le répertoire courant, tapez la commande :

`doxygen configFile` 

<div style='text-align:center'>
    <img src="./EMMK-logo.png" alt="Logo Enseirb-Matmeca">

Ce travail est la propriété de l'[Enseirb-Matmeca](https://enseirb-matmeca.bordeaux-inp.fr/fr).
</div>
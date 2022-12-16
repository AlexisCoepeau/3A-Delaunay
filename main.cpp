#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <vector>

/**
* @mainpage Projet Maillage - Documentation
* Ce projet rentre dans le cadre du <a href="https://moodle.bordeaux-inp.fr/pluginfile.php/161133/mod_resource/content/4/projet_delaunay.pdf">projet</a> de l'<a href='https://enseirb-matmeca.bordeaux-inp.fr/fr'>ENSEIRB-MATMECA</a> de 3A du module <a href="https://ent.bordeaux-inp.fr/render.userLayoutRootNode.uP?uP_sparam=activeTab&activeTab=5&uP_root=u28l1n40">Technique de Maillage</a>.
*
* @authors
* <ul>
* <li> <a href='https://www.linkedin.com/in/alexis-co%C3%ABpeau/'>Alexis COËPEAU</a> </li>
* <li> <a href='https://www.linkedin.com/in/guillaume-damour-5021331b7/'>Guillaume DAMOUR</a> </li>
* </ul>
*
* @par Encadrant
* <ul>
* <li> <a href="https://nicolasbarral.fr/">Nicolas BARRAL</a> </li>
* </ul>
*
* @copyright Ce travail est la propriété de l'<a href='https://enseirb-matmeca.bordeaux-inp.fr/fr'>ENSEIRB-MATMECA</a>.
* @date Décembre 2022.
*/

using namespace std;

struct maillage
{
  // Localisation des sommets
  /** @brief Nombre de sommets du maillage */
  int N_Vertices=0 ;

  /**
  * @brief Tableau des sommets du maillage
  * @details Le tableau de sommets est de taille 2 N_vertices. Il contient les coordonnées de chaque sommets du maillage :
  * <table>
  * <tr style="text-align:center"> <td> Indice : </td> <td> </td>  <td> \f$\cdots\f$ </td> <td> \f$2i\f$ </td> <td> \f$2i+1\f$ </td> <td> \f$\cdots\f$ </td> </tr>
  * <tr style="text-align:center"> <td> Vertices : </td> <td> </td> <td> \f$\cdots\f$ </td> <td> \f$x_i\f$ </td> <td> \f$y_i\f$ </td> <td> \f$\cdots\f$ </td> </tr>
  * </table>
  */
  vector<double> Vertices;

  /** @brief Position minimale selon x des sommets du maillage*/
  double VerticesXMin=0.0 ;

  /** @brief Position maximale selon x des sommets du maillage*/
  double VerticesXMax=0.0 ;

  /** @brief Position minimale selon y des sommets du maillage*/
  double VerticesYMin=0.0 ;

  /** @brief Position maximale selon y des sommets du maillage*/
  double VerticesYMax=0.0 ;

  /** @brief Nombre de segments du maillage */
  int N_Edges=0 ;
  /**
  * @brief Tableau des segments du maillage
  * @details Le tableau de segments est de taille 2 N_Edges. Il est contient le numéro des sommets pour chaque segment du maillage :
  * <table>
  * <tr style="text-align:center"> <td> Indice : </td> <td> </td>  <td> \f$\cdots\f$ </td> <td> \f$2i\f$ </td> <td> \f$2i+1\f$ </td> <td> \f$\cdots\f$ </td> </tr>
  * <tr style="text-align:center"> <td> Edges : </td> <td> </td> <td> \f$\cdots\f$ </td> <td> \f$S_1\f$ </td> <td> \f$S_2\f$ </td> <td> \f$\cdots\f$ </td> </tr>
  * </table>
  */
  vector<int> Edges;
  // Triangle entre trois sommets numérotés

  /** @brief Nombre de triangles du maillage */
  int N_Triangles=0 ;
  /**
  * @brief Tableau des triangles du maillage
  * @details Le tableau de triangles est de taille 2 N_Triangles. Il est contient le numéro des sommets pour chaque triangles du maillage :
  * <table>
  * <tr style="text-align:center"> <td> Indice : </td> <td> </td>  <td> \f$\cdots\f$ </td> <td> \f$3i\f$ </td> <td> \f$3i+1\f$ </td> <td> \f$3i+2\f$ </td>  <td> \f$\cdots\f$ </td> </tr>
  * <tr style="text-align:center"> <td> Triangles : </td> <td> </td> <td> \f$\cdots\f$ </td> <td> \f$S_1\f$ </td> <td> \f$S_2\f$ </td> <td> \f$S_3\f$ </td> <td> \f$\cdots\f$ </td> </tr>
  * </table>
  */
  vector<int> Triangles;
  int N_Corners=0 ;
  vector<int> Corners;
  int N_Ridges=0 ;
  vector<int> Ridges;
};

/* PROTOTYPES */

double Distance2D(const double, const double, const double, const double) ;
double Qualite2D(const int, const struct maillage &) ;
void cercle(int, struct maillage &, double, double) ;
void AjoutePoint(const int, const struct maillage &, struct maillage &) ;
void Chargement(const char*, struct maillage*) ;
void EcritureSol(const char*, const struct maillage &) ;
void TriangleToNodes(const struct maillage &, const int, int &, int &, int &);
void EdgeToNodes(const struct maillage &, const int, int &, int &) ;
int  Admissibilite(const double, const double, const int, const struct maillage &) ;
void NodeToEdges(const struct maillage &, const int, int* &, int &) ;
void NodeToTriangles(const struct maillage &, const int, int* &, int &);
void Triangle_to_its_neighbours(const struct maillage &, const int , int* &, int &);
void Triangle_to_its_neighbours_sans_deja_vu(const struct maillage &, const int, int* &, int &, vector<int> &);
bool IsPointInTriangle(const struct maillage &, const int, const double, const double) ;
void treatCouple(const int, const int, vector<int> &, vector<int> &) ;
void Sortie(const char*, struct maillage &) ;
void Creation_boite(struct maillage&, const double, const double, const double, const double) ;
void swap(const int, const int, struct maillage &) ;
void ForceBound(struct maillage &) ;
bool triangleCrossEdges(const int, const int, const int, const struct maillage &) ;
void Deletebox(struct maillage &, vector<int> &, int* &);
void Delete(struct maillage &, int, vector<int> &, int* &, int);

/**
* @brief Fonction principale
* @details Usage : ./main <fichier.mesh>
*/
int main(int argc, char* argv[])
{

  if(argc!=2){
    cout<<"Erreur : Mauvaise utilisation de l'executable !" << endl << endl ;
    cout<<"Utilisation : ./main <fichier_entreee.mesh>" << endl ;
    cout<<"Exemple : " << endl ;
    exit(EXIT_FAILURE) ;
  }

  // Déclaration du maillage
  struct maillage mesh_Initial;

  // Chargement des données de maillage
  Chargement(argv[1], &mesh_Initial) ;

  //Création de la boite
  struct maillage mesh_Final ;
  Creation_boite(mesh_Final, mesh_Initial.VerticesXMax, mesh_Initial.VerticesXMin, mesh_Initial.VerticesYMax, mesh_Initial.VerticesYMin) ;

  //Ajout des Edges
  mesh_Final.N_Edges=mesh_Initial.N_Edges ;
  mesh_Final.Edges.resize(2*mesh_Final.N_Edges) ;

  for(int i=0 ; i< 2*mesh_Initial.N_Edges ; i++)
    mesh_Final.Edges[i]=mesh_Initial.Edges[i]+4 ;


  for(int i=1; i<mesh_Initial.N_Vertices+1; i++)
  {
    AjoutePoint(i, mesh_Initial, mesh_Final);
  }

  ForceBound(mesh_Final) ;

  cout << "iti" << endl ;

  vector<int> tabdejavu ;
  int* triangles_a_supprimer ;

  Deletebox(mesh_Final, tabdejavu, triangles_a_supprimer) ;

  cout << "itie" << endl ;


  for(int triangle=0 ; triangle < mesh_Final.N_Triangles ; triangle++){
    cout << "Triangle " << triangle << " a supprimer ? : " << triangles_a_supprimer[triangle] << endl ;
  }

  cout << "itiee" << endl ;


  Sortie("sortie.mesh", mesh_Final);

  //Affichage de la qualité
  // for(int i=0; i<2; i++)
  // {
  // 	cout << "-------------------------------------------------------" << endl;
  // 	cout << "Qualité triangle " << i << "=" << Qualite2D(i, mesh_Initial) << endl;
  // }
  //

  // cercle(1, mesh_Initial, 3.0, 2.5);
  // cout << "Admissibilité = " << Admissibilite(3.0, 2.5, 1, mesh_Initial) << endl;
  // cercle(1, mesh_Initial, 3.0, 13.0);
  // cout << "Admissibilité = " << Admissibilite(3.0, 13.0, 1, mesh_Initial) << endl;
  // cercle(1, mesh_Initial, 3.0, 7.0);
  // cout << "Admissibilité = " << Admissibilite(3.0, 7.0, 1, mesh_Initial) << endl;

  EcritureSol("sortie.sol", mesh_Final) ;

  //Libération de la mémoire de maillage automatiquement
  return 0;
}

/* CONTAINS */

void Creation_boite(struct maillage & mesh, const double xmax, const double xmin, const double ymax, const double ymin)
{
  mesh.Vertices.push_back(xmin-(xmax-xmin)/2.);  // 20x
  mesh.Vertices.push_back(ymin-(ymax-ymin)/2.);  // 20y

  mesh.Vertices.push_back(xmax+(xmax-xmin)/2.);  // 21x
  mesh.Vertices.push_back(ymin-(ymax-ymin)/2.);  // 21y

  mesh.Vertices.push_back(xmax+(xmax-xmin)/2.);  // 22x
  mesh.Vertices.push_back(ymax+(ymax-ymin)/2.);  // 22y

  mesh.Vertices.push_back(xmin-(xmax-xmin)/2.);  // 23x
  mesh.Vertices.push_back(ymax+(ymax-ymin)/2.);  // 23y

  mesh.Triangles.push_back(1) ;
  mesh.Triangles.push_back(2) ;
  mesh.Triangles.push_back(4) ;

  mesh.Triangles.push_back(2) ;
  mesh.Triangles.push_back(3) ;
  mesh.Triangles.push_back(4) ;

  mesh.N_Vertices = 4;
  mesh.N_Triangles = 2;
}


/**
* @brief Fonction renvoyant la distance euclidienne en 2 dimensions entre 2 points.
* @param[in] x1 Position selon x du point 1.
* @param[in] y1 Position selon y du point 1.
* @param[in] x2 Position selon x du point 2.
* @param[in] y2 Position selon y du point 2.
* @par Théorie et Algorithmie
* \f$ distance = \sqrt{(x_1-x_2)^2+(y_1-y_2)^2}\f$
*
* @par Complexité
* Temps constant.
*/
double Distance2D(const double x1, const double y1, const double x2, const double y2)
{
  double dist=0.0;

  dist=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));

  return dist;
}

/**
* @brief Fonction calculant la qualité d'un triangle numéro \f$numTriangle\f$ pour un maillage donné.
* @param[in] numTriangle numéro du triangle.
* @param[in] mesh maillage.
* @par Théorie et Algorithmie
* Si on note \f$S_1(x_1,y_1), S_2(x_2,y_2)\f$ et \f$S_3(x_3,y_3)\f$ les sommets du triangle considéré,
* <ul>
* <li> \f$aire = \frac{1}{2}\begin{vmatrix} x_2-x_1 & x_3-x_1 \\ y_2-y_1 & y_3-y_1 \end{vmatrix}\f$</li>
* <li> \f$Qualité = \frac{\sqrt{3}}{12} \frac{S_1S_2^2+S_1S_3^2+S_2S_3^2}{aire}\f$ </li>
* </ul>
*
* @par Complexité
* Temps constant.
*/
double Qualite2D(const int numTriangle, const struct maillage &mesh)
{
  double Q, aire, s1x, s1y, s2x, s2y, s3x, s3y;
  s1x = mesh.Vertices[(mesh.Triangles[3*numTriangle]-1)*2];
  s1y = mesh.Vertices[(mesh.Triangles[3*numTriangle]-1)*2+1];
  s2x = mesh.Vertices[(mesh.Triangles[3*numTriangle+1]-1)*2];
  s2y = mesh.Vertices[(mesh.Triangles[3*numTriangle+1]-1)*2+1];
  s3x = mesh.Vertices[(mesh.Triangles[3*numTriangle+2]-1)*2];
  s3y = mesh.Vertices[(mesh.Triangles[3*numTriangle+2]-1)*2+1];

  aire = abs((1./2.)*((s2x-s1x)*(s3y-s1y)-(s3x-s1x)*(s2y-s1y)));

  Q = (sqrt(3.0)/(12.0*aire))*( Distance2D(s1x, s1y, s2x, s2y)*Distance2D(s1x, s1y, s2x, s2y)
  +Distance2D(s1x, s1y, s3x, s3y)*Distance2D(s1x, s1y, s3x, s3y)
  +Distance2D(s3x, s3y, s2x, s2y)*Distance2D(s3x, s3y, s2x, s2y));

  return Q;
}



/**
* @brief Procédure de chargement du maillage
* @details
* Procédure qui prend un fichier d'entrée au format `.mesh` et qui charge les données dans une structure `maillage`.
*
* @param[in] fichier Fichier de données au format `.mesh`.
* @param[out] mesh Structure maillage.
*
* @par Complexité
* Temps linéaire à la longueur du fichier d'entrée.
*
* @warning
* La procédure arrête le programme avec `EXIT_FAILURE` et affiche un message d'erreur si le fichier ne peut pas être ouvert.
* @sa maillage
*/
void Chargement(const char* fichier, struct maillage *mesh)
{
  ifstream monFlux(fichier); // exemple : "${PATH}/meshes/2D/square_disc.mesh"
  string ligne;
  int indice;
  if(monFlux)
  {
    while(getline(monFlux,ligne))
    {
      if(ligne=="Vertices")
      {
        monFlux >> mesh->N_Vertices; // Nombre de sommets
        double stock ;

        // Remplissage du tableau de taille 2*N_Vertices
        for(int i=0; i<mesh->N_Vertices; i++)
        {
          // 1re coordonnée du sommet
          monFlux >> stock ;
          mesh->VerticesXMin=min(mesh->VerticesXMin, stock) ;
          mesh->VerticesXMax=max(mesh->VerticesXMax, stock) ;
          mesh->Vertices.push_back(stock);   // stocké en 2*i

          //2e coordonnée du sommet
          monFlux >> stock ;
          mesh->VerticesYMin=min(mesh->VerticesYMin, stock) ;
          mesh->VerticesYMax=max(mesh->VerticesYMax, stock) ;
          mesh->Vertices.push_back(stock);  // stocké en 2*i+1

          monFlux >> indice;
        }
      }
      if(ligne=="Edges")
      {
        monFlux >> mesh->N_Edges;
        int stock ;

        // Remplissage du tableau de taille 2*N_Egdes
        for(int i=0; i<mesh->N_Edges; i++)
        {
          monFlux >> stock;
          mesh->Edges.push_back(stock);   // stocké en 2*i
          monFlux >> stock;
          mesh->Edges.push_back(stock);   // stocké en 2*i+1

          monFlux >> indice;
        }
      }
      if(ligne=="Triangles")
      {
        monFlux >> mesh->N_Triangles;
        int stock ;

        // Remplissage du tableau de taille 3*N_Triangles
        for(int i=0; i<mesh->N_Triangles; i++)
        {
          monFlux >> stock;
          mesh->Triangles.push_back(stock);   // stocké en 3*i
          monFlux >> stock;
          mesh->Triangles.push_back(stock);   // stocké en 3*i+1
          monFlux >> stock ;
          mesh->Triangles.push_back(stock);   // stocké en 3*i+2

          monFlux >> indice;
        }
      }
      if(ligne=="Corners")
      {
        monFlux >> mesh->N_Corners;
        int stock ;

        // Remplissage du tableau de taille N_Corners
        for(int i=0; i<mesh->N_Corners; i++)
        {
          monFlux >> stock;
          mesh->Corners.push_back(stock);   // stocké en 3*i
        }
      }
      if(ligne=="Ridges")
      {
        monFlux >> mesh->N_Ridges ;
        int stock ;

        // Remplissage du tableau de taille N_Ridges
        for(int i=0; i<mesh->N_Ridges; i++)
        {
          monFlux >> stock;
          mesh->Ridges.push_back(stock);   // stocké en 3*i
        }
      }
    }
    monFlux.close();
  }
  else{
    cout<<"Erreur : ouverture de fichier" << endl << endl ;
    cout<<"Vous avez voulu traiter le fichier :" << fichier << endl ;
    exit(EXIT_FAILURE) ;
  }
}


/**
* @brief Procédure de chargement du maillage
* @details
* Procédure qui prend un fichier d'entrée au format `.mesh` et qui charge les données dans une structure `maillage`.
*
* @param[in] fichier Fichier de données au format `.mesh`.
* @param[out] mesh Structure maillage.
*
* @par Complexité
* Temps linéaire à la longueur du fichier d'entrée.
*
* @warning
* La procédure arrête le programme avec `EXIT_FAILURE` et affiche un message d'erreur si le fichier ne peut pas être ouvert.
* @sa maillage
*/
void Sortie(const char* fichier, struct maillage &mesh)
{
  ofstream monFlux(fichier);
  string ligne;
  monFlux << "MeshVersionFormatted 2" << endl;
  monFlux << " " << endl;
  monFlux << "Dimension 2" << endl;
  monFlux << " " << endl;

  monFlux << "Vertices" << endl;
  monFlux << mesh.N_Vertices << endl; // Nombre de sommets
  for(int i=0; i< mesh.N_Vertices; i++)
  {
    monFlux << mesh.Vertices[2*i] << " " << mesh.Vertices[2*i+1] << endl;
  }
  monFlux << " " << endl;

  monFlux << "Edges" << endl;
  monFlux << mesh.N_Edges<< endl;
  for(int i=0; i<mesh.N_Edges; i++)
  {
    monFlux << mesh.Edges[2*i] << " " << mesh.Edges[2*i+1] << endl;
  }
  monFlux << " " << endl;

  monFlux << "Triangles" << endl;
  monFlux << mesh.N_Triangles<< endl;
  for(int i=0; i<mesh.N_Triangles; i++)
  {
    monFlux <<  mesh.Triangles[3*i] << " " << mesh.Triangles[3*i+1] << " " << mesh.Triangles[3*i+2] << endl;
  }
  monFlux << " " << endl;

  monFlux << "Corners" << endl;
  monFlux << mesh.N_Corners<< endl;
  for(int i=0; i<mesh.N_Corners; i++)
  {
    monFlux <<  mesh.Corners[i] << endl;
  }
  monFlux << " " << endl;

  monFlux << "Ridges" << endl;
  monFlux << mesh.N_Ridges<< endl ;
  for(int i=0; i<mesh.N_Ridges; i++)
  {
    monFlux << mesh.Ridges[i] << endl;   // stocké en 3*i
  }
  monFlux.close();

}


/**
* @brief Fonction qui enregistre un fichier `.sol` contenant les qualité des triangles.
* @warning Uniquement valable avec une dimension 2.
*/
void EcritureSol(const char* fichier, const struct maillage &mesh){
  ofstream monFlux(fichier);
  if(monFlux){
    monFlux << "MeshVersionFormatted" << endl ;
    monFlux << "2" << endl;
    monFlux << endl ;
    monFlux << "Dimension" << endl;
    monFlux << "2" << endl;
    monFlux << endl ;
    monFlux << "SolAtTriangles" << endl ;
    monFlux << mesh.N_Triangles << endl ;
    for(int triangle=0 ; triangle < mesh.N_Triangles ; triangle++){
      monFlux << Qualite2D(triangle, mesh) << endl ;
    }
  }else{
    cout<<"Erreur : écriture de fichier .sol" << endl << endl ;
    cout<<"Vous avez voulu écrire dans le fichier :" << fichier << endl ;
    exit(EXIT_FAILURE) ;
  }
}

/**
* @brief Fonction qui teste le critère de Delaunay pour un point et un triangle donné.
*
* @details La fonction renvoie -1 si le point se situe dans la boule circonscrite du triangle de numéro \f$numTriangle\f$ du maillage. 0 sinon
* @param[in] x Position selon x du point à tester.
* @param[in] y Position selon y du point à tester.
* @param[in] numTriangle numéro du triangle.
* @param[in] mesh Structure de maillage.
*
* @par Complexité
* Temps constant.
*/
int Admissibilite(const double x, const double y, const int numTriangle, const struct maillage &mesh)
{
  //Sommets du triangle numTriangle
  double s1x, s1y, s2x, s2y, s3x, s3y;
  s1x = mesh.Vertices[(mesh.Triangles[3*numTriangle]-1)*2];
  s1y = mesh.Vertices[(mesh.Triangles[3*numTriangle]-1)*2+1];
  s2x = mesh.Vertices[(mesh.Triangles[3*numTriangle+1]-1)*2];
  s2y = mesh.Vertices[(mesh.Triangles[3*numTriangle+1]-1)*2+1];
  s3x = mesh.Vertices[(mesh.Triangles[3*numTriangle+2]-1)*2];
  s3y = mesh.Vertices[(mesh.Triangles[3*numTriangle+2]-1)*2+1];

  //Test
  // s3x = 3.0;
  // s3y = 2.8;
  // s2x = 3.72;
  // s2y = 2.76;
  // s1x = 0.145;
  // s1y = 4.314;

  //Propriétés du cercle circonscrit au triangle
  double a, b, c, d, e, f, g, alpha, xcentre, ycentre, rayon;
  //Distance entre le point et le centre du cercle circonscrit
  double dist=0.0;
  //Admissible -1 si ne respecte pas le critère de Delaunay et 0 sinon
  int Delaunay=0;

  // a = s2x - s1x;
  // b = s2y - s1y;
  // c = s3x - s1x;
  // d = s3y - s1y;
  // e = s2x*s2x - s1x*s1x + s2y*s2x - s1y*s1y;
  // f = s3x*s3x - s1x*s1x + s3y*s3y - s1y*s1y;
  // g = -(1./(2.*(a*d-b*c)));
  //
  // xcentre = g*( d*e - b*f);
  // ycentre = g*(-c*e + a*f);

  a = s1y - s2y;
  b = s3y - s1y;
  c = s2x - s1x;
  d = s1x - s3x;
  e = (s3x-s2x)/2.;
  f = (s3y-s2y)/2.;
  g = (1./(a*d-b*c));

  alpha = g*( d*e - b*f);
  xcentre = alpha*(s1y - s2y) + (s1x + s2x)/2.;
  ycentre = alpha*(s2x - s1x) + (s1y + s2y)/2.;


  rayon = Distance2D(xcentre,ycentre,s1x,s1y);

  dist  = Distance2D(xcentre,ycentre,x,y);

  if (dist<rayon)
  {
    Delaunay=-1;
  }

  return Delaunay;
}



void cercle(int i, struct maillage &mesh, double x, double y)
{
  //Sommets du triangle i
  double s1x, s1y, s2x, s2y, s3x, s3y;
  s1x = mesh.Vertices[(mesh.Triangles[3*i]-1)*2];
  s1y = mesh.Vertices[(mesh.Triangles[3*i]-1)*2+1];
  s2x = mesh.Vertices[(mesh.Triangles[3*i+1]-1)*2];
  s2y = mesh.Vertices[(mesh.Triangles[3*i+1]-1)*2+1];
  s3x = mesh.Vertices[(mesh.Triangles[3*i+2]-1)*2];
  s3y = mesh.Vertices[(mesh.Triangles[3*i+2]-1)*2+1];

  //Test
  // s3x = 3.0;
  // s3y = 2.8;
  // s2x = 3.72;
  // s2y = 2.76;
  // s1x = 0.145;
  // s1y = 4.314;

  //Propriétés du cercle circonscrit au triangle
  double a, b, c, d, e, f, g, alpha, xcentre, ycentre, rayon;
  //Autres
  int N=100;
  double theta, coef;

  // a = s2x - s1x;
  // b = s2y - s1y;
  // c = s3x - s1x;
  // d = s3y - s1y;
  // e = s2x*s2x - s1x*s1x + s2y*s2x - s1y*s1y;
  // f = s3x*s3x - s1x*s1x + s3y*s3y - s1y*s1y;
  // g = -(1./(2.*(a*d-b*c)));
  //
  // xcentre = g*( d*e - b*f);
  // ycentre = g*(-c*e + a*f);
  //

  a = s1y - s2y;
  b = s3y - s1y;
  c = s2x - s1x;
  d = s1x - s3x;
  e = (s3x-s2x)/2.;
  f = (s3y-s2y)/2.;
  g = (1./(a*d-b*c));

  alpha = g*( d*e - b*f);
  xcentre = alpha*(s1y - s2y) + (s1x + s2x)/2.;
  ycentre = alpha*(s2x - s1x) + (s1y + s2y)/2.;

  coef=1./N;
  ofstream monFlux1("cercle.dat");
  monFlux1 << "#Triangle" << endl;
  for (int i=0; i<=N; i++)
  {
    monFlux1 << i*coef*(s2x - s1x) + s1x << " " << i*coef*(s2y - s1y) + s1y << endl;
  }
  for (int i=0; i<=N; i++)
  {
    monFlux1 << i*coef*(s3x - s1x) + s1x << " " << i*coef*(s3y - s1y) + s1y << endl;
  }
  for (int i=0; i<=N; i++)
  {
    monFlux1 << i*coef*(s3x - s2x) + s2x << " " << i*coef*(s3y - s2y) + s2y << endl;
  }

  monFlux1 << " " << endl;
  monFlux1 << " " << endl;
  monFlux1 << "#Centre" << endl;
  monFlux1 << xcentre << " " << ycentre << endl;

  rayon = Distance2D(xcentre,ycentre,s1x,s1y);
  theta = 2*(4*atan(1))/N;
  monFlux1 << " " << endl;
  monFlux1 << " " << endl;
  monFlux1 << "#Cercle" << endl;
  for (int i=0; i<=N; i++)
  {
    monFlux1 << xcentre + rayon*cos(i*theta) << " " << ycentre + rayon*sin(i*theta) << endl;
  }

  monFlux1 << " " << endl;
  monFlux1 << " " << endl;
  monFlux1 << "#Point" << endl;
  monFlux1 << x << " " << y << endl;

  monFlux1.close();
}


/**
* @brief Fonction qui renvoie vrai sur un triangle donné coupe le segment entre 2 sommets donné.
* @param[in] triangle Numéro du triangle à considérer.
* @param[in] sommet Numéro du premier sommet <b> qui appartient au triangle </b>.
* @param[in] sommet_opp Numéro du sommet opposé par le segment à sommet numéro `sommet.
* @param[in] mesh Structure de maillage.
*/
bool triangleCrossEdges(const int triangle, const int sommet, const int sommet_opp, const struct maillage &mesh){

  int S1 = mesh.Triangles[3*triangle] ;
  int S2 = mesh.Triangles[3*triangle+1] ;
  int S3 = mesh.Triangles[3*triangle+2] ;

  // Bascule sur S1 S2
  if(sommet==S1){
    S1=S3 ;
  }else if(sommet==S2){
    S2=S3 ;
  }

  // Positions de S1 et S2
  double S1x = mesh.Vertices[2*(S1-1)] ;
  double S1y = mesh.Vertices[2*(S1-1)+1] ;
  double S2x = mesh.Vertices[2*(S2-1)] ;
  double S2y = mesh.Vertices[2*(S2-1)+1] ;

  // Equation de la droite S1 S2 : ax+by=c
  double a = -(S2y-S1y) ;
  double b =  (S2x-S1x) ;
  double c = a*S1x+b*S1y ;

  // Position de sommet et sommet_opp
  double sommetx = mesh.Vertices[2*(sommet-1)] ;
  double sommety = mesh.Vertices[2*(sommet-1)+1] ;
  double sommet_oppx = mesh.Vertices[2*(sommet_opp-1)] ;
  double sommet_oppy = mesh.Vertices[2*(sommet_opp-1)+1] ;

  // Equation de la droite portée par le edges : dx+ey=f
  double d = -(sommet_oppy-sommety) ;
  double e =  (sommet_oppx-sommetx) ;
  double f = d*sommetx+e*sommety ;

  /* Système à résoudre pour trouver le point d'intersection
  * entre les 2 droites */

  double x = 1.0/(a*e-d*b) *(e*c-b*f) ;
  double y = 1.0/(a*e-d*b) *(-d*c+a*f) ;

  // Calcul du produit scalaire entre S1S2 et S2 intersec / ||S1S2||
  double PS1 = ((S2x-S1x)*(x-S1x)+(S2y-S1y)*(y-S1y))/((S2x-S1x)*(S2x-S1x)+(S2y-S1y)*(S2y-S1y)) ;
  // Calcul du produit scalaire entre edge et sommet-intersec / ||edge||
  double PS2 = ((sommet_oppx-sommetx)*(x-sommetx)+(sommet_oppy-sommety)*(y-sommety))/((sommet_oppx-sommetx)*(sommet_oppx-sommetx)+(sommet_oppy-sommety)*(sommet_oppy-sommety)) ;

  // Il faut que le point soit entre S1 et S2 mais également entre les 2 points de edge.
  if((PS1>0.0)&&(PS1<1.0)&&(PS2>0.0)&&(PS2<1.0))
  return true ;
  else
  return false ;
}

/**
* @brief Fonction qui modifie le maillage pour le forcer à contenir la frontière du domaine.
* @param[inout] mesh Structure de maillage.
*/
void ForceBound(struct maillage &mesh){

  for(int edge=1 ; edge < mesh.N_Edges+1 ; edge++){
    int S1 = mesh.Edges[2*(edge-1)] ;
    int S2 = mesh.Edges[2*(edge-1)+1] ;

    // Tableau contenant S1
    int NTrianglesS1 ;
    int *tabTrianglesS1 ;
    NodeToTriangles(mesh, S1, tabTrianglesS1, NTrianglesS1) ;

    // Vérification : "Existe-t-il un triangle qui contient S2 ?"
    bool dejaInclu = false ;
    int i = 0 ;
    int numTriangle ;
    while((not(dejaInclu)) && (i<NTrianglesS1)){
      numTriangle = tabTrianglesS1[i] ;
      dejaInclu = (S2==mesh.Triangles[3*numTriangle])||(S2==mesh.Triangles[3*numTriangle+1])||(S2==mesh.Triangles[3*numTriangle+2]) ;
      i++ ;
    }


    if(not(dejaInclu)){
      bool isGoodTriangle=false ;
      i=-1 ;
      while(not(isGoodTriangle)){
        i++ ;
        isGoodTriangle = triangleCrossEdges(tabTrianglesS1[i], S1, S2, mesh) ;
      }

      // Tableau contenant S2
      int NTrianglesS2 ;
      int *tabTrianglesS2 ;
      NodeToTriangles(mesh, S2, tabTrianglesS2, NTrianglesS2) ;

      isGoodTriangle=false ;
      int j=-1 ;
      while(not(isGoodTriangle)){
        j++ ;
        isGoodTriangle = triangleCrossEdges(tabTrianglesS2[j], S2, S1, mesh) ;
      }

      // Swap final
      swap(tabTrianglesS1[i], tabTrianglesS2[j], mesh) ;
    }
  }
}


void Deletebox(struct maillage &mesh, vector<int> &tabdejavu, int* &triangles_a_supprimer)
{
  //Initialisation du tableau des triangles à supprimer (0 si on ne supprime pas et 1 si on supprime le triangle i)
  triangles_a_supprimer = (int*)malloc(mesh.N_Triangles*sizeof(int));
  
  for(int i=0 ; i<mesh.N_Triangles ; i++)
    triangles_a_supprimer[i] = 0;

  // Tableau contenant 1 (qui appartient à la boite)
  int NTrianglesS1 ;
  int *tabTrianglesS1 ;
  NodeToTriangles(mesh, 1, tabTrianglesS1, NTrianglesS1) ;

  //On prend au hazard un des triangles qui a pour sommet 1 qui sera forcément un triangle qu'on souhaite supprimer
  int premier_triangle = tabTrianglesS1[0] ;

  Delete(mesh, premier_triangle, tabdejavu, triangles_a_supprimer, 1);

  free(tabTrianglesS1);
}


void Delete(struct maillage &mesh, int triangle, vector<int> &tabdejavu, int* &triangles_a_supprimer, int cond_arret)
{
  if (cond_arret==1)
  {
    //Calcule des voisins du triangle
    int NTriangles;
    int* tabNeighbours;
    Triangle_to_its_neighbours_sans_deja_vu(mesh, triangle, tabNeighbours, NTriangles, tabdejavu);

    int numTriangle ;
    int S1, S2, S3;
    int S1edge, S2edge;
    for (int i=0; i<NTriangles; i++)
    {
      numTriangle = tabNeighbours[i];
      S1 = mesh.Triangles[3*numTriangle];
      S2 = mesh.Triangles[3*numTriangle+1];
      S3 = mesh.Triangles[3*numTriangle+2];

      for (int j=0; j<mesh.N_Edges; j++)
      {
        S1edge = mesh.Edges[2*j];
        S2edge = mesh.Edges[2*j+1];

        // Si le triangle voisin est un triangle appartenant au domaine de calcul, on arrête
        if (((S1==S1edge)||(S1==S2edge))&&((S2==S1edge)||(S2==S2edge)))
        {
          triangles_a_supprimer[numTriangle]=1;
          Delete(mesh, numTriangle, tabdejavu, triangles_a_supprimer, 0);
        }
        else if (((S1==S1edge)||(S1==S2edge))&&((S3==S1edge)||(S3==S2edge)))
        {
          triangles_a_supprimer[numTriangle]=1;
          Delete(mesh, numTriangle, tabdejavu, triangles_a_supprimer, 0);
        }
        else if (((S2==S1edge)||(S2==S2edge))&&((S3==S1edge)||(S3==S2edge)))
        {
          triangles_a_supprimer[numTriangle]=1;
          Delete(mesh, numTriangle, tabdejavu, triangles_a_supprimer, 0);
        }
        else
        { // Si le triangle voisin n'est pas un triangle appartenant au domaine de calcul, on continue
          triangles_a_supprimer[numTriangle]=1;
          Delete(mesh, numTriangle, tabdejavu, triangles_a_supprimer, 1);
        }
      }
    }
    free(tabNeighbours) ;
  }
}

/**
* @brief Procédure qui renvoie la liste des sommets d'un triangle donné.
*
* @param[in] mesh Structure de maillage.
* @param[in] numTriangle Numéro du triangle.
* @param[in] S1 numéro du sommet 1.
* @param[in] S2 numéro du sommet 2.
* @param[in] S3 numéro du sommet 3.
*
* @par Complexité
* Temps constant.
*/
void TriangleToNodes(const struct maillage &mesh, const int numTriangle, int &S1, int &S2, int &S3){
  S1 = mesh.Triangles[3*numTriangle] ;
  S2 = mesh.Triangles[3*numTriangle+1] ;
  S3 = mesh.Triangles[3*numTriangle+2] ;
}

/**
* @brief Procédure qui renvoie la liste des sommets d'un côté donné.
*
* @param[in] mesh Structure de maillage.
* @param[in] numEdge Numéro du coté.
* @param[in] S1 numéro du sommet 1.
* @param[in] S2 numéro du sommet 2.
* @par Complexité
* Temps constant.
*/
void EdgeToNodes(const struct maillage &mesh, const int numEdge, int &S1, int &S2){
  S1 = mesh.Edges[2*numEdge] ;
  S2 = mesh.Edges[2*numEdge+1] ;
}

/**
* @brief Procédure qui renvoie la liste des côtés dans lequel un sommet donné est engagé.
*
* @param[in] mesh Structure de maillage.
* @param[in] numSommet Numéro du sommet.
* @param tabEdges Liste des cotés <b>non alloué</b> en entrée, <b>alloué</b> en sortie.
* @param NEdges Nombres des cotés et taille de tabEdges.
* @par Complexité
* Linéaire du nombre de côté du maillage mesh.
*/
void NodeToEdges(const struct maillage &mesh, const int numSommet, int* &tabEdges, int & NEdges){

  // Variables
  int S1, S2     ; // Sommets candidats
  NEdges=0       ; // Nombre de côtés effectifs
  int* Edges_Max ; // Côtés effectifs

  // Tableau de taille maximale
  Edges_Max=(int*)malloc(mesh.N_Edges*sizeof(int)) ;

  // Recherche des cotés effectifs
  for(int edge=0 ; edge < mesh.N_Edges ; edge++){
    S1 = mesh.Edges[2*edge] ;
    S2 = mesh.Edges[2*edge+1] ;

    if((numSommet==S1)||(numSommet==S2)){
      Edges_Max[NEdges] = edge ;
      NEdges++ ;
    }
  }

  // Réaffectation dans un tableau de bonne taille
  tabEdges=(int*)malloc(NEdges*sizeof(int)) ;

  for(int edge=0 ; edge < NEdges ; edge++)
  tabEdges[edge] = Edges_Max[edge] ;

  // Libération du tableau intermédiaire
  free(Edges_Max) ;
}

/**
* @brief Procédure qui renvoie la liste des triangles dans lequel un sommet donné est engagé.
*
* @param[in] mesh Structure de maillage.
* @param[in] numSommet Numéro du sommet.
* @param tabTriangles Liste des triangles <b>non alloué</b> en entrée, <b>alloué</b> en sortie.
* @param NTriangles Nombres des triangles et taille de tabTriangles.
* @par Complexité
* Linéaire du nombre de triangles du maillage mesh.
*/
void NodeToTriangles(const struct maillage &mesh, const int numSommet, int* &tabTriangles, int &NTriangles){

  // Variables
  int S1, S2, S3     ; // Sommets candidats
  NTriangles=0       ; // Nombre de côtés effectifs
  int* Triangles_Max ; // Côtés effectifs

  // Tableau de taille maximale
  Triangles_Max=(int*)malloc(mesh.N_Triangles*sizeof(int)) ;

  // Recherche des cotés effectifs
  for(int triangle=0 ; triangle < mesh.N_Triangles ; triangle++){
    S1 = mesh.Triangles[3*triangle] ;
    S2 = mesh.Triangles[3*triangle+1] ;
    S3 = mesh.Triangles[3*triangle+2] ;

    if((numSommet==S1)||(numSommet==S2)||(numSommet==S3)){
      Triangles_Max[NTriangles] = triangle ;
      NTriangles++ ;
    }
  }

  // Réaffectation dans un tableau de bonne taille
  tabTriangles=(int*)malloc(NTriangles*sizeof(int)) ;

  for(int triangle=0 ; triangle < NTriangles ; triangle++)
  tabTriangles[triangle] = Triangles_Max[triangle] ;

  // Libération du tableau intermédiaire
  free(Triangles_Max) ;
}


void Triangle_to_its_neighbours(const struct maillage &mesh, const int numTriangle, int* &tabNeighbours, int &NTriangles)
{

  // Variables
  int S1, S2, S3                ; // Sommets du triangle
  int S1tilde, S2tilde, S3tilde ; // Sommets du triangle candidat
  NTriangles=0              ; // Nombre de triangles voisins effectifs
  int* Triangles_neighbours_Max ;

  // Tableau de taille maximale
  Triangles_neighbours_Max=(int*)malloc(3*sizeof(int)) ;

  // Recherche des triangles voisins
  for(int triangle=0 ; triangle < mesh.N_Triangles ; triangle++){
    S1tilde = mesh.Triangles[3*triangle] ;
    S2tilde = mesh.Triangles[3*triangle+1] ;
    S3tilde = mesh.Triangles[3*triangle+2] ;

    if (triangle != numTriangle)
    {
      if(((S1tilde==S1)||(S1tilde==S2)||(S1tilde==S3))&&((S2tilde==S1)||(S2tilde==S2)||(S2tilde==S3)))
      {
        Triangles_neighbours_Max[NTriangles] = triangle ;
        NTriangles++ ;
      }
      else if(((S1tilde==S1)||(S1tilde==S2)||(S1tilde==S3))&&((S3tilde==S1)||(S3tilde==S2)||(S3tilde==S3)))
      {
        Triangles_neighbours_Max[NTriangles] = triangle ;
        NTriangles++ ;
      }
      else if(((S2tilde==S1)||(S2tilde==S2)||(S2tilde==S3))&&((S3tilde==S1)||(S3tilde==S2)||(S3tilde==S3)))
      {
        Triangles_neighbours_Max[NTriangles] = triangle ;
        NTriangles++ ;
      }
    }
  }

  // Réaffectation dans un tableau de bonne taille
  tabNeighbours=(int*)malloc(NTriangles*sizeof(int)) ;

  for(int triangle=0 ; triangle < NTriangles ; triangle++)
  tabNeighbours[triangle] = Triangles_neighbours_Max[triangle] ;

  // Libération du tableau intermédiaire
  free(Triangles_neighbours_Max) ;
}


void Triangle_to_its_neighbours_sans_deja_vu(const struct maillage &mesh, const int numTriangle, int* &tabNeighbours, int &NTriangles, vector<int> &tabdejavu)
{
  // Variables
  int S1, S2, S3                ; // Sommets du triangle
  int S1tilde, S2tilde, S3tilde ; // Sommets du triangle candidat
  NTriangles=0              ; // Nombre de triangles voisins effectifs
  int* Triangles_neighbours_Max ;
  int dejavu                ;

  // Tableau de taille maximale
  Triangles_neighbours_Max=(int*)malloc(3*sizeof(int)) ;

  // Recherche des triangles voisins
  for(int triangle=0 ; triangle < mesh.N_Triangles ; triangle++){
    S1tilde = mesh.Triangles[3*triangle] ;
    S2tilde = mesh.Triangles[3*triangle+1] ;
    S3tilde = mesh.Triangles[3*triangle+2] ;

    //Vérification si le triangle a déjà été traité
    dejavu=0;
    for(int j=0; j<tabdejavu.size(); j++)
    {
      if (tabdejavu[j]==triangle)
      {
        dejavu=1;
      }
    }

    if ((triangle != numTriangle)&&(dejavu!=1))
    {
      if(((S1tilde==S1)||(S1tilde==S2)||(S1tilde==S3))&&((S2tilde==S1)||(S2tilde==S2)||(S2tilde==S3)))
      {
        Triangles_neighbours_Max[NTriangles] = triangle ;
        tabdejavu.push_back(triangle);
        NTriangles++ ;
      }
      else if(((S1tilde==S1)||(S1tilde==S2)||(S1tilde==S3))&&((S3tilde==S1)||(S3tilde==S2)||(S3tilde==S3)))
      {
        Triangles_neighbours_Max[NTriangles] = triangle ;
        tabdejavu.push_back(triangle);
        NTriangles++ ;
      }
      else if(((S2tilde==S1)||(S2tilde==S2)||(S2tilde==S3))&&((S3tilde==S1)||(S3tilde==S2)||(S3tilde==S3)))
      {
        Triangles_neighbours_Max[NTriangles] = triangle ;
        tabdejavu.push_back(triangle);
        NTriangles++ ;
      }
    }
  }

  // Réaffectation dans un tableau de bonne taille
  tabNeighbours=(int*)malloc(NTriangles*sizeof(int)) ;

  for(int triangle=0 ; triangle < NTriangles ; triangle++)
  	tabNeighbours[triangle] = Triangles_neighbours_Max[triangle] ;

  // Libération du tableau intermédiaire
  free(Triangles_neighbours_Max) ;
}


/**
* @brief Fonction testant l'appartenance géométrique d'un point à un triangle
* @param[in] mesh Structure de maillage.
* @param[in] numTriangle Numéro du triangle.
* @param[in] x Position selon x du point.
* @param[in] y Position selon y du point.
* @result Booléen T/F
*
* @par Théorie et Algorithmie
* L'algorithme se base sur le calcul des coordonnées locales du point \f$P(x,y)\f$ dans le triangle numéro `numTriangle`. <br>
* Le calcul global est effectué à partir de 4 déterminant de matrices de format \f$2\times2\f$. <br>
* Le point est dans le triangle si et seulement si ses 3 coordonnées locales sont positives ou nulles.
*
* @par Complexité
* Temps constant.
*/
bool IsPointInTriangle(const struct maillage &mesh, const int numTriangle, const double x, const double y){

  // Chargement des données relatives aux sommet du triangle
  int S1, S2, S3 ;
  TriangleToNodes(mesh, numTriangle, S1, S2, S3) ;

  double S1x, S1y, S2x, S2y, S3x, S3y ;
  S1x = mesh.Vertices[2*(S1-1)];
  S1y = mesh.Vertices[2*(S1-1)+1];
  S2x = mesh.Vertices[2*(S2-1)];
  S2y = mesh.Vertices[2*(S2-1)+1];
  S3x = mesh.Vertices[2*(S3-1)];
  S3y = mesh.Vertices[2*(S3-1)+1];

  //  double de l'aire signée du triangle (S1, S2, S3)
  double Daire = ((S2x-S1x)*(S3y-S1y)-(S3x-S1x)*(S2y-S1y));
  double lambda1, lambda2, lambda3 ;

  // lambda1 = aire(P, S2, S3)/aire(S1, S2, S3)
  lambda1 = ((S2x-x)*(S3y-y)-(S3x-x)*(S2y-y))/Daire ;

  // lambda2 = aire(S1, P, S3)/aire(S1, S2, S3)
  lambda2 = ((x-S1x)*(S3y-S1y)-(S3x-S1x)*(y-S1y))/Daire;

  // lambda3 = aire(S1, S2, P)/aire(S1, S2, S3)
  lambda3 = ((S2x-S1x)*(y-S1y)-(x-S1x)*(S2y-S1y))/Daire;

  if((lambda1>=0.0)&&(lambda2>=0.0)&&(lambda3>=0.0))
  return true ;
  else
  return false ;
}

/**
* @brief Fonction qui ajoute le sommet i du maillage initiale dans le maillage final
* @param[in] sommet Numéro du sommet du maillage initial.
* @param[in] mesh_Initial Maillage initial.
* @param[in] mesh_Final Maillage final.
*/
void AjoutePoint(const int sommet, const struct maillage & mesh_Initial, struct maillage & mesh_Final){

  // Déclarations ////////////////////////////////////////////////////
  vector<int> couple ;         // Contient toutes les pairs de couples.
  vector<int> nombreFoisSupp ; // contient des labels pour dire si un couple doit être supprimé ou pas.

  vector<int> numTriangle ;    // Liste des triangles à supprimer
  int nbTriangles(0) ;         // Nombre de triangles à supprimer

  double sommet_x = mesh_Initial.Vertices[2*(sommet-1)] ;
  double sommet_y = mesh_Initial.Vertices[2*(sommet-1)+1] ;

  // Balayage des triangles pour tester le critère de Delaunay ///////
  for(int triangle=0 ; triangle < mesh_Final.N_Triangles ; triangle++){

    // Stock si le point sommet du maillage initial est dans la boule du triangle triangle du maillage Final
    int inBouleTriangle=Admissibilite(sommet_x, sommet_y, triangle, mesh_Final) ;

    if(inBouleTriangle==-1){ // Si le point est dans la boule

      //Sommet du triangle
      int S1 = mesh_Final.Triangles[3*triangle] ;
      int S2 = mesh_Final.Triangles[3*triangle+1] ;
      int S3 = mesh_Final.Triangles[3*triangle+2] ;

      // S1 S2
      treatCouple(min(S1,S2), max(S1,S2), couple, nombreFoisSupp) ;

      // S1 S3
      treatCouple(min(S1,S3), max(S1,S3), couple, nombreFoisSupp) ;

      // S2 S3
      treatCouple(min(S2,S3), max(S2,S3), couple, nombreFoisSupp) ;

      // On stock le triangle comme étant à supprimer
      numTriangle.push_back(triangle) ;
      nbTriangles++ ;
    }
  }

  // ÉCRITURE DES NOUVEAUX TRIANGLES

  // Réécriture sur les triangles à supprimer + les derniers triangles finaux
  int numRemplacement(0) ;

  // On balaye les couples pour voir ceux qui sont à garder
  for(int numcouple=0 ; numcouple<nombreFoisSupp.size() ; numcouple++){

    // Si on garde ce couple pour un nouveau triangle
    if(nombreFoisSupp[numcouple]==1){

      // Sommets basé sur ce couple et le sommet à ajouter dans la triangulation.
      int S1 = couple[2*numcouple] ;
      int S2 = couple[2*numcouple+1] ;
      int S3 = mesh_Final.N_Vertices+1 ;

      if(numRemplacement<nbTriangles){
        // On écrase le numRemplacement triangle à supprimer
        mesh_Final.Triangles[3*numTriangle[numRemplacement]] = S1 ;
        mesh_Final.Triangles[3*numTriangle[numRemplacement]+1] = S2 ;
        mesh_Final.Triangles[3*numTriangle[numRemplacement]+2] = S3 ;
      }else{
        // On ajoute les derniers triangles
        mesh_Final.Triangles.push_back(S1) ;
        mesh_Final.Triangles.push_back(S2) ;
        mesh_Final.Triangles.push_back(S3) ;

        // Ajout de triangles supplémentaires
        mesh_Final.N_Triangles++ ;
      }
      numRemplacement++ ;
    }
  }
  // Le point à été ajouté
  mesh_Final.Vertices.push_back(sommet_x) ;
  mesh_Final.Vertices.push_back(sommet_y) ;
  mesh_Final.N_Vertices++ ;
}

/**
* @brief Fonction qui ajoute au vecteur couple S1 et S2 s'il n'est pas présent. Augmente de 1 status sinon.
* @param[in] S1 Premier numéro de sommet.
* @param[in] S1 Second numéro de sommet.
* @param[in] couple Vecteur des couples.
* @param[in] status Vecteur donnant un status 1 si le couple est unique ou 2 s'il est déjà présent dans le vecteur couple.
*/
void treatCouple(const int S1, const int S2, vector<int> &couple, vector<int> & status){
  int taille=couple.size()/2 ;
  bool deja = false ;

  for(int i=0 ; i< taille ; i++){
    if((S1==couple[2*i])&&(S2==couple[2*i+1])){
      status[i]=2 ;
      deja = true ;
    }
  }


  if(not(deja)){
    // Le couple n'est pas présent
    couple.push_back(S1) ;
    couple.push_back(S2) ;
    status.push_back(1) ;
  }
}

/**
* @brief Procédure qui renverse l'arrête entre 2 triangles s'ils sont voisins
* @param[in] t1 Numéro du premier triangle.
* @param[in] t2 Numéro du second triangle.
* @param[inout] mesh Structure de maillage.
* \par Théorie
* La fonction renverse l'arrête qui sépare les 2 triangles s'ils sont voisins. S'ils ne le sont pas, rien ne se produit.
*/
void swap(const int t1, const int t2, struct maillage &mesh){

  int placeS1iDans2[3] ={-1,-1,-1} ;

  for(int i=0; i<3 ; i++){
    for(int j=0 ; j<3 ; j++){
      if(mesh.Triangles[3*t1+i] == mesh.Triangles[3*t2+j]) // S1i = S2j
      placeS1iDans2[i]=j ;
    }
  }

  // Vérification qu'il n'y a que 1 seul indice -1
  int compteur(0) ;
  for(int k=0 ; k<3 ; k++){
    if(placeS1iDans2[k]==-1)
    compteur++ ;
  }

  if(compteur==1){ // Alors on a bien des triangles voisins

    // Récupération du sommet S1i à replacer
    int i=0 ;
    while(placeS1iDans2[i]!=-1){
      i++ ;
    }

    // Test si le sommet j est dans le tableau placeS1i dans 2
    bool SjInTab[3] ;
    for(int j=0; j<3 ; j++)
    SjInTab[j]=(placeS1iDans2[0]== j)||(placeS1iDans2[1]== j)||(placeS1iDans2[2]== j) ;

    // Récupération du sommet j du triangle 2 a replacer
    int j=0 ;
    while(SjInTab[j]){
      j++ ;
    }

    // On écrase i+1 par j
    mesh.Triangles[3*t1+((i+1)%3)]= mesh.Triangles[3*t2+j] ;
    // On écrase l'autre noeud commun dans T2
    mesh.Triangles[3*t2+(placeS1iDans2[(i+2)%3])] =  mesh.Triangles[3*t1+i] ;
  }
}

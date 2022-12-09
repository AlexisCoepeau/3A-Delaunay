#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>

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
    int N_Vertices ;

	/**
	 * @brief Tableau des sommets du maillage
	 * @details Le tableau de sommets est de taille 2 N_vertices. Il contient les coordonnées de chaque sommets du maillage :
	 * <table>
	 * <tr style="text-align:center"> <td> Indice : </td> <td> </td>  <td> \f$\cdots\f$ </td> <td> \f$2i\f$ </td> <td> \f$2i+1\f$ </td> <td> \f$\cdots\f$ </td> </tr>
	 * <tr style="text-align:center"> <td> Vertices : </td> <td> </td> <td> \f$\cdots\f$ </td> <td> \f$x_i\f$ </td> <td> \f$y_i\f$ </td> <td> \f$\cdots\f$ </td> </tr>
	 * </table>
	*/
	double * Vertices;

	/** @brief Nombre de segments du maillage */
    int N_Edges ;
	/**
	 * @brief Tableau des segments du maillage
	 * @details Le tableau de segments est de taille 2 N_Edges. Il est contient le numéro des sommets pour chaque segment du maillage :
	 * <table>
	 * <tr style="text-align:center"> <td> Indice : </td> <td> </td>  <td> \f$\cdots\f$ </td> <td> \f$2i\f$ </td> <td> \f$2i+1\f$ </td> <td> \f$\cdots\f$ </td> </tr>
	 * <tr style="text-align:center"> <td> Edges : </td> <td> </td> <td> \f$\cdots\f$ </td> <td> \f$S_1\f$ </td> <td> \f$S_2\f$ </td> <td> \f$\cdots\f$ </td> </tr>
	 * </table>
	*/
	int * Edges;
	// Triangle entre trois sommets numérotés

	/** @brief Nombre de triangles du maillage */
    int N_Triangles ;
	/**
	 * @brief Tableau des triangles du maillage
	 * @details Le tableau de triangles est de taille 2 N_Triangles. Il est contient le numéro des sommets pour chaque triangles du maillage :
	 * <table>
	 * <tr style="text-align:center"> <td> Indice : </td> <td> </td>  <td> \f$\cdots\f$ </td> <td> \f$3i\f$ </td> <td> \f$3i+1\f$ </td> <td> \f$3i+2\f$ </td>  <td> \f$\cdots\f$ </td> </tr>
	 * <tr style="text-align:center"> <td> Triangles : </td> <td> </td> <td> \f$\cdots\f$ </td> <td> \f$S_1\f$ </td> <td> \f$S_2\f$ </td> <td> \f$S_3\f$ </td> <td> \f$\cdots\f$ </td> </tr>
	 * </table>
	*/
	int * Triangles;
    int N_Corners ;
    int * Corners;
	int N_Ridges ;
    int * Ridges;
};

/* PROTOTYPES */

double Distance2D(const double, const double, const double, const double) ;
double Qualite2D(const int, const struct maillage) ;
int admissibilite(double x, double y, int i, struct maillage mesh) ;
void cercle(int i, struct maillage mesh, double x, double y) ;
void Chargement(const char*, struct maillage*) ;
void TriangleToNodes(const struct maillage &, const int, int &, int &, int &);
void EdgeToNodes(const struct maillage &, const int, int &, int &) ;
int Admissibilite(const double, const double, const int, const struct maillage) ;
void free(struct maillage) ;
void NodeToEdges(const struct maillage &, const int, int* &, int &) ;
void NodeToTriangles(const struct maillage &, const int, int* &, int &);
bool IsPointInTriangle(const struct maillage &, const int, const double, const double) ;

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


	//Affichage de la qualité
	// for(int i=0; i<2; i++)
	// {
	// 	cout << "-------------------------------------------------------" << endl;
	// 	cout << "Qualité triangle " << i << "=" << Qualite2D(i, mesh_Initial) << endl;
	// }

	// cercle(1, mesh_Initial, 3.0, 2.5);
  // cout << "Admissibilité = " << Admissibilite(3.0, 2.5, 1, mesh_Initial) << endl;
  // cercle(1, mesh_Initial, 3.0, 13.0);
  // cout << "Admissibilité = " << Admissibilite(3.0, 13.0, 1, mesh_Initial) << endl;
  // cercle(1, mesh_Initial, 3.0, 7.0);
  // cout << "Admissibilité = " << Admissibilite(3.0, 7.0, 1, mesh_Initial) << endl;

  //Test Delaunay






	//On est sur le triangle contenant le point initial donc il est forcement noté -1
	/*for (arretes du triangle contenant le point noté -1)
		Tant qu'on ne tombe pas sur un triangle ayant deux voisins noté 0 on continue à aller sur ses triangles voisins
			fonction(sur nouveau triangle)
			Tant qu'on ne tombe pas sur un triangle ayant deux voisins noté 0 on continue à aller sur ses triangles voisins
				fonction(sur nouveau triangle)*/

	free(mesh_Initial) ;

	return 0;
}

/* CONTAINS */

/**
 * @brief Fonction `free` surchargée pour la libération mémoire d'un maillage.
 * @details Fonction qui libère la mémoire allouée lors de la génération des chaps d'un maillage.
 * @param mesh Structure de maillage.
 * @sa maillage
 */
void free(struct maillage mesh){
	free(mesh.Vertices) ;
	free(mesh.Edges) ;
	free(mesh.Triangles) ;
	free(mesh.Corners) ;
	free(mesh.Ridges) ;
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
double Qualite2D(const int numTriangle, const struct maillage mesh)
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
				mesh->Vertices = (double*)malloc(sizeof(double)*(2*mesh->N_Vertices));

				for(int i=0; i<mesh->N_Vertices; i++)
				{
					monFlux >> mesh->Vertices[2*i];
					monFlux >> mesh->Vertices[2*i+1];

					monFlux >> indice;
				}
			}
			if(ligne=="Edges")
			{
				monFlux >> mesh->N_Edges;
				mesh->Edges = (int*)malloc(sizeof(int)*(2*mesh->N_Edges));

				for(int i=0; i<mesh->N_Edges; i++)
				{
					monFlux >> mesh->Edges[2*i];
					monFlux >> mesh->Edges[2*i+1];

					monFlux >> indice;
				}
			}
			if(ligne=="Triangles")
			{
				monFlux >> mesh->N_Triangles;
				mesh->Triangles = (int*)malloc(sizeof(int)*(3*mesh->N_Triangles));

				for(int i=0; i<mesh->N_Triangles; i++)
				{
					monFlux >> mesh->Triangles[3*i];
					monFlux >> mesh->Triangles[3*i+1];
					monFlux >> mesh->Triangles[3*i+2];

					monFlux >> indice;
				}
			}
			if(ligne=="Corners")
			{
				monFlux >> mesh->N_Corners;
				mesh->Corners = (int*)malloc(sizeof(int)*(mesh->N_Corners));

				for(int i=0; i<mesh->N_Corners; i++)
				{
					monFlux >> mesh->Corners[i];
				}
			}
			if(ligne=="Ridges")
			{
				monFlux >> mesh->N_Ridges ;
				mesh->Ridges = (int*)malloc(sizeof(int)*(mesh->N_Ridges));

				for(int i=0; i<mesh->N_Ridges; i++)
				{
					monFlux >> mesh->Ridges[i];
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
int Admissibilite(const double x, const double y, const int numTriangle, const struct maillage mesh)
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



void cercle(int i, struct maillage mesh, double x, double y)
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
	S1x = mesh.Vertices[2*S1];
	S1y = mesh.Vertices[2*S1+1];
	S2x = mesh.Vertices[2*S2];
	S2y = mesh.Vertices[2*S2+1];
	S3x = mesh.Vertices[2*S3];
	S3y = mesh.Vertices[2*S3+1];

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

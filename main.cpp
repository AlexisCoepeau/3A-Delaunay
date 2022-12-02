#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>

using namespace std;

struct maillage
{
	// Localisation des sommets
	/** @brief Nombre de sommets du maillage */ 
    int N_Vertices ;

	/** 
	 * @brief Tableau des sommets
	 * @details Le tableau de sommets est de taille 2 N_vertices. Il est construit comme :
	 * <table>
	 * <tr style="text-align:center"> <td> indice : </td> <td> </td>  <td> \f$\cdots\f$ </td> <td> \f$2i\f$ </td> <td> \f$2i+1\f$ </td> <td> \f$\cdots\f$ </td> </tr>
	 * <tr style="text-align:center"> <td> Vertices : </td> <td> </td> <td> \f$\cdots\f$ </td> <td> \f$x_i\f$ </td> <td> \f$y_i\f$ </td> <td> \f$\cdots\f$ </td> </tr>
	 * </table>
	*/
	double * Vertices;
	// Segment entre deux sommets numérotés
	/** @brief Nombre de cotés du maillage */
    int N_Edges ;

	/** 
	 * @brief Tableau des sommets
	 * @details Le tableau de sommets est de taille 2 N_vertices. Il est construit comme :
	 * <table>
	 * <tr style="text-align:center"> <td> indice : </td> <td> </td>  <td> \f$\cdots\f$ </td> <td> \f$2i\f$ </td> <td> \f$2i+1\f$ </td> <td> \f$\cdots\f$ </td> </tr>
	 * <tr style="text-align:center"> <td> Vertices : </td> <td> </td> <td> \f$\cdots\f$ </td> <td> \f$x_i\f$ </td> <td> \f$y_i\f$ </td> <td> \f$\cdots\f$ </td> </tr>
	 * </table>
	*/
	int * Edges;
	// Triangle entre trois sommets numérotés
	/** @brief Nombre de triangles du maillage */
    int N_Triangles ;
	/** @brief Tableau des triangles du maillage */
	int * Triangles;
    int N_Corners ;
    int * Corners;
	int N_Ridges ;
    int * Ridges;
};

/* PROTOTYPES */

double Distances2D(const double, const double, const double, const double) ;
double Qualite2D(const int, const struct maillage) ;
void Chargement(const char*, struct maillage*) ;


/**
 * @brief Fonction principale
 * @details Usage : ./main <fichier.mesh>
 * 
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
	struct maillage mesh;

	// Chargement des données de maillage
	Chargement(argv[1], &mesh) ;


	//Affichage de la qualité
	for(int i=0; i<2; i++)
	{
		cout << "-------------------------------------------------------" << endl;
		cout << "Qualité triangle " << i << "=" << Qualite2D(i, mesh) << endl;
	}

	//On est sur le triangle contenant le point initial donc il est forcement noté -1
	for (arretes du triangle contenant le point noté -1)
		Tant qu'on ne tombe pas sur un triangle ayant deux voisins noté 0 on continue à aller sur ses triangles voisins
			fonction(sur nouveau triangle)
			Tant qu'on ne tombe pas sur un triangle ayant deux voisins noté 0 on continue à aller sur ses triangles voisins
				fonction(sur nouveau triangle)


	return 0;
}



/* CONTAINS */
/**
 * @brief Fonction renvoyant la distance euclidienne en 2 dimensions entre 2 points.
 * @param[in] x1 Position selon x du point 1.
 * @param[in] y1 Position selon y du point 1.
 * @param[in] x2 Position selon x du point 2.
 * @param[in] y2 Position selon y du point 2.
 * @par Théorie et Algorithmie
 * \f$ distance = \sqrt{(x_1-x_2)^2+(y_1-y_2)^2}\f$
*/
double Distance2D(const double x1, const double y1, const double x2, const double y2)
{
	double dist=0.0;

	dist=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));

	return dist;
}

/**
 * @brief Fonction calculant la qualité d'un triangle numéro \f$i\f$ pour un maillage donné.
 * @param[in] i numéro du triangle.
 * @param[in] mesh maillage.
 * @par Théorie et Algorithmie
 * Si on note \f$S_1(x_1,y_1), S_2(x_2,y_2)\f$ et \f$S_3(x_3,y_3)\f$ les sommets du triangle considéré, 
 * <ul>
 * <li> \f$aire = \frac{1}{2}\begin{vmatrix} x_2-x_1 & x_3-x_1 \\ y_2-y_1 & y_3-y_1 \end{vmatrix}\f$</li>
 * <li> \f$Qualité = \frac{\sqrt{3}}{12} \frac{S_1S_2^2+S_1S_3^2+S_2S_3^2}{aire}\f$ </li>
 * </ul>
*/
double Qualite2D(const int i, const struct maillage mesh)
{
	double Q, aire, s1x, s1y, s2x, s2y, s3x, s3y;
	s1x = mesh.Vertices[(mesh.Triangles[3*i]-1)*2];
	s1y = mesh.Vertices[(mesh.Triangles[3*i]-1)*2+1];
	s2x = mesh.Vertices[(mesh.Triangles[3*i+1]-1)*2];
	s2y = mesh.Vertices[(mesh.Triangles[3*i+1]-1)*2+1];
	s3x = mesh.Vertices[(mesh.Triangles[3*i+2]-1)*2];
	s3y = mesh.Vertices[(mesh.Triangles[3*i+2]-1)*2+1];

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
 * @param[in] fichier Fichier de données au format `.mesh`
 * @param[out] mesh Structure maillage
 * 
 * @warning
 * La procédure arrête le programme avec `EXIT_FAILURE` si le fichier ne peut pas être ouvert.
 * 
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
					monFlux >> mesh->Edges[i];
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

int admissibilite(double x, double y, int i, struct maillage mesh)
{
	//Sommets du triangle i
	double s1x, s1y, s2x, s2y, s3x, s3y;
	s1x = mesh.Vertices[(mesh.Triangles[3*i]-1)*2];
	s1y = mesh.Vertices[(mesh.Triangles[3*i]-1)*2+1];
	s2x = mesh.Vertices[(mesh.Triangles[3*i+1]-1)*2];
	s2y = mesh.Vertices[(mesh.Triangles[3*i+1]-1)*2+1];
	s3x = mesh.Vertices[(mesh.Triangles[3*i+2]-1)*2];
	s3y = mesh.Vertices[(mesh.Triangles[3*i+2]-1)*2+1];
	//Propriétés du cercle circonscrit au triangle
	double a, b, c, d, e, f, xcentre, ycentre, rayon
	//Distance entre le point et le centre du cercle circonscrit
	double dist=0.0;
	//Admissible -1 si ne respecte pas le critère de Delaunay et 0 sinon
	int Delaunay=0;

	a = s2x - s1x;
	b = s2y - s1y;
	c = s3x - s1x;
	d = s3y - s1y;
	e = s2x*s2x - s1x*s1x + s2y*s2x - s1y*s1y;
	f = s3x*s3x - s1x*s1x + s3y*s3y - s1y*s1y;
	g = -(1./(2.*(a*d-b*c));

	xcentre = g*( d*e - b*f);
	ycentre = g*(-c*e + a*f);

	rayon = Distance2D(xcentre,ycentre,s1x,s1y);

	dist  = Distance2D(xcentre,ycentre,x,y);

	if (dist<rayon)
	{
		Delaunay=-1;
	}

	return Delaunay;
}

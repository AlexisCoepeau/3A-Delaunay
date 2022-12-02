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
    int N_Vertices ;
	double * Vertices;
	// Segment entre deux sommets numérotés
    int N_Edges ;
	int * Edges;
	// Triangle entre trois sommets numérotés
    int N_Triangles ;
	int * Triangles;
    int N_Corners ;
    int * Corners;
	int N_Ridges ;
    int * Ridges;
};

/* PROTOTYPES */

double distances2D(const double, const double, const double, const double) ;
double Qualite2D(const int, const struct maillage) ;
int admissibilite(double x, double y, int i, struct maillage mesh) ;
void cercle(double *x, double *y, int N, int i, struct maillage mesh) ;


/* Fonction principale
 *
 * Usage : ./main <fichier.mesh>
 *
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

    //if(argv[1])

	ifstream monFlux(argv[1]); // "/home/guillaume/Bureau/Enseirb_Matmeca/CHP2/Technique/TP1/meshes/2D/square_disc.mesh"
	struct maillage mesh;
	string ligne;
	int N, indice;

	if(monFlux)
	{
		while(getline(monFlux,ligne))
		{
			if(ligne=="Vertices")
			{
				monFlux >> mesh.N_Vertices; // Nombre de sommets
				mesh.Vertices = (double*)malloc(sizeof(double)*(2*N));

				for(int i=0; i<mesh.N_Vertices; i++)
				{
					monFlux >> mesh.Vertices[2*i];
					monFlux >> mesh.Vertices[2*i+1];

					monFlux >> indice;
				}
			}
			if(ligne=="Edges")
			{
				monFlux >> mesh.N_Edges;
				mesh.Edges = (int*)malloc(sizeof(int)*(2*N));

				for(int i=0; i<mesh.N_Edges; i++)
				{
					monFlux >> mesh.Edges[i];
					monFlux >> mesh.Edges[2*i+1];

					monFlux >> indice;
				}
			}
			if(ligne=="Triangles")
			{
				monFlux >> mesh.N_Triangles;
				mesh.Triangles = (int*)malloc(sizeof(int)*(3*N));

				for(int i=0; i<mesh.N_Triangles; i++)
				{
					monFlux >> mesh.Triangles[3*i];
					monFlux >> mesh.Triangles[3*i+1];
					monFlux >> mesh.Triangles[3*i+2];

					monFlux >> indice;
				}
			}
			if(ligne=="Corners")
			{
				monFlux >> mesh.N_Corners;
				mesh.Corners = (int*)malloc(sizeof(int)*(N));

				for(int i=0; i<mesh.N_Corners; i++)
				{
					monFlux >> mesh.Corners[i];
				}
			}
			if(ligne=="Ridges")
			{
				monFlux >> mesh.N_Ridges ;
				mesh.Ridges = (int*)malloc(sizeof(int)*(N));

				for(int i=0; i<mesh.N_Ridges; i++)
				{
					monFlux >> mesh.Ridges[i];
				}
			}
		}
		monFlux.close();

			cout << "yo" << endl;
		//Affichage de la qualité
		for(int i=0; i<2; i++)
		{
			cout << "-------------------------------------------------------" << endl;
			cout << "Qualité triangle " << i << "=" << Qualite2D(i, mesh) << endl;
		}
			cout << "yo" << endl;
	}

	//On est sur le triangle contenant le point initial donc il est forcement noté -1
	// for (arretes du triangle contenant le point noté -1)
	// 	Tant qu'on ne tombe pas sur un triangle ayant deux voisins noté 0 on continue à aller sur ses triangles voisins
	// 		fonction(sur nouveau triangle)
	// 		Tant qu'on ne tombe pas sur un triangle ayant deux voisins noté 0 on continue à aller sur ses triangles voisins
	// 			fonction(sur nouveau triangle)

	//Test cercle et Delaunay
	double *x, *y;
	cercle(x, y, 100, 4, mesh);

	ofstream monFlux2("cercle.dat");
	for (int i=0; i<=N; i++)
	{
		monFlux2 << x[i] << y[i] << endl;
	}





	return 0;
}



/* CONTAINS */
double distance2D(const double x1, const double y1, const double x2, const double y2)
{
	double dist=0.0;

	dist=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));

	return dist;
}

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

	Q = (sqrt(3.0)/(12.0*aire))*(distance2D(s1x, s1y, s2x, s2y)+distance2D(s1x, s1y, s3x, s3y)+distance2D(s3x, s3y, s2x, s2y));

	return Q;
}

int admissibilite(double x, double y, int i, struct maillage mesh)
{
	//Sommets du triangle i
	double s1x, s1y, s2x, s2y, s3x, s3y;
	// s1x = mesh.Vertices[(mesh.Triangles[3*i]-1)*2];
	// s1y = mesh.Vertices[(mesh.Triangles[3*i]-1)*2+1];
	// s2x = mesh.Vertices[(mesh.Triangles[3*i+1]-1)*2];
	// s2y = mesh.Vertices[(mesh.Triangles[3*i+1]-1)*2+1];
	// s3x = mesh.Vertices[(mesh.Triangles[3*i+2]-1)*2];
	// s3y = mesh.Vertices[(mesh.Triangles[3*i+2]-1)*2+1];
	s1x = 3.0;
	s1y = 2.8;
	s2x = 3.72;
	s2y = 2.76;
	s3x = 0.145;
	s3y = 4.314;

	//Propriétés du cercle circonscrit au triangle
	double a, b, c, d, e, f, g, xcentre, ycentre, rayon;
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
	g = -(1./(2.*(a*d-b*c)));

	xcentre = g*( d*e - b*f);
	ycentre = g*(-c*e + a*f);

	rayon = distance2D(xcentre,ycentre,s1x,s1y);

	dist  = distance2D(xcentre,ycentre,x,y);

	if (dist<rayon)
	{
		Delaunay=-1;
	}

	return Delaunay;
}

void cercle(double *x, double *y, int N, int i, struct maillage mesh)
{
	//Sommets du triangle i
	double s1x, s1y, s2x, s2y, s3x, s3y;
	// s1x = mesh.Vertices[(mesh.Triangles[3*i]-1)*2];
	// s1y = mesh.Vertices[(mesh.Triangles[3*i]-1)*2+1];
	// s2x = mesh.Vertices[(mesh.Triangles[3*i+1]-1)*2];
	// s2y = mesh.Vertices[(mesh.Triangles[3*i+1]-1)*2+1];
	// s3x = mesh.Vertices[(mesh.Triangles[3*i+2]-1)*2];
	// s3y = mesh.Vertices[(mesh.Triangles[3*i+2]-1)*2+1];
	s1x = 3.0;
	s1y = 2.8;
	s2x = 3.72;
	s2y = 2.76;
	s3x = 0.145;
	s3y = 4.314;

	//Propriétés du cercle circonscrit au triangle
	double a, b, c, d, e, f, g, xcentre, ycentre, rayon;
	//Distance entre le point et le centre du cercle circonscrit
	double dist=0.0;
	//Admissible -1 si ne respecte pas le critère de Delaunay et 0 sinon
	int Delaunay=0;
	double theta;

	a = s2x - s1x;
	b = s2y - s1y;
	c = s3x - s1x;
	d = s3y - s1y;
	e = s2x*s2x - s1x*s1x + s2y*s2x - s1y*s1y;
	f = s3x*s3x - s1x*s1x + s3y*s3y - s1y*s1y;
	g = -(1./(2.*(a*d-b*c)));

	xcentre = g*( d*e - b*f);
	ycentre = g*(-c*e + a*f);

	rayon = distance2D(xcentre,ycentre,s1x,s1y);
	theta = 2*(4*atan(1))/N;
	for (int i=0; i<=N; i++)
	{
		x[i]=xcentre + rayon*cos(i*theta);
		y[i]=ycentre + rayon*sin(i*theta);
	}
}

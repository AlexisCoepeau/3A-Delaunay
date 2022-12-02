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
	double * Vertices;
	// Segment entre deux sommets numérottés
	int * Edges;
	// Triangle entre trois sommets numérottés
	int * Triangles;
	int * Corners;
	int * Ridges;
};


double distance2D(double x1, double y1, double x2, double y2)
{
	double dist=0.0;

	dist=sqrt(pow(x1-x2,2)+pow(y1-y2,2));

	return dist;
}

double Qualite2D(int i, struct maillage mesh)
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

int main(int argc, char* argv[])
{
	ifstream monFlux("/home/guillaume/Bureau/Enseirb_Matmeca/CHP2/Technique/TP1/meshes/2D/square_disc.mesh");
	struct maillage mesh;
	string ligne;
	int N, indice;


	if(monFlux)
	{
		while(getline(monFlux,ligne))
		{
			if(ligne=="Vertices")
			{
				monFlux >> N;
				mesh.Vertices = (double*)malloc(sizeof(double)*(2*N));

				for(int i=0; i<N; i++)
				{
					monFlux >> mesh.Vertices[2*i];
					monFlux >> mesh.Vertices[2*i+1];

					monFlux >> indice;
				}
			}
			if(ligne=="Edges")
			{
				monFlux >> N;
				mesh.Edges = (int*)malloc(sizeof(int)*(2*N));

				for(int i=0; i<N; i++)
				{
					monFlux >> mesh.Edges[i];
					monFlux >> mesh.Edges[2*i+1];

					monFlux >> indice;
				}
			}
			if(ligne=="Triangles")
			{
				monFlux >> N;
				mesh.Triangles = (int*)malloc(sizeof(int)*(3*N));

				for(int i=0; i<N; i++)
				{
					monFlux >> mesh.Triangles[3*i];
					monFlux >> mesh.Triangles[3*i+1];
					monFlux >> mesh.Triangles[3*i+2];

					monFlux >> indice;
				}
			}
			if(ligne=="Corners")
			{
				monFlux >> N;
				mesh.Corners = (int*)malloc(sizeof(int)*(N));

				for(int i=0; i<N; i++)
				{
					monFlux >> mesh.Corners[i];
				}
			}
			if(ligne=="Ridges")
			{
				monFlux >> N;
				mesh.Ridges = (int*)malloc(sizeof(int)*(N));

				for(int i=0; i<N; i++)
				{
					monFlux >> mesh.Ridges[i];
				}
			}
		}
		monFlux.close();

		//Affichage de la qualité
		for(int i=0; i<2; i++)
		{
			cout << "-------------------------------------------------------" << endl;
			cout << "Qualité triangle " << i << "=" << Qualite2D(i, mesh) << endl;
		}
	}

	return 0;
}

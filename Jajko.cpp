#include "Jajko.h"



Jajko::Jajko()
{
	const int N = 30;
	point tab_wsp[N + 1][N + 1];
	point tab_znorm_wekt_wsp[N + 1][N + 1];
	point tab_tekstur[N + 1][N + 1];

	float x_u, x_v, y_u, y_v, z_u, z_v;
	float n_x, n_y, n_z;
	float dlug_wek, znrm_x, znrm_y, znrm_z;

	for (int j = 0; j < N + 1; j++)
	{
		for (int i = 0; i < N + 1; i++)
		{
			tab_wsp[i][j].x = ((1 / (double)N)*i);
			tab_wsp[i][j].y = ((1 / (double)N)*j);
		}
	}

	for (int i = 0; i < N + 1; i++)
	{
		for (int j = 0; j < N + 1; j++)
		{
			float u = tab_wsp[i][j].x;
			float v = tab_wsp[i][j].y;
			tab_tekstur[i][j].x = v;
			tab_tekstur[i][j].y = u;

			tab_wsp[i][j].x = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u)*cos(pi*v);
			tab_wsp[i][j].y = 160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2);
			tab_wsp[i][j].z = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u)*sin(pi*v);


			x_u = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * cos(pi * v);
			x_v = pi * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * sin(pi * v);

			y_u = 640 * pow(u, 3) - 960 * pow(u, 2) + 320 * u;
			y_v = 0;

			z_u = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * sin(pi * v);
			z_v = -pi * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * cos(pi * v);

			n_x = y_u * z_v - z_u * y_v;
			n_y = z_u * x_v - x_u * z_v;
			n_z = x_u * y_v - y_u * x_v;

			dlug_wek = sqrt(pow(n_x, 2) + pow(n_y, 2) + pow(n_z, 2));

			znrm_x = n_x / dlug_wek;
			znrm_y = n_y / dlug_wek;
			znrm_z = n_z / dlug_wek;

			if (u > 0.5)
			{
				tab_znorm_wekt_wsp[i][j].x = znrm_x * (-1);
				tab_znorm_wekt_wsp[i][j].y = znrm_y * (-1);
				tab_znorm_wekt_wsp[i][j].z = znrm_z * (-1);
			}
			else
			{
				tab_znorm_wekt_wsp[i][j].x = znrm_x;
				tab_znorm_wekt_wsp[i][j].y = znrm_y;
				tab_znorm_wekt_wsp[i][j].z = znrm_z;
			}


		}
	}

	glTranslated(0.0, -5.0, 0.0);

	if (model_jajka == 1)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				glColor3f(1.0f, 1.0f, 0.0f);
				glBegin(GL_POINTS);
				glVertex3f(tab_wsp[i][j].x, tab_wsp[i][j].y, tab_wsp[i][j].z);
				glEnd();
			}
		}
	}
	if (model_jajka == 2)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				glColor3f(1.0f, 1.0f, 0.0f);
				glBegin(GL_LINES);
				glVertex3f(tab_wsp[i][j].x, tab_wsp[i][j].y, tab_wsp[i][j].z);
				glVertex3f(tab_wsp[i + 1][j].x, tab_wsp[i + 1][j].y, tab_wsp[i + 1][j].z);
				glEnd();
			}
		}
	}

	if (model_jajka == 3)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				//glColor3ub(rand() % 256, rand() % 256, rand() % 256);
				glBegin(GL_TRIANGLES);

				glNormal3f(tab_znorm_wekt_wsp[i][j].x, tab_znorm_wekt_wsp[i][j].y, tab_znorm_wekt_wsp[i][j].z);
				glTexCoord2f(tab_tekstur[i][j].x, tab_tekstur[i][j].y);
				glVertex3f(tab_wsp[i][j].x, tab_wsp[i][j].y, tab_wsp[i][j].z);

				glNormal3f(tab_znorm_wekt_wsp[i + 1][j].x, tab_znorm_wekt_wsp[i + 1][j].y, tab_znorm_wekt_wsp[i + 1][j].z);
				glTexCoord2f(tab_tekstur[i + 1][j].x, tab_tekstur[i + 1][j].y);
				glVertex3f(tab_wsp[i + 1][j].x, tab_wsp[i + 1][j].y, tab_wsp[i + 1][j].z);

				glNormal3f(tab_znorm_wekt_wsp[i][j + 1].x, tab_znorm_wekt_wsp[i][j + 1].y, tab_znorm_wekt_wsp[i][j + 1].z);
				glTexCoord2f(tab_tekstur[i][j + 1].x, tab_tekstur[i][j + 1].y);
				glVertex3f(tab_wsp[i][j + 1].x, tab_wsp[i][j + 1].y, tab_wsp[i][j + 1].z);

				glEnd();


				glBegin(GL_TRIANGLES);

				glNormal3f(tab_znorm_wekt_wsp[i + 1][j + 1].x, tab_znorm_wekt_wsp[i + 1][j + 1].y, tab_znorm_wekt_wsp[i + 1][j + 1].z);
				glTexCoord2f(tab_tekstur[i + 1][j + 1].x, tab_tekstur[i + 1][j + 1].y);
				glVertex3f(tab_wsp[i + 1][j + 1].x, tab_wsp[i + 1][j + 1].y, tab_wsp[i + 1][j + 1].z);

				glNormal3f(tab_znorm_wekt_wsp[i + 1][j].x, tab_znorm_wekt_wsp[i + 1][j].y, tab_znorm_wekt_wsp[i + 1][j].z);
				glTexCoord2f(tab_tekstur[i + 1][j].x, tab_tekstur[i + 1][j].y);
				glVertex3f(tab_wsp[i + 1][j].x, tab_wsp[i + 1][j].y, tab_wsp[i + 1][j].z);

				glNormal3f(tab_znorm_wekt_wsp[i][j + 1].x, tab_znorm_wekt_wsp[i][j + 1].y, tab_znorm_wekt_wsp[i][j + 1].z);
				glTexCoord2f(tab_tekstur[i][j + 1].x, tab_tekstur[i][j + 1].y);
				glVertex3f(tab_wsp[i][j + 1].x, tab_wsp[i][j + 1].y, tab_wsp[i][j + 1].z);
				glEnd();
			}
		}
	}
}


Jajko::~Jajko()
{
}

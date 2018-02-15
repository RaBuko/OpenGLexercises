

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <fstream>
#include "Jajko.h"

int model = 2;
bool ifAxes = true;
/*MODELE
1 'o'- ostroslup
2 'j'- jajko
3 'c'- czajnik
*/

typedef float point3[3];

double pi = 3.14159265359;

static GLfloat viewer[] = { 0.0, 0.0, 10.0 };
static GLfloat xtheta = 0.0;
static GLfloat pix2angle;
static GLint status = 0;
static int x_pos_old = 0;
static int delta_x = 0;
static int y_pos_old = 0;
static int delta_y = 0;
static GLfloat ytheta = 0.0;

void Axes(void)
{
	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);

	glVertex3fv(x_min);
	glVertex3fv(x_max);

	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);

	glVertex3fv(y_min);
	glVertex3fv(y_max);

	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);

	glVertex3fv(z_min);
	glVertex3fv(z_max);

	glEnd();
}

void Mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;
		y_pos_old = y;
		status = 1;
	}

	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		y_pos_old = y;
		x_pos_old = x;
		status = 2;
	}

	else
		status = 0;
}

void Motion(GLsizei x, GLsizei y)
{
	delta_x = x - x_pos_old;
	delta_y = y - y_pos_old;
	y_pos_old = y;
	x_pos_old = x;
	glutPostRedisplay();
}

void Triangle()
{
	glBegin(GL_QUADS);

	glTexCoord2f(-5.0f, 5.0f);
	glVertex2f(-5.0f, 5.0f);

	glTexCoord2f(5.0f, 5.0f);
	glVertex2f(5.0f, 5.0f);

	glTexCoord2f(5.0f, -5.0f);
	glVertex2f(5.0f, -5.0f);

	glTexCoord2f(-5.0f, -5.0f);
	glVertex2f(-5.0f, -5.0f);

	glEnd();


	glBegin(GL_TRIANGLES);
	glTexCoord3f(-5.0f, -5.0f, 0.0f);
	glVertex3f(-5.0f, -5.0f, 0.0f);

	glTexCoord3f(5.0f, -5.0f, 0.0f);
	glVertex3f(5.0f, -5.0f, 0.0f);

	glTexCoord3f(0.0f, 0.0f, 7.5f);
	glVertex3f(0.0f, 0.0f, 7.5f);

	glEnd();


	glBegin(GL_TRIANGLES);

	glTexCoord3f(5.0f, -5.0f, 0.0f);
	glVertex3f(5.0f, -5.0f, 0.0f);

	glTexCoord3f(5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);

	glTexCoord3f(0.0f, 0.0f, 7.5f);
	glVertex3f(0.0f, 0.0f, 7.5f);

	glEnd();


	glBegin(GL_TRIANGLES);

	glTexCoord3f(5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);

	glTexCoord3f(-5.0f, 5.0f, 0.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);

	glTexCoord3f(0.0f, 0.0f, 7.5f);
	glVertex3f(0.0f, 0.0f, 7.5f);

	glEnd();


	glBegin(GL_TRIANGLES);

	glTexCoord3f(-5.0f, 5.0f, 0.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);

	glTexCoord3f(-5.0f, -5.0f, 0.0f);
	glVertex3f(-5.0f, -5.0f, 0.0f);

	glTexCoord3f(0.0f, 0.0f, 7.5f);
	glVertex3f(0.0f, 0.0f, 7.5f);

	glEnd();
}

GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat)
{

	/*************************************************************************************/

	// Struktura dla nag³ówka pliku  TGA


#pragma pack(1)           
	typedef struct
	{
		GLbyte    idlength;
		GLbyte    colormaptype;
		GLbyte    datatypecode;
		unsigned short    colormapstart;
		unsigned short    colormaplength;
		unsigned char     colormapdepth;
		unsigned short    x_orgin;
		unsigned short    y_orgin;
		unsigned short    width;
		unsigned short    height;
		GLbyte    bitsperpixel;
		GLbyte    descriptor;
	}TGAHEADER;
#pragma pack(8)

	FILE *pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;
	GLbyte    *pbitsperpixel = NULL;


	/*************************************************************************************/

	// Wartoœci domyœlne zwracane w przypadku b³êdu

	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;

#pragma warning (disable : 4996)
	pFile = fopen(FileName, "rb");
	if (pFile == NULL)
		return NULL;

	/*************************************************************************************/
	// Przeczytanie nag³ówka pliku 


	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);


	/*************************************************************************************/

	// Odczytanie szerokoœci, wysokoœci i g³êbi obrazu

	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;


	/*************************************************************************************/
	// Sprawdzenie, czy g³êbia spe³nia za³o¿one warunki (8, 24, lub 32 bity)

	if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;

	/*************************************************************************************/

	// Obliczenie rozmiaru bufora w pamiêci


	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;


	/*************************************************************************************/

	// Alokacja pamiêci dla danych obrazu


	pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

	if (pbitsperpixel == NULL)
		return NULL;

	if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
	{
		free(pbitsperpixel);
		return NULL;
	}


	/*************************************************************************************/

	// Ustawienie formatu OpenGL


	switch (sDepth)

	{

	case 3:

		*ImFormat = GL_BGR_EXT;

		*ImComponents = GL_RGB8;

		break;

	case 4:

		*ImFormat = GL_BGRA_EXT;

		*ImComponents = GL_RGBA8;

		break;

	case 1:

		*ImFormat = GL_LUMINANCE;

		*ImComponents = GL_LUMINANCE8;

		break;

	};



	fclose(pFile);



	return pbitsperpixel;

}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (ifAxes) Axes();

	glLoadIdentity();

	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	if (status == 2)
	{
		viewer[2] += delta_y;
	}

	if (status == 1)
	{
		xtheta += delta_x * pix2angle;
		glRotatef(xtheta, 0.0, 1.0, 0.0);

		ytheta += delta_y * pix2angle;
		glRotatef(ytheta, 1.0, 0.0, 0.0);
	}

	glColor3f(1.0f, 1.0f, 1.0f);

	if (model == 1) Triangle();
	if (model == 2) new Jajko();
	if (model == 3) glutSolidTeapot(3.0);

	glFlush();
	glutSwapBuffers();
}

void Keys(unsigned char key, int x, int y)
{
	if (key == 'o') model = 1;
	if (key == 'j') model = 2;
	if (key == 'c') model = 3;
	if (key == 'a')
	{
		if (ifAxes) ifAxes = false;
		else ifAxes = true;
	}

	RenderScene(); // przerysowanie obrazu sceny
}

void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLbyte *pBytes;
	GLint ImWidth, ImHeight, ImComponents;
	GLenum ImFormat;

	// MATERIAL

	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki ka =[kar,kag,kab] dla œwiat³a otoczenia

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki kd =[kdr,kdg,kdb] œwiat³a rozproszonego

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki ks =[ksr,ksg,ksb] dla œwiat³a odbitego               

	GLfloat mat_shininess = { 20.0 };
	// wspó³czynnik n opisuj¹cy po³ysk powierzchni


	// DEFINICJA ZRODLA SWIATLA
	GLfloat att_constant = { 1.0 };
	// sk³adowa sta³a ds dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a

	GLfloat att_linear = { (GLfloat)0.05 };
	// sk³adowa liniowa dl dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a

	GLfloat att_quadratic = { (GLfloat)0.001 };
	// sk³adowa kwadratowa dq dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a

	// PIERWSZE ZRODLO SWIATLA
	GLfloat light_position[] = { 10.0, 10.0, 0, 1.0 };

	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]


	//DRUGIE ZRODLO SWIATLA
	GLfloat light_position1[] = { -10.0,-10.0, 0, 1.0 };

	GLfloat light_ambient1[] = { 0.1, 0.1, 0.1, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse1[] = { 1.0, 0.1, 0.1, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular1[] = { 1.0, 0.5, 0.5, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]

	// USTAWIENIE PARAMETROW MATERIALU
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	// USTAWIENIE PIERWSZEGO SWIATLA
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	// Ustawienie opcji systemu oœwietlania sceny
	glShadeModel(GL_SMOOTH); // w³aczenie ³agodnego cieniowania
	glEnable(GL_LIGHTING);   // w³aczenie systemu oœwietlenia sceny
	glEnable(GL_LIGHT0);     // w³¹czenie Ÿród³a o numerze 0
	glEnable(GL_DEPTH_TEST); // w³¹czenie mechanizmu z-bufora


							 // Teksturowanie bêdzie prowadzone tyko po jednej stronie œciany
							 //glEnable(GL_CULL_FACE);

							 //Wczytanie tekstury
	pBytes = LoadTGAImage("tekstury//RBmapa.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);

	// Zdefiniowanie tekstury 2-D
	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);

	free(pBytes);


	// W³¹czenie mechanizmu teksturowania
	glEnable(GL_TEXTURE_2D);

	// Ustalenie trybu teksturowania
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	// Okreœlenie sposobu nak³adania tekstur

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	pix2angle = 360.0 / (float)horizontal;  // przeliczenie pikseli na stopnie
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(70, 1.0, 1.0, 30.0);

	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 800);

	glutCreateWindow("OpenGL");

	glutKeyboardFunc(Keys);

	glutMouseFunc(Mouse);

	glutMotionFunc(Motion);

	glutDisplayFunc(RenderScene);

	glutReshapeFunc(ChangeSize);
	MyInit();

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}

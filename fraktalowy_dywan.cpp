
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <time.h>
#include <cstdlib>

void koloruj_kwadrat(GLfloat x, GLfloat y, GLfloat a);
void losuj_kolor();
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym
	koloruj_kwadrat(0.0f, 0.0f, 150.0f);
	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania
}

void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wn�trza okna - ustawiono na szary
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szeroko�� i wysoko�� okna) s�
// przekazywane do funkcji za ka�dym razem, gdy zmieni si� rozmiar okna
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Okre�lenie uk�adu wsp�rz�dnych obserwatora

	glLoadIdentity();
	// Okre�lenie przestrzeni ograniczaj�cej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest
	// okre�lenie okna obserwatora.
	// Pozwala to zachowa� w�a�ciwe proporcje rysowanego obiektu
	// Do okre�lenia okna obserwatora s�u�y funkcja glOrtho(...)

	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okre�lenie uk�adu wsp�rz�dnych     

	glLoadIdentity();
}

void main(int argc, char* argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wy�wietlania
	// GLUT_SINGLE - pojedynczy bufor wy�wietlania
	// GLUT_RGBA - model kolor�w RGB

	glutCreateWindow("Fraktalowy Dywan");
	// Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
	// Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy trzeba b�dzie przerysowa� okno

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn� za zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie inicjalizacje konieczneprzed przyst�pieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}

void koloruj_kwadrat(GLfloat x, GLfloat y, GLfloat a)
{
	if (a < 1.0f) return

	glBegin(GL_QUADS);
	losuj_kolor();
	glVertex2f(x + a / 2, y + a / 2);
	glVertex2f(x, y + a / 2);
	glVertex2f(x + a / 2, y);
	glVertex2f(x, y);
	glEnd();
	koloruj_kwadrat(x + a / 2, y + a / 2, a / 2);

	glBegin(GL_QUADS);
	losuj_kolor();
	glVertex2f(x - a / 2, y + a / 2);
	glVertex2f(x, y + a / 2);
	glVertex2f(x - a / 2, y);
	glVertex2f(x, y);
	koloruj_kwadrat(x - a / 2, y + a / 2, a / 2);
	glEnd();


	glBegin(GL_QUADS);
	losuj_kolor();
	glVertex2f(x - a / 2, y - a / 2);
	glVertex2f(x - a / 2, y);
	glVertex2f(x, y - a / 2);
	glVertex2f(x, y);
	koloruj_kwadrat(x - a / 2, y - a / 2, a / 2);
	glEnd();


	glBegin(GL_QUADS);
	losuj_kolor();
	glVertex2f(x + a / 2, y - a / 2);
	glVertex2f(x, y - a / 2);
	glVertex2f(x + a / 2, y);
	glVertex2f(x, y);
	koloruj_kwadrat(x + a / 2, y - a / 2, a / 2);
	glEnd();

}

void losuj_kolor()
{
	glColor3f((std::rand() % 100) / 100.0f, (std::rand() % 100) / 100.0f, (std::rand() % 100) / 100.0f);
}



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
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym
	koloruj_kwadrat(0.0f, 0.0f, 150.0f);
	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania
}

void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wnêtrza okna - ustawiono na szary
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szerokoœæ i wysokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem, gdy zmieni siê rozmiar okna
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio okreœlaj¹cej proporcjê wymiarów okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna urz¹dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Okreœlenie uk³adu wspó³rzêdnych obserwatora

	glLoadIdentity();
	// Okreœlenie przestrzeni ograniczaj¹cej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest
	// okreœlenie okna obserwatora.
	// Pozwala to zachowaæ w³aœciwe proporcje rysowanego obiektu
	// Do okreœlenia okna obserwatora s³u¿y funkcja glOrtho(...)

	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okreœlenie uk³adu wspó³rzêdnych     

	glLoadIdentity();
}

void main(int argc, char* argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wyœwietlania
	// GLUT_SINGLE - pojedynczy bufor wyœwietlania
	// GLUT_RGBA - model kolorów RGB

	glutCreateWindow("Fraktalowy Dywan");
	// Utworzenie okna i okreœlenie treœci napisu w nag³ówku okna

	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback)
	// Biblioteka GLUT bêdzie wywo³ywa³a t¹ funkcjê za ka¿dym razem, gdy trzeba bêdzie przerysowaæ okno

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹ za zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy¿ej) wykonuje wszelkie inicjalizacje konieczneprzed przyst¹pieniem do renderowania

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


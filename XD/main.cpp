// Gl_template.c
//Wy³šczanie b³êdów przed "fopen"
#define  _CRT_SECURE_NO_WARNINGS


// £adowanie bibliotek:

#ifdef _MSC_VER                         // Check if MS Visual C compiler
#  pragma comment(lib, "opengl32.lib")  // Compiler-specific directive to avoid manually configuration
#  pragma comment(lib, "glu32.lib")     // Link libraries
#endif

//{{NO_DEPENDENCIES}}
// Microsoft Developer Studio generated include file.
// Used by resource.rc
//
#define IDR_MENU                        101
#define IDD_DIALOG_ABOUT                102
#define IDR_TOOLBAR1                    104
#define IDC_OPENGL_VENDOR               1000
#define IDC_OPENGL_RENDERER             1001
#define IDC_OPENGL_VERSION              1002
#define IDC_OPENGL_EXTENSIONS           1003
#define IDC_GLU_VERSION                 1005
#define IDC_GLU_EXTENSIONS              1006
#define IDC_ERROR1                      1007
#define IDC_ERROR2                      1008
#define IDC_ERROR3                      1009
#define IDC_ERROR4                      1010
#define IDC_ERROR5                      1011
#define IDC_ERROR6                      1012
#define ID_FILE_EXIT                    40001
#define ID_HELP_ABOUT                   40002
#define ID_BUTTON40003                  40003
#define ID_LIGHTING_SUNLIGHT            40004
#define ID_LIGHTING_AMBIENTLIGHT        40005
#define STB_IMAGE_IMPLEMENTATION


// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        106
#define _APS_NEXT_COMMAND_VALUE         40006
#define _APS_NEXT_CONTROL_VALUE         1013
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif



// Ustalanie trybu tekstowego:
#ifdef _MSC_VER        // Check if MS Visual C compiler
#   ifndef _MBCS
#      define _MBCS    // Uses Multi-byte character set
#   endif
#   ifdef _UNICODE     // Not using Unicode character set
#      undef _UNICODE 
#   endif
#   ifdef UNICODE
#      undef UNICODE 
#   endif
#endif
#include <windows.h>            // Window defines
#include <gl\gl.h>              // OpenGL
#include <gl\glu.h>             // GLU library
#include <math.h>				// Define for sqrt
#include <stdio.h>          // About box resource identifiers.
#include "Walec.h"
#include "Prostopadloscian.h"
#include "Lazik.h"
#include "grid.h"
#include "stb_image.h"
#include "Podloze.h"
#include "Camera.h"
#include "OBJ_Loader.h"
#include "object.h"
#include "freeglut/include/GL/freeglut.h"

#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)
#define BITMAP_ID 0x4D42		// identyfikator formatu BMP
#define GL_PI 3.14

// Color Palette handle
HPALETTE hPalette = NULL;

// Application name and instance storeage
static LPCTSTR lpszAppName = "XD";
static HINSTANCE hInstance;

bool keys[256];

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;
static GLdouble xV = 0.0f;
static GLdouble yV = 0.0f;
static GLdouble zV = 0.0f;
static GLdouble startX = -90;
static GLdouble startZ = 0;
static GLdouble doZ = 0;
static GLdouble chX = 0;
static GLdouble chZ = 0;
static GLdouble speed = 0;


static GLsizei lastHeight;
static GLsizei lastWidth;

// Opis tekstury
BITMAPINFOHEADER	bitmapInfoHeader;	// nag³ówek obrazu
unsigned char*		bitmapData;			// dane tekstury
unsigned int		texture[2];			// obiekt tekstury

unsigned int textures[5];
GLfloat rot[] = { 0,1,0,0 };
GLfloat rot1[] = { 0,1,0,0 };

GLfloat pos1[3] = { 0,0,-5 };
GLfloat pos2[3] = { 100,10,-50 };
GLfloat pos3[3] = { 200,10,-70 };
GLfloat pos4[3] = { 10,200,-70 };

GLfloat color1[3] = { 0,0.6,0 };
GLfloat color2[3] = { 0.27,0.24,0.285 };
GLfloat color3[3] = { 0,0.5,0 };

auto terrain = new object{ &textures[0], "terrain/landscape.obj", color1, pos1, rot, 20 };
auto trunk1 = new object{ &textures[1], "trunk/trunk.obj", color2, pos2, rot1, 20 };
auto trunk2 = new object{ &textures[1], "trunk/trunk.obj", color2, pos3, rot1, 20 };
auto trunk3 = new object{ &textures[1], "trunk/trunk.obj", color2, pos4, rot1, 20 };
auto leafs1 = new object{ &textures[1], "leafs/leafs.obj", color3, pos2, rot1, 20 };
auto leafs2 = new object{ &textures[1], "leafs/leafs.obj", color3, pos3, rot1, 20 };
auto leafs3 = new object{ &textures[1], "leafs/leafs.obj", color3, pos4, rot1, 20 };
auto camera = new Camera{};


unsigned int LoadTexture(const char* file, GLenum textureSlot)
{
	GLuint texHandle;
	// Copy file to OpenGL
	glGenTextures(textureSlot, &texHandle);
	glBindTexture(GL_TEXTURE_2D, texHandle);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	const auto data = stbi_load(file, &width, &height, &nrChannels, 0);
	if (data)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		gluBuild2DMipmaps(GL_TEXTURE_2D, nrChannels, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		//error
	}
	stbi_image_free(data);
	return texHandle;
}


// Declaration for Window procedure
LRESULT CALLBACK WndProc(HWND    hWnd,
	UINT    message,
	WPARAM  wParam,
	LPARAM  lParam);

// Dialog procedure for about box
BOOL APIENTRY AboutDlgProc(HWND hDlg, UINT message, UINT wParam, LONG lParam);

// Set Pixel Format function - forward declaration
void SetDCPixelFormat(HDC hDC);



// Reduces a normal vector specified as a set of three coordinates,
// to a unit normal vector of length one.
void ReduceToUnit(float vector[3])
{
	float length;

	// Calculate the length of the vector		
	length = (float)sqrt((vector[0] * vector[0]) +
		(vector[1] * vector[1]) +
		(vector[2] * vector[2]));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if (length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}


// Points p1, p2, & p3 specified in counter clock-wise order
void calcNormal(float v[3][3], float out[3])
{
	float v1[3], v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	// Calculate two vectors from the three points
	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	out[x] = v1[y] * v2[z] - v1[z] * v2[y];
	out[y] = v1[z] * v2[x] - v1[x] * v2[z];
	out[z] = v1[x] * v2[y] - v1[y] * v2[x];

	// Normalize the vector (shorten length to one)
	ReduceToUnit(out);
}



// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 7000.0f;
	GLfloat fAspect;
	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	lastWidth = w;
	lastHeight = h;

	fAspect = (GLfloat)w / (GLfloat)h;
	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	/*if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
*/
// Establish perspective: 

	gluPerspective(90.0f, fAspect, 10.0, nRange);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
{
	// Light values and coordinates
	//GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	//GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	//GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	//GLfloat	 lightPos[] = { 0.0f, 150.0f, 150.0f, 1.0f };
	//GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };


	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	//glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Enable lighting
	//glEnable(GL_LIGHTING);

	// Setup and enable light 0
	//glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	//glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	//glEnable(GL_LIGHT0);

	// Enable color tracking
	//glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	//glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	//glMateriali(GL_FRONT,GL_SHININESS,128);


	// White background
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Black brush
	glColor3f(0.0, 0.0, 0.0);
}

void skrzynka(void)
{
	glColor3d(0.8, 0.7, 0.3);


	glEnable(GL_TEXTURE_2D); // W³¹cz teksturowanie

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glNormal3d(0, 0, 1);
	glTexCoord2d(1.0, 1.0); glVertex3d(25, 25, 25);
	glTexCoord2d(0.0, 1.0); glVertex3d(-25, 25, 25);
	glTexCoord2d(0.0, 0.0); glVertex3d(-25, -25, 25);
	glTexCoord2d(1.0, 0.0); glVertex3d(25, -25, 25);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3d(1, 0, 0);
	glTexCoord2d(1.0, 1.0); glVertex3d(25, 25, 25);
	glTexCoord2d(0.0, 1.0); glVertex3d(25, -25, 25);
	glTexCoord2d(0.0, 0.0); glVertex3d(25, -25, -25);
	glTexCoord2d(1.0, 0.0); glVertex3d(25, 25, -25);
	glEnd();

	glDisable(GL_TEXTURE_2D); // Wy³¹cz teksturowanie



	glBegin(GL_QUADS);
	glNormal3d(0, 0, -1);
	glVertex3d(25, 25, -25);
	glVertex3d(25, -25, -25);
	glVertex3d(-25, -25, -25);
	glVertex3d(-25, 25, -25);

	glNormal3d(-1, 0, 0);
	glVertex3d(-25, 25, -25);
	glVertex3d(-25, -25, -25);
	glVertex3d(-25, -25, 25);
	glVertex3d(-25, 25, 25);

	glNormal3d(0, 1, 0);
	glVertex3d(25, 25, 25);
	glVertex3d(25, 25, -25);
	glVertex3d(-25, 25, -25);
	glVertex3d(-25, 25, 25);

	glNormal3d(0, -1, 0);
	glVertex3d(25, -25, 25);
	glVertex3d(-25, -25, 25);
	glVertex3d(-25, -25, -25);
	glVertex3d(25, -25, -25);
	glEnd();
}

void walec01(void)
{
	GLUquadricObj*obj;
	obj = gluNewQuadric();
	gluQuadricNormals(obj, GLU_SMOOTH);
	glColor3d(1, 0, 0);
	glPushMatrix();
	gluCylinder(obj, 20, 20, 30, 15, 7);
	gluCylinder(obj, 0, 20, 0, 15, 7);
	glTranslated(0, 0, 60);
	glRotated(180.0, 0, 1, 0);
	gluCylinder(obj, 0, 20, 30, 15, 7);
	glPopMatrix();
}

void kula(void)
{
	GLUquadricObj*obj;
	obj = gluNewQuadric();
	gluQuadricTexture(obj, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor3d(1.0, 0.8, 0.8);
	glEnable(GL_TEXTURE_2D);
	gluSphere(obj, 40, 15, 7);
	glDisable(GL_TEXTURE_2D);
}

GLuint loadBMP_custom(const char* path) {
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;

	FILE * file = fopen("tekstura.jpg", "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return 0;
	}
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54;

	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}


// LoadBitmapFile
// opis: ³aduje mapê bitow¹ z pliku i zwraca jej adres.
//       Wype³nia strukturê nag³ówka.
//	 Nie obs³uguje map 8-bitowych.
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;							// wskaŸnik pozycji pliku
	BITMAPFILEHEADER	bitmapFileHeader;		// nag³ówek pliku
	unsigned char		*bitmapImage;			// dane obrazu
	int					imageIdx = 0;		// licznik pikseli
	unsigned char		tempRGB;				// zmienna zamiany sk³adowych

	// otwiera plik w trybie "read binary"
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// wczytuje nag³ówek pliku
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// sprawdza, czy jest to plik formatu BMP
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// wczytuje nag³ówek obrazu
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// ustawia wskaŸnik pozycji pliku na pocz¹tku danych obrazu
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// przydziela pamiêæ buforowi obrazu
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// sprawdza, czy uda³o siê przydzieliæ pamiêæ
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// wczytuje dane obrazu
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// sprawdza, czy dane zosta³y wczytane
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// zamienia miejscami sk³adowe R i B 
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// zamyka plik i zwraca wskaŸnik bufora zawieraj¹cego wczytany obraz
	fclose(filePtr);
	return bitmapImage;
}
float kat = 0.0f;

void szescian(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		// Parametry wierzcholkow

		GLfloat sa[3] = { 0.0f,0.0f,0.0f };
		GLfloat sb[3] = { 10.0f,0.0f,0.0f };
		GLfloat sc[3] = { 10.0f,10.0f,0.0f };
		GLfloat sd[3] = { 0.0f,10.0f,0.0f };
		GLfloat se[3] = { 0.0f,0.0f,-10.0f };
		GLfloat sf[3] = { 10.0f,0.0f,-10.0f };
		GLfloat sg[3] = { 10.0f,10.0f,-10.0f };
		GLfloat sh[3] = { 0.0f,10.0f,-10.0f };

		GLfloat ma[3] = { 0.0f, 0.0f, 0.0f };
		GLfloat mb[3] = { 10.0f * cos(kat), 0.0f, 10.0f*sin(kat) };
		GLfloat mc[3] = { 10.0f * cos(kat), 10.0f, 10.0f*sin(kat) };
		GLfloat md[3] = { 0.0f, 10.0f, 0.0f };

		GLfloat ta[3] = { 0.0f,0.0f,0.0f };
		GLfloat tb[3] = { 0.0f,10.0f,0.0f };
		GLfloat tc[3] = { 2.0f,0.0f,0.0f };
		GLfloat td[3] = { 2.0f,10.0f,0.0f };
		GLfloat te[3] = { 4.0f,0.0f,0.0f };
		GLfloat tf[3] = { 4.0f,10.0f,0.0f };
		GLfloat tg[3] = { 6.0f,0.0f,0.0f };
		GLfloat th[3] = { 6.0f,10.0f,0.0f };
		GLfloat ti[3] = { 8.0f,0.0f,0.0f };
		GLfloat tj[3] = { 8.0f,10.0f,0.0f };
		GLfloat tk[3] = { 10.0f,0.0f,0.0f };
		GLfloat tl[3] = { 10.0f,10.0f,0.0f };

		// Sciany skladowe
		/*glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);
		
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3fv(ta);
		glVertex3fv(tb);
		glVertex3fv(tc);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3fv(td);
		glColor3f(0.9f, 0.0f, 0.0f);
		glVertex3fv(te);
		glColor3f(0.8f, 0.0f, 0.0f);
		glVertex3fv(tf);
		glColor3f(0.7f, 0.0f, 0.0f);
		glVertex3fv(tg);
		glColor3f(0.6f, 0.0f, 0.0f);
		glVertex3fv(th);
		glColor3f(0.5f, 0.0f, 0.0f);
		glVertex3fv(ti);
		glColor3f(0.4f, 0.0f, 0.0f);
		glVertex3fv(tj);
		glColor3f(0.3f, 0.0f, 0.0f);
		glVertex3fv(tk);
		glColor3f(0.2f, 0.0f, 0.0f);
		glVertex3fv(tl);


		glEnd();*/

		/*glBegin(GL_TRIANGLE_STRIP);
		float c = 1.05f;
		float y = 10.0f;
		glColor3f(c, 0.0f, 0.0f);
		for (float i = 0.0f; i < 20.0f; i += 0.1) {
			if (y == 10.0f) y = 0.0f;
			else y = 10.0f;
			c -= 0.005f;
			glColor3f(c, 0.0f, 0.0f);
			glVertex3f(i, y, 0.0f);
		}

		glEnd();*/

		float c = 1.0f;
		glColor3f(c, 0.f, 0.35f);
		glBegin(GL_TRIANGLE_STRIP);
		//glVertex3f(20.0f, 0.0f, 0.0f);
		float z, x;
		float temp = 40.0f;
		for (float pi = 0.f; pi <= 2*GL_PI; pi += 0.01f) {
			if (temp == 40.0f) {
				temp = 0.0f;
			}
			else {
				temp = 40.0f;
			}
			z = 20 * cos(pi);
			x = 20 * sin(pi);
			glVertex3f(x, temp, z);
			c -= 0.00318/2.0f;
			glColor3f(c, 0.f, 0.35f);
		}
		glEnd();
	}
}

void rysCeg(float x, float y, float z) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{

		GLfloat sa[3] = { x, y, z };
		GLfloat sb[3] = { x + 24.0f, y, z };
		GLfloat sc[3] = { x, y + 12.0f, z };
		GLfloat sd[3] = { x + 24.0f, y + 12.0f, z };
		GLfloat se[3] = { x, y, z + 6.0f };
		GLfloat sf[3] = { x + 24.0f, y, z + 6.0f };
		GLfloat sg[3] = { x, y + 12.0f, z + 6.0f };
		GLfloat sh[3] = { x + 24.0f, y + 12.0f, z + 6.0f };

		glColor3f(0.9, 0, 0);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sc);
		glVertex3fv(sd);
		glEnd();

		glColor3f(1, 0, 0);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(sc);
		glVertex3fv(sd);
		glVertex3fv(sg);
		glVertex3fv(sh);
		glEnd();
		//--------------------
		glColor3f(0.9, 0, 0);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(sg);
		glVertex3fv(sh);
		glVertex3fv(se);
		glVertex3fv(sf);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1, 0, 0);
		glVertex3fv(se);
		glVertex3fv(sf);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.8, 0, 0);
		glVertex3fv(sa);
		glVertex3fv(sc);
		glVertex3fv(se);
		glVertex3fv(sg);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.8, 0, 0);
		glVertex3fv(sb);
		glVertex3fv(sd);
		glVertex3fv(sf);
		glVertex3fv(sh);
		glEnd();
	}
}

void rys(int iloscCegiel, int iloscWarstw) {

	//obliczenie szerokoœci ca³ego muru
	float szerokosc = (iloscCegiel + 1) * 24.0f + iloscCegiel;

	//jedna iteracja tej pêtli rysuje jedn¹ warstwê
	for (int i = 0; i < iloscWarstw; i++) {
		if (i % 2 == 0) {
			//rysuje "iloscCegiel + 1" cegie³ zaczynaj¹c od pocz¹tku
			for (int j = 0; j < (iloscCegiel + 1); j++) {
				rysCeg(-szerokosc / 2 + j * 25, 0, i * 7);
			}
		}
		else {
			//rysuje "iloscCegiel" cegie³ zaczynaj¹c od pocz¹tku + 50% d³ugoœci ceg³y
			for (int j = 0; j < (iloscCegiel); j++) {
				rysCeg(-szerokosc / 2 + j * 25 + 12, 0, i * 7);
			}
		}
	}
}

void most(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		// Parametry wierzcholkow

		GLfloat sa[3] = { 0.0f,0.0f,40.0f };
		GLfloat sb[3] = { 80.0f,0.0f,40.0f };
		GLfloat sc[3] = { 0.0f,40.0f,40.0f };
		GLfloat sd[3] = { 80.0f,40.0f,40.0f };
		GLfloat se[3] = { 80.0f, 0.0f, 0.0f };
		GLfloat sf[3] = { 80.0f, 40.0f, 0.0f };
		GLfloat sg[3] = { 60.0f, 0.0f, 0.0f };
		GLfloat sh[3] = { 60.0f, 40.0f, 0.0f };
		GLfloat si[3] = { 60.0f, 0.0f, 20.0f };
		GLfloat sj[3] = { 60.0f, 40.0f, 20.0f };
		GLfloat sk[3] = { 20.0f, 0.0f, 20.0f };
		GLfloat sl[3] = { 20.0f, 40.0f, 20.0f };
		GLfloat sm[3] = { 20.0f, 0.0f, 0.0f };
		GLfloat sn[3] = { 20.0f, 40.0f, 0.0f };
		GLfloat so[3] = { 0.0f, 0.0f, 0.0f };
		GLfloat sp[3] = { 0.0f, 40.0f, 0.0f };

		// Sciana boczna
		glColor3f(0.5f, 0.5f, 0.5f);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(sa);
		glVertex3fv(sc);
		glVertex3fv(sb);
		glVertex3fv(sd);
		glColor3f(0.45f, 0.45f, 0.45f);
		glVertex3fv(se);
		glVertex3fv(sf);
		glVertex3fv(sg);
		glVertex3fv(sh);
		glEnd();

		glColor3f(0.45f, 0.45f, 0.45f);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(sm);
		glVertex3fv(sn);
		glVertex3fv(so);
		glVertex3fv(sp);
		glVertex3fv(sa);
		glVertex3fv(sc);
		glEnd();

		// Œciana z przodu bez ³uków
		glColor3f(0.4f, 0.4f, 0.4f);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(so);
		glVertex3fv(sm);
		glVertex3fv(sa);
		glVertex3fv(sk);
		glVertex3fv(sb);
		glVertex3fv(si);
		glVertex3fv(se);
		glVertex3fv(sg);
		glEnd();

		// Œciana z ty³u bez ³uków
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(sp);
		glVertex3fv(sn);
		glVertex3fv(sc);
		glVertex3fv(sl);
		glVertex3fv(sd);
		glVertex3fv(sj);
		glVertex3fv(sf);
		glVertex3fv(sh);
		glEnd();


		// Prawy przedni ³uk
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(60.0f, 0.0f, 20.0f);
		GLfloat temp[3];
		temp[1] = 0.0f;
		float z, x;
		for (float pi = 0.f; pi <= GL_PI / 2.0f; pi += 0.05f) {
			z = 20 * sin(pi);
			x = 20 * cos(pi);
			temp[0] = 40 + x;
			temp[2] = z;
			glVertex3fv(temp);
		}
		glEnd();

		// Lewy przedni ³uk
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(20.0f, 0.0f, 20.0f);
		temp[1] = 0.0f;
		for (float pi = 0.f; pi <= GL_PI / 2.0f; pi += 0.05f) {
			z = 20 * sin(pi);
			x = 20 * cos(pi);
			temp[0] = 40 - x;
			temp[2] = z;
			glVertex3fv(temp);
		}
		glEnd();

		//Prawy tylny ³uk
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(60.0f, 40.0f, 20.0f);
		temp[1] = 40.0f;
		for (float pi = 0.f; pi <= GL_PI / 2.0f; pi += 0.05f) {
			z = 20 * sin(pi);
			x = 20 * cos(pi);
			temp[0] = 40 + x;
			temp[2] = z;
			glVertex3fv(temp);
		}
		glEnd();

		//Lewy tylny ³uk
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(20.0f, 40.0f, 20.0f);
		temp[1] = 40.0f;
		for (float pi = 0.f; pi <= GL_PI / 2.0f; pi += 0.05f) {
			z = 20 * sin(pi);
			x = 20 * cos(pi);
			temp[0] = 40 - x;
			temp[2] = z;
			glVertex3fv(temp);
		}
		glEnd();

		// Wype³nienie pomiêdzy ³ukami
		glColor3f(0.35f, 0.35f, 0.35f);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(20.0f, 0.0f, 0.0f);
		temp[1] = 40.0f;
		for (float pi = 0.f; pi <= GL_PI; pi += 0.01f) {
			if (temp[1] == 40.0f) {
				temp[1] = 0.0f;
			}
			else {
				temp[1] = 40.0f;
			}
			z = 20 * sin(pi);
			x = 20 * cos(pi);
			temp[0] = 40 - x;
			temp[2] = z;
			glVertex3fv(temp);
		}
		glEnd();
	}
}

void mur(void)
{

	rys(5, 7);

}

void ramie(double r1, double r2, double h, double d)
{
	double PI = 3.14, alpha, x, y;
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(0.8, 0.0, 0);
	glVertex3d(0, 0, 0);
	for (alpha = PI; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		x = r1 * sin(alpha);
		y = r1 * cos(alpha);
		glVertex3d(x, y, 0);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (alpha = 0; alpha >= -PI; alpha -= PI / 8.0)
	{
		x = r1 * sin(alpha);
		y = r1 * cos(alpha);
		glVertex3d(x, y, h);
		glVertex3d(x, y, 0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0, 0, h);
	for (alpha = 0; alpha >= -PI; alpha -= PI / 8.0)
	{
		x = r1 * sin(alpha);
		y = r1 * cos(alpha);
		glVertex3d(x, y, h);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3d(0.8, 0.0, 0);
	//glVertex3d(d,r2,0);
	//glVertex3d(d, r2, h);
	for (alpha = 0; alpha <= PI; alpha += PI / 8.0)
	{
		x = d + r2 * sin(alpha);
		y = d + r2 * cos(alpha);
		glVertex3d(x, y, 0);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	//glVertex3d(d, r2, 0);
	for (alpha = 0; alpha <= PI; alpha += PI / 8.0)
	{
		x = d + r2 * sin(alpha);
		y = d + r2 * cos(alpha);
		glVertex3d(x, y, h);
		glVertex3d(x, y, 0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	//glVertex3d(d, r2, h);
	for (alpha = 0; alpha <= PI; alpha += PI / 8.0)
	{
		x = d + r2 * sin(alpha);
		y = d + r2 * cos(alpha);
		glVertex3d(x, y, h);
	}
	glEnd();
}

Lazik laz(0, 0, 30);

void walec(double r, double h)
{
	double x, y, alpha, PI = 3.14;
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(0.8, 0.0, 0);
	glVertex3d(0, 0, 0);
	for (alpha = 0; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(x, y, 0);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(x, y, 0);
		glVertex3d(x, y, h);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0, 0, h);
	for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 8.0)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(x, y, h);
	}
	glEnd();
}

// Called to draw scene
void RenderScene(void)
{
	//float normal[3];	// Storeage for calculated surface normal

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state and do the rotations
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	/////////////////////////////////////////////////////////////////
	// MIEJSCE NA KOD OPENGL DO TWORZENIA WLASNYCH SCEN:		   //
	/////////////////////////////////////////////////////////////////
	//szescian();

	//Sposób na odróŸnienie "przedniej" i "tylniej" œciany wielok¹ta:
	glPolygonMode(GL_BACK, GL_LINE);
	//walec(40, 40);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	terrain->draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	trunk1->draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	trunk2->draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	trunk3->draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	leafs1->draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	leafs2->draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	leafs3->draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	/*glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	trunk->draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();*/

	//lazik();
	glPushMatrix();


	glTranslatef(chX, -60.0, chZ); // 3. Translate to the object's position.

	glRotatef(startX, 1.0, 0.0, 0.0); // 2. Rotate the object.
	glRotatef(startZ + doZ, 0.0, 0.0, 1.0); // 2. Rotate the object.

	//glTranslatef(-250, -250, 0.0); // 1. Translate to the origin.

	// Draw the object
	laz.rysujLazik();
	glPopMatrix();
	//Uzyskanie siatki:
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	//Wyrysowanie prostokata:
	//glRectd(-10.0,-10.0,20.0,20.0);

	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	// Flush drawing commands
	glFlush();
	if (keys['J']) {
		doZ += 5;
	}

	if (keys['L']) {
		doZ -= 5;
	}
	GLdouble odl1 = sqrt(pow(chX - pos2[0], 2) + pow(chZ - pos2[1], 2));
	GLdouble odl2 = sqrt(pow(chX - pos3[0], 2) + pow(chZ - pos3[1], 2));
	GLdouble odl3 = sqrt(pow(chX - pos4[0], 2) + pow(chZ - pos4[1], 2));
	GLdouble col = 50;
	if (odl1 > col && odl2 > col && odl3 > col) {
		if (keys['K']) {
			//speed += 10;
			chX += sin((startZ + doZ + 90)*GL_PI / 180) * 5;
			chZ += cos((startZ + doZ + 90)*GL_PI / 180) * 5;
		}

		if (keys['I']) {
			//speed -= 10;	
			chX -= sin((startZ + doZ + 90)*GL_PI / 180) * 5;
			chZ -= cos((startZ + doZ + 90)*GL_PI / 180) * 5;
		}
	}
}

//void timer(int) {
//	RenderScene();
//	glutTimerFunc(1000.0 / 60.0, timer, 0);
//}

// Select the pixel format for a given device context
void SetDCPixelFormat(HDC hDC)
{
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // Size of this structure
		1,                                                              // Version of this structure    
		PFD_DRAW_TO_WINDOW |                    // Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |					// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,                       // Double buffered
		PFD_TYPE_RGBA,                          // RGBA Color mode
		24,                                     // Want 24bit color 
		0,0,0,0,0,0,                            // Not used to select mode
		0,0,                                    // Not used to select mode
		0,0,0,0,0,                              // Not used to select mode
		32,                                     // Size of depth buffer
		0,                                      // Not used to select mode
		0,                                      // Not used to select mode
		PFD_MAIN_PLANE,                         // Draw in main plane
		0,                                      // Not used to select mode
		0,0,0 };                                // Not used to select mode

	// Choose a pixel format that best matches that described in pfd
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	// Set the pixel format for the device context
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}


// If necessary, creates a 3-3-2 palette for the device context listed.
HPALETTE GetOpenGLPalette(HDC hDC)
{
	HPALETTE hRetPal = NULL;	// Handle to palette to be created
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange, GreenRange, BlueRange;
	// Range for each color entry (7,7,and 3)


// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(hDC);
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if (!(pfd.dwFlags & PFD_NEED_PALETTE))
		return NULL;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + nColors * sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) - 1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) - 1;

	// Loop through all the palette entries
	for (i = 0; i < nColors; i++)
	{
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double)pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char)NULL;
	}


	// Create the palette
	hRetPal = CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(hDC, hRetPal, FALSE);
	RealizePalette(hDC);

	// Free the memory used for the logical palette structure
	free(pPal);

	// Return the handle to the new palette
	return hRetPal;
}


// Entry point of all Windows programs
int APIENTRY WinMain(HINSTANCE       hInst,
	HINSTANCE       hPrevInstance,
	LPSTR           lpCmdLine,
	int                     nCmdShow)
{
	MSG                     msg;            // Windows message structure
	WNDCLASS        wc;                     // Windows class structure
	HWND            hWnd;           // Storeage for window handle

	hInstance = hInst;

	// Register Window style
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	// No need for background brush for OpenGL window
	wc.hbrBackground = NULL;

	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName = lpszAppName;

	// Register the window class
	if (RegisterClass(&wc) == 0)
		return FALSE;


	// Create the main application window
	hWnd = CreateWindow(
		lpszAppName,
		lpszAppName,

		// OpenGL requires WS_CLIPCHILDREN and WS_CLIPSIBLINGS
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,

		// Window position and size
		50, 50,
		400, 400,
		NULL,
		NULL,
		hInstance,
		NULL);

	// If window was not created, quit
	if (hWnd == NULL)
		return FALSE;


	// Display the window
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// Process application messages until the application closes
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}




// Window procedure, handles all messages for this program
LRESULT CALLBACK WndProc(HWND    hWnd,
	UINT    message,
	WPARAM  wParam,
	LPARAM  lParam)
{
	static HGLRC hRC;               // Permenant Rendering context
	static HDC hDC;                 // Private GDI Device context


	switch (message)
	{
		// Window creation, setup for OpenGL
	case WM_CREATE:
		// Store the device context
		hDC = GetDC(hWnd);
		//glutTimerFunc(1000.0 / 60.0, timer, 0);
		// Select the pixel format
		SetDCPixelFormat(hDC);

		// Create palette if needed
		hPalette = GetOpenGLPalette(hDC);

		// Create the rendering context and make it current
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		SetupRC();
		glGenTextures(2, &texture[0]);                  // tworzy obiekt tekstury			

		textures[0] = LoadTexture("grass.png", 1);
		textures[1] = LoadTexture("grass.png", 1);



		// ³aduje pierwszy obraz tekstury:
		//bitmapData = LoadBitmapFile("Bitmapy\\checker.bmp", &bitmapInfoHeader);

		glBindTexture(GL_TEXTURE_2D, texture[0]);       // aktywuje obiekt tekstury

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// tworzy obraz tekstury
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

		if (bitmapData)
			free(bitmapData);

		// ³aduje drugi obraz tekstury:
		//bitmapData = LoadBitmapFile("Bitmapy\\crate.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[1]);       // aktywuje obiekt tekstury

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// tworzy obraz tekstury
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

		if (bitmapData)
			free(bitmapData);

		// ustalenie sposobu mieszania tekstury z t³em
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		break;

		// Window is being destroyed, cleanup
	case WM_DESTROY:
		// Deselect the current rendering context and delete it
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);

		// Delete the palette if it was created
		if (hPalette != NULL)
			DeleteObject(hPalette);

		// Tell the application to terminate after the window
		// is gone.
		PostQuitMessage(0);
		break;

		// Window is resized.
	case WM_SIZE:
		// Call our function which modifies the clipping
		// volume and viewport
		ChangeSize(LOWORD(lParam), HIWORD(lParam));
		break;


		// The painting function.  This message sent by Windows 
		// whenever the screen needs updating.
	case WM_PAINT:
	{
		// Call OpenGL drawing code
		RenderScene();

		SwapBuffers(hDC);

		// Validate the newly painted client area
		ValidateRect(hWnd, NULL);
	}
	break;

	// Windows is telling the application that it may modify
	// the system palette.  This message in essance asks the 
	// application for a new palette.
	case WM_QUERYNEWPALETTE:
		// If the palette was created.
		if (hPalette)
		{
			int nRet;

			// Selects the palette into the current device context
			SelectPalette(hDC, hPalette, FALSE);

			// Map entries from the currently selected palette to
			// the system palette.  The return value is the number 
			// of palette entries modified.
			nRet = RealizePalette(hDC);

			// Repaint, forces remap of palette in current window
			InvalidateRect(hWnd, NULL, FALSE);

			return nRet;
		}
		break;


		// This window may set the palette, even though it is not the 
		// currently active window.
	case WM_PALETTECHANGED:
		// Don't do anything if the palette does not exist, or if
		// this is the window that changed the palette.
		if ((hPalette != NULL) && ((HWND)wParam != hWnd))
		{
			// Select the palette into the device context
			SelectPalette(hDC, hPalette, FALSE);

			// Map entries to system palette
			RealizePalette(hDC);

			// Remap the current colors to the newly realized palette
			UpdateColors(hDC);
			return 0;
		}
		break;

		// Key press, check for arrow keys to do cube rotation.
	case WM_KEYUP:
	{
		if (wParam == 'J') {
			keys['J'] = false;
		}

		if (wParam == 'L') {
			keys['L'] = false;
		}

		if (wParam == 'K') {
			keys['K'] = false;
		}

		if (wParam == 'I') {
			keys['I'] = false;
		}
	}
	break;
	case WM_KEYDOWN:
	{
		/*if (wParam == VK_UP)
			xRot -= 5.0f;

		if (wParam == VK_DOWN)
			xRot += 5.0f;

		if (wParam == VK_LEFT)
			yRot -= 5.0f;

		if (wParam == VK_RIGHT)
			yRot += 5.0f;

		xRot = (const int)xRot % 360;
		yRot = (const int)yRot % 360;

		InvalidateRect(hWnd, NULL, FALSE);*/

		//TODO renderowanie cykliczne, antweakbar, fabu³a z pieni¹¿kami i pomiarem czase, mo¿liwoœæ kilku graczy

		camera->update(wParam);

		xRot = (const int)xRot % 360;
		yRot = (const int)yRot % 360;
		zRot = (const int)zRot % 360;

		InvalidateRect(hWnd, NULL, FALSE);

		if (wParam == 'J') {
			keys['J'] = true;
		}

		if (wParam == 'L') {
			keys['L'] = true;
		}

		if (wParam == 'K') {
			keys['K'] = true;
		}

		if (wParam == 'I') {
			keys['I'] = true;
		}
	}
	break;

	// A menu command
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			// Exit the program
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			break;

			// Display the about box
		case ID_HELP_ABOUT:
			DialogBox(hInstance,
				MAKEINTRESOURCE(IDD_DIALOG_ABOUT),
				hWnd,
				AboutDlgProc);
			break;
		}
	}
	break;


	default:   // Passes it on if unproccessed
		return (DefWindowProc(hWnd, message, wParam, lParam));

	}
	return (0L);
}




// Dialog procedure.
BOOL APIENTRY AboutDlgProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{

	switch (message)
	{
		// Initialize the dialog box
	case WM_INITDIALOG:
	{
		int i;
		GLenum glError;

		// glGetString demo
		//SetDlgItemText(hDlg, IDC_OPENGL_VENDOR, glGetString(GL_VENDOR));
		//SetDlgItemText(hDlg, IDC_OPENGL_RENDERER, glGetString(GL_RENDERER));
		//SetDlgItemText(hDlg, IDC_OPENGL_VERSION, glGetString(GL_VERSION));
		//SetDlgItemText(hDlg, IDC_OPENGL_EXTENSIONS, glGetString(GL_EXTENSIONS));

		//// gluGetString demo
		//SetDlgItemText(hDlg, IDC_GLU_VERSION, gluGetString(GLU_VERSION));
		//SetDlgItemText(hDlg, IDC_GLU_EXTENSIONS, gluGetString(GLU_EXTENSIONS));


		//// Display any recent error messages
		//i = 0;
		//do {
		//	glError = glGetError();
		//	SetDlgItemText(hDlg, IDC_ERROR1 + i, gluErrorString(glError));
			//i++;
		//} while (i < 6 && glError != GL_NO_ERROR);


		return (TRUE);
	}
	break;

	// Process command messages
	case WM_COMMAND:
	{
		// Validate and Make the changes
		if (LOWORD(wParam) == IDOK)
			EndDialog(hDlg, TRUE);
	}
	break;

	// Closed from sysbox
	case WM_CLOSE:
		EndDialog(hDlg, TRUE);
		break;
	}

	return FALSE;
}

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
#include "AntTweakBar.h"
#include "Coin.h"
#include <ctime>
#include <cstdlib>
#pragma comment(lib, "lib/AntTweakBar.lib")

#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)
#define BITMAP_ID 0x4D42		// identyfikator formatu BMP
#define GL_PI 3.14

// Color Palette handle
HPALETTE hPalette = NULL;

// Application name and instance storeage
static LPCTSTR lpszAppName = "XD";
static HINSTANCE hInstance;

bool keys[256];
void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
void RenderScene(void);
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
static GLdouble speed2 = 0;

clock_t begin;
clock_t end;
double elapsedTime[3];

float coinsPositions1[3] = { 0,0,-40 };
float coinsPositions2[3] = { 0,0,-40 };
float coinsPositions3[3] = { 0,0,-40 };
float coinsPositions4[3] = { 0,0,-40 };
float coinsPositions5[3] = { 0,0,-40 };

Coin coin1 = Coin(coinsPositions1[0], coinsPositions1[1], -80, 20, 30, "zolty");
Coin coin2 = Coin(coinsPositions2[0], coinsPositions2[1], -80, 20, 30, "zolty");
Coin coin3 = Coin(coinsPositions3[0], coinsPositions3[1], -80, 20, 30, "zolty");
Coin coin4 = Coin(coinsPositions4[0], coinsPositions4[1], -80, 20, 30, "zolty");
Coin coin5 = Coin(coinsPositions5[0], coinsPositions5[1], -80, 20, 30, "zolty");
int game = -1;
bool gameOn = false;
int coinsLeft = 0;

Lazik laz(0, 0, 30);
UINT TimerId = SetTimer(NULL, 1, 5, &TimerProc);

void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	InvalidateRect(hWnd, NULL, FALSE);
	if (gameOn) {
		end = clock();
		elapsedTime[game] = double(end - begin) / CLOCKS_PER_SEC;
	}
}

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
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0, 0.0, 0.0);
}


float kat = 0.0f;

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

	glPolygonMode(GL_BACK, GL_LINE);

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

	glPushMatrix();
	glTranslatef(chX, -60.0, chZ); // 3. Translate to the object's position.
	glRotatef(startX, 1.0, 0.0, 0.0); // 2. Rotate the object.
	glRotatef(startZ + doZ, 0.0, 0.0, 1.0); // 2. Rotate the object.
	laz.rysujLazik();
	glPopMatrix();

	if (gameOn) {
		glPushMatrix();
		glRotatef(startX, 1.0, 0.0, 0.0);
		if (!coin1.taken)
			coin1.rysujWalec();
		if (!coin2.taken)
			coin2.rysujWalec();
		if (!coin3.taken)
			coin3.rysujWalec();
		if (!coin4.taken)
			coin4.rysujWalec();
		if (!coin5.taken)
			coin5.rysujWalec();
		glPopMatrix();
	}

	srand(time(NULL));

	glMatrixMode(GL_MODELVIEW);
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
	if (keys['K']) {
		if (speed < 5)
			speed += 5;
	}

	if (keys['I']) {
		if (speed > -30)
			speed -= 5;
	}

	GLdouble addX = sin((startZ + doZ + 90)*GL_PI / 180) * speed;
	GLdouble addZ = cos((startZ + doZ + 90)*GL_PI / 180) * speed;

	if (odl1 >= col && odl2 >= col && odl3 >= col) {	
		chX += addX;
		chZ += addZ;
	}
	else {
		speed = -5;
		GLdouble odl11 = sqrt(pow(chX + addX - pos2[0], 2) + pow(chZ + addZ - pos2[1], 2));
		GLdouble odl21 = sqrt(pow(chX + addX - pos3[0], 2) + pow(chZ + addZ - pos3[1], 2));
		GLdouble odl31 = sqrt(pow(chX + addX - pos4[0], 2) + pow(chZ + addZ - pos4[1], 2));
		if (odl11 >= odl1 && odl21 >= odl2 && odl31 >= odl3) {
			chX += addX;
			chZ += addZ;
		}
	}

	if (keys['B']) {
		if (!gameOn) {
			game++;
			if (game == 3)
				game = 0;
			gameOn = true;
			chX = 0;
			chZ = 0;
			speed = 0;
			coinsLeft = 5;

			coinsPositions1[0] = (rand() % 2000) - 1000;
			coinsPositions1[1] = (rand() % 2000) - 1000;
			
			coinsPositions2[0] = (rand() % 2000) - 1000;
			coinsPositions2[1] = (rand() % 2000) - 1000;

			coinsPositions3[0] = (rand() % 2000) - 1000;
			coinsPositions3[1] = (rand() % 2000) - 1000;

			coinsPositions4[0] = (rand() % 2000) - 1000;
			coinsPositions4[1] = (rand() % 2000) - 1000;

			coinsPositions5[0] = (rand() % 2000) - 1000;
			coinsPositions5[1] = (rand() % 2000) - 1000;

			coin1.ustawPozycje(coinsPositions1[0], coinsPositions1[1], 0);
			coin2.ustawPozycje(coinsPositions2[0], coinsPositions2[1], 0);
			coin3.ustawPozycje(coinsPositions3[0], coinsPositions3[1], 0);
			coin4.ustawPozycje(coinsPositions4[0], coinsPositions4[1], 0);
			coin5.ustawPozycje(coinsPositions5[0], coinsPositions5[1], 0);

			coin1.taken = false;
			coin2.taken = false;
			coin3.taken = false;
			coin4.taken = false;
			coin5.taken = false;
			begin = clock();
		}
	}

	GLdouble odlCoin1 = sqrt(pow(chX - coinsPositions1[0], 2) + pow(chZ + coinsPositions1[1], 2));
	GLdouble odlCoin2 = sqrt(pow(chX - coinsPositions2[0], 2) + pow(chZ + coinsPositions2[1], 2));
	GLdouble odlCoin3 = sqrt(pow(chX - coinsPositions3[0], 2) + pow(chZ + coinsPositions3[1], 2));
	GLdouble odlCoin4 = sqrt(pow(chX - coinsPositions4[0], 2) + pow(chZ + coinsPositions4[1], 2));
	GLdouble odlCoin5 = sqrt(pow(chX - coinsPositions5[0], 2) + pow(chZ + coinsPositions5[1], 2));

	if (!coin1.taken)
		if (odlCoin1 <= 100) {
			coin1.taken = true;
			coinsLeft--;
			if (coinsLeft == 0) {
				gameOn = false;
				end = clock();
				elapsedTime[game] = double(end - begin) / CLOCKS_PER_SEC;
			}
		}
	if (!coin2.taken)
		if (odlCoin2 <= 100) {
			coin2.taken = true;
			coinsLeft--;
			if (coinsLeft == 0) {
				gameOn = false;
				end = clock();
				elapsedTime[game] = double(end - begin) / CLOCKS_PER_SEC;
			}
		}
	if (!coin3.taken)
		if (odlCoin3 <= 100) {
			coin3.taken = true;
			coinsLeft--;
			if (coinsLeft == 0) {
				gameOn = false;
				end = clock();
				elapsedTime[game] = double(end - begin) / CLOCKS_PER_SEC;
			}
		}
	if (!coin4.taken)
		if (odlCoin4 <= 100) {
			coin4.taken = true;
			coinsLeft--;
			if (coinsLeft == 0) {
				gameOn = false;
				end = clock();
				elapsedTime[game] = double(end - begin) / CLOCKS_PER_SEC;
			}
		}
	if (!coin5.taken)
		if (odlCoin5 <= 100) {
			coin5.taken = true;
			coinsLeft--;
			if (coinsLeft == 0) {
				gameOn = false;
				end = clock();
				elapsedTime[game] = double(end - begin) / CLOCKS_PER_SEC;
			}
		}

	speed2 = -speed;
	TwDraw();
}


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

	//coins[0] = &Coin(20, -60, 20, 20, 30, "zolty");

	//inicjalizacja anttweakbara
	TwInit(TW_OPENGL, NULL);
	TwWindowSize(200,200);
	TwBar *myBar;
	myBar = TwNewBar("Parameters");
	TwAddVarRW(myBar, "X", TW_TYPE_DOUBLE, &chX, "");
	TwAddVarRW(myBar, "Y", TW_TYPE_DOUBLE, &chZ, "");
	TwAddVarRW(myBar, "Speed", TW_TYPE_DOUBLE, &speed2, "");
	TwAddVarRW(myBar, "Coins left", TW_TYPE_INT16, &coinsLeft, "");
	TwAddVarRW(myBar, "Player 1", TW_TYPE_DOUBLE, &elapsedTime, "");
	TwAddVarRW(myBar, "Player 2", TW_TYPE_DOUBLE, &elapsedTime[1], "");
	TwAddVarRW(myBar, "Player 3", TW_TYPE_DOUBLE, &elapsedTime[2], "");
	//TwAddButton(myBar, "Run", RunCB, NULL, "label = 'Pokemon'");

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

	case WM_TIMER:
		RenderScene();

		SwapBuffers(hDC);

		// Validate the newly painted client area
		ValidateRect(hWnd, NULL);
		break;
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
		if (wParam == 'B') {
			keys['B'] = false;
		}
	}
	break;
	case WM_KEYDOWN:
	{
		//TODO fabu³a z pieni¹¿kami i pomiarem czase, mo¿liwoœæ kilku graczy

		camera->update(wParam);

		xRot = (const int)xRot % 360;
		yRot = (const int)yRot % 360;
		zRot = (const int)zRot % 360;

		//InvalidateRect(hWnd, NULL, FALSE);

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
		if (wParam == 'B') {
			keys['B'] = true;
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

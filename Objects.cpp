
/****************************************************************************

    CarGL (Objects.cpp)

    Pr�ctica de Gr�ficos por Computador (Grado Ingenier�a Multimedia)
  -----------------------------------------------------------------------

    Noviembre 2012 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)

****************************************************************************/


#include "Objects.h"
#include <GL/glui.h>

#include "load3ds.c"
#include "imageloader.cpp"

//0 camino, 1 ladera,  2 cesped,  3 pared_vieja_textura
//4 madera_vieja,  5 teja_antigua,  6 arena, 7 banco_madera, 8 tronco, 9 hierba, 10 pared piedra
GLuint texturas[11] = { 0,0,0,0,0,0,0,0,0,0,0};

// Variable para inicializar los vectores correpondientes con los valores iniciales
GLfloat light0_ambient_c[4]  = {   0.2f, 0.2f, 0.2f, 1.0f };
GLfloat light0_diffuse_c[4]  = {   0.6f, 0.6f, 0.6f, 1.0f };
GLfloat light0_specular_c[4] = {   1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light0_position_c[4] = { -20.0f, 70.0f, -90.0f, 1.0f };

GLfloat light1_ambient_c[4]  = { 0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light1_diffuse_c[4]  = { 0.6f,   0.6f,  0.6f, 1.0f };
GLfloat light1_specular_c[4] = { 1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light1_position_c[4] = { 0.0f, 100.0f, 10.0f, 1.0f };

GLfloat light2_ambient_c[4]  = { 0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light2_diffuse_c[4]  = { 0.6f,   0.6f,  0.6f, 1.0f };
GLfloat light2_specular_c[4] = { 1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light2_position_c[4] = { 10.0f, 50.0f, 90.0f, 1.0f };

GLfloat mat_ambient_c[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse_c[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular_c[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat high_shininess_c[1] = { 100.0f };


// Matriz de 4x4 = (I)
float view_rotate_c[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_position_c[3] = { 0.0, -2.0, -25.0 };

//Materiales
GLfloat materialNulo[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat ambMedio[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat ambMarron[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat dif[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat espMedio[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat esp[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat noResplandor[] = { 0.0 };
GLfloat bajoResplandor[] = { 12.0 };
GLfloat medioResplandor[] = { 50.0 };
GLfloat altoResplandor[] = { 100.0 };

GLfloat matEmision[] = {1.0, 1.0, 1.0, 0.9};


//CREAR MATERIALES PARA EL COCHE
GLfloat brilloCoche[] = {0.75 };
GLfloat lumCoche[] = {25.0 };
GLfloat difCoche[] = {0.7, 0.7, 0.7, 1.0};
<<<<<<< HEAD
GLfloat espCoche[] = {1.0, 1.0, 1.0, 1.0};

float pos_arboles[8][2]={
                            {9.0 , 9.0},
                            {9.0, 0.0},
                            {9.0, -9.0},
                            {0.0 , 9.0},
                            {0.0, -9.0},
                            {-9.0 , 9.0},
                            {-9.0, 0.0},
                            {-9.0, -9.0}
                        };
=======
GLfloat espCoche[] = {1.0, 1.0, 1.0, 1.0};
>>>>>>> 787514e29c3856a12eeb7ad9c973bf3c9735b82e

//Colores
float color_suelo[4] = {0.15,1,0.15, 1};
float color_blanco[4] = {1.0,1.0,1.0, 1.0};
float colores_c[2][4] = { {0.8, 0.5, 0.0, 1.0}, {0.35, 0.35, 0.35, 1.0}}; //Coche, rueda
float colores_farola[3][4] = {{0.6, 0.6, 0.6, 1.0},{0.5, 0.5, 0.5, 1.0},{1.0, 1.0, 1.0, 0.42}}; //Base, capucha, y cristal de la farola
float colores_carr[4] = {1.0,0.8,0.6, 1.0};
float colores_carr_claro[4] = {0.5,0.4,0.1, 1.0};
float colores_casa[4][4] = {
                                {1.0 , 1.0, 1.0, 1.0},      //Casa
                                {1.0, 0.15, 0.0, 1.0},      //Tejado
                                {0.93, 0.65, 0.05, 1.0},    //Puerta y Ventanas
                                {0.93, 0.8, 0.25, 1.0}      //Entrada
                            };




float colores_arbol[2][4] = {
                                {0.9 , 0.7, 0.5, 1.0},      //Tronco
                                {0.15,1,0.15, 1}          //Hojas
                            };

float colores_banco[4] = {0.9 , 0.7, 0.5, 1.0};

float colores_piramide[2][4] = {
                                {0.75,0.75,0.75, 1.0},      //Piramide y palo
                                {0.93, 0.15, 0.05, 0.8}    //Bola
                            };

float colores_semaforo[5][4] = {
                                {0.85 , 0.85, 0.35, 1.0},      //Palo
                                {0.3, 0.3, 0.3, 1.0},      //Cabeza
                                {0.93, 0.05, 0.05, 1.0},    //Rojo
                                {0.93, 0.7, 0.15, 1.0},      //Naranja
                                {0.2, 1.0, 0.1, 1.0}      //Verde
                            };


int LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
    int Status=TRUE;
	Image *TextureImage[11];

	//memset(TextureImage[0],0,sizeof(void *)*1);

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0]=loadBMP("../../Texturas/camino.bmp"))
	{
		glGenTextures(1, &texturas[0]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texturas[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->width, TextureImage[0]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
    else
        Status=FALSE;

    if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->pixels)							// If Texture Image Exist
			free(TextureImage[0]->pixels);					// Free The Texture Image Memory

		free(TextureImage[0]);								// Free The Image Structure
	}



	if (TextureImage[1]=loadBMP("../../Texturas/ladera.bmp"))
	{
		glGenTextures(1, &texturas[1]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texturas[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->width, TextureImage[1]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else
        Status=FALSE;

    if (TextureImage[1])									// If Texture Exists
	{
		if (TextureImage[1]->pixels)							// If Texture Image Exist
			free(TextureImage[1]->pixels);					// Free The Texture Image Memory

		free(TextureImage[1]);								// Free The Image Structure
	}


	if (TextureImage[2]=loadBMP("../../Texturas/cesped.bmp"))
	{
		glGenTextures(1, &texturas[2]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texturas[2]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[2]->width, TextureImage[2]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[2]->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else
        Status=FALSE;

    if (TextureImage[2])									// If Texture Exists
	{
		if (TextureImage[2]->pixels)							// If Texture Image Exist
			free(TextureImage[2]->pixels);					// Free The Texture Image Memory

		free(TextureImage[2]);								// Free The Image Structure
	}

        //0 camino, 1 ladera,  2 cesped,  3 pared_vieja_textura
        //4 madera_vieja,  5 teja_antigua,  6 arena
	if (TextureImage[3]=loadBMP("../../Texturas/pared_vieja_textura.bmp"))
	{
	    glGenTextures(1, &texturas[3]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texturas[3]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[3]->width, TextureImage[3]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[3]->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else
        Status=FALSE;

    if (TextureImage[3])									// If Texture Exists
	{
		if (TextureImage[3]->pixels)							// If Texture Image Exist
			free(TextureImage[3]->pixels);					// Free The Texture Image Memory

		free(TextureImage[3]);								// Free The Image Structure
	}


	if (TextureImage[4]=loadBMP("../../Texturas/madera_vieja.bmp"))
	{
		glGenTextures(1, &texturas[4]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texturas[4]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[4]->width, TextureImage[4]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[4]->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else
        Status=FALSE;

    if (TextureImage[4])									// If Texture Exists
	{
		if (TextureImage[4]->pixels)							// If Texture Image Exist
			free(TextureImage[4]->pixels);					// Free The Texture Image Memory

		free(TextureImage[4]);								// Free The Image Structure
	}



	if (TextureImage[5]=loadBMP("../../Texturas/teja_antigua.bmp"))
	{
		glGenTextures(1, &texturas[5]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texturas[5]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[5]->width, TextureImage[5]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[5]->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else
        Status=FALSE;

    if (TextureImage[5])									// If Texture Exists
	{
		if (TextureImage[5]->pixels)							// If Texture Image Exist
			free(TextureImage[5]->pixels);					// Free The Texture Image Memory

		free(TextureImage[5]);								// Free The Image Structure
	}


	if (TextureImage[6]=loadBMP("../../Texturas/arena.bmp"))
	{
		glGenTextures(1, &texturas[6]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texturas[6]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[6]->width, TextureImage[6]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[6]->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else
        Status=FALSE;

	if (TextureImage[6])									// If Texture Exists
	{
		if (TextureImage[6]->pixels)							// If Texture Image Exist
			free(TextureImage[6]->pixels);					// Free The Texture Image Memory

		free(TextureImage[6]);								// Free The Image Structure
	}



	if (TextureImage[7]=loadBMP("../../Texturas/madera_banco.bmp"))
	{
		glGenTextures(1, &texturas[7]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texturas[7]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[7]->width, TextureImage[7]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[7]->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else
        Status=FALSE;

	if (TextureImage[7])									// If Texture Exists
	{
		if (TextureImage[7]->pixels)							// If Texture Image Exist
			free(TextureImage[7]->pixels);					// Free The Texture Image Memory

		free(TextureImage[7]);								// Free The Image Structure
	}


	if (TextureImage[8]=loadBMP("../../Texturas/tronco.bmp"))
	{
		glGenTextures(1, &texturas[8]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texturas[8]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[8]->width, TextureImage[8]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[8]->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else
        Status=FALSE;

	if (TextureImage[8])									// If Texture Exists
	{
		if (TextureImage[8]->pixels)							// If Texture Image Exist
			free(TextureImage[8]->pixels);					// Free The Texture Image Memory

		free(TextureImage[8]);								// Free The Image Structure
	}



	if (TextureImage[9]=loadBMP("../../Texturas/hierba.bmp"))
	{
		glGenTextures(1, &texturas[9]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texturas[9]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[9]->width, TextureImage[9]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[9]->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else
        Status=FALSE;

	if (TextureImage[9])									// If Texture Exists
	{
		if (TextureImage[9]->pixels)							// If Texture Image Exist
			free(TextureImage[9]->pixels);					// Free The Texture Image Memory

		free(TextureImage[9]);								// Free The Image Structure
	}

	if (TextureImage[10]=loadBMP("../../Texturas/pared_piedra.bmp"))
	{
		glGenTextures(1, &texturas[10]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texturas[10]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[10]->width, TextureImage[10]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[10]->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else
        Status=FALSE;

	if (TextureImage[10])									// If Texture Exists
	{
		if (TextureImage[10]->pixels)							// If Texture Image Exist
			free(TextureImage[10]->pixels);					// Free The Texture Image Memory

		free(TextureImage[10]);								// Free The Image Structure
	}


	return Status; 										// Return The Status
}



//************************************************************** Variables de clase

TEscena escena;
TGui    gui;

//************************************************************** Clase TPrimitiva

TPrimitiva::TPrimitiva(int DL, int t)
{

    ID   = DL;
    tipo = t;

    //Inicializamos valores de rotacion y escalado para que no pete
    sx = sy = sz = 1;
    rx = ry = rz = 0;
    anguloRuedas = 0;

	switch (tipo) {
	    case SUELO_ID: {  // Creaci�n de la carretera
		    tx = tz = 0;
		    ty = 0.0;
            glNewList(ID, GL_COMPILE);
                glBegin(GL_QUADS);
                    // La perpendicular al suelo es el eje Y
                    glNormal3f(0.0, 1.0, 0.0);
                    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                    glVertex3f( 1000, -0.001, -1000);
                    glTexCoord2f(25.0,0.0);
                    glVertex3f(-1000, -0.001, -1000);
                    glTexCoord2f(0.0,0.0);
                    glVertex3f(-1000, -0.001,  1000);
                    glTexCoord2f(0.0,25.0);
                    glVertex3f( 1000, -0.001,  1000);
                    glTexCoord2f(25.0,25.0);

                glEnd();
            glEndList();
            break;
		}


		case CARRETERA_ID: {  // Creaci�n de la carretera
		    tx = 0;
		    ty = 0.02;
		    tz = 0;
		    rx = 90;
		    ry = 0;
            rz = 90;

            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/carretera_recta.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            break;
		}


		case CARRETERA_LARGA_ID: {  // Creaci�n de la carretera
		    tx = 0;
		    ty = 0.04;
		    tz = 0;
		    rx = 90;
		    ry = 0;
            rz = 90;

            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/carretera_larga.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            break;
		}


		case COCHE_ID: { // Creaci�n del coche

            tx = 0;
		    ty = 0.31;
		    tz = 0;
		    v = 0;

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/coche.3ds", &num_vertices);

            glNewList(COCHE_ID, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);


            //************************ Cargar modelos ***********************************
            num_vertices = 0;

            modelo = Load3DS("../../Modelos/rueda.3ds", &num_vertices);

            glNewList(COCHE_ID+RUEDA, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;

            modelo = Load3DS("../../Modelos/coche_marcador.3ds", &num_vertices);

            glNewList(COCHE_ID+MARCADOR, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            break;
		}

		/********************************************** FAROLA */
		case FAROLA_ID: {

		    tx = 10;
		    ty = 0;
		    tz = 1;
		    rx = -90;
            sx = sy = sz = 0.67;

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/farola_base.3ds", &num_vertices);

            glNewList(ID+FAROLA_BASE, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/farola_capucha.3ds", &num_vertices);

            glNewList(ID+FAROLA_CAPUCHA, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/farola_cristal.3ds", &num_vertices);

            glNewList(ID+FAROLA_CRISTAL, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
		}

		case CASA_ID: { // Creaci�n del coche

            tx = tz = 0;
            ty = 0.05;

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/casa_base.3ds", &num_vertices);

            glNewList(CASA_ID+CASA_BASE, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/casa_tejado.3ds", &num_vertices);

            glNewList(CASA_ID+CASA_TEJADO, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/casa_ventanas.3ds", &num_vertices);

            glNewList(CASA_ID+CASA_VENTANAS, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/casa_puerta.3ds", &num_vertices);

            glNewList(CASA_ID+CASA_PUERTA, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);


            num_vertices = 0;
            modelo = Load3DS("../../Modelos/casa_entrada.3ds", &num_vertices);

            glNewList(CASA_ID+CASA_ENTRADA, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            break;
		}

		case LADERA_BAJA_ID: {  // Creaci�n de la carretera
		    tx = tz = 0;
		    ty = -0.3;
		    sx = sy = sz = 3;

            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/ladera_baja.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            break;
		}

		case LADERA_ALTA_ID: {  // Creaci�n de la carretera
		    tx = tz = 0;
		    ty = -0.3;
		    sx = sy = sz = 3.7;
		    rx = -90;

            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/ladera_alta.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            break;
		}

		/********************************************** PIRAMIDE */
		case PIRAMIDE_ID: {

            sx = sy = sz = 1.5;

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/piramide_base.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/piramide_palo.3ds", &num_vertices);

            glNewList(ID+1, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/piramide_bola.3ds", &num_vertices);

            glNewList(ID+2, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
		}



		/********************************************** SEMAFORO */
		case SEMAFORO_ID: {

            //sx = sy = sz = 0.67;

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/semaforo_palo.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/semaforo_cabeza.3ds", &num_vertices);

            glNewList(ID+1, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/semaforo_bola_verde.3ds", &num_vertices);

            glNewList(ID+2, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/semaforo_bola_naranja.3ds", &num_vertices);

            glNewList(ID+3, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/semaforo_bola_rojo.3ds", &num_vertices);

            glNewList(ID+4, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
		}


		/********************************************** ARBOL */
		case ARBOL_ID: {

<<<<<<< HEAD
            sx = sy = sz = 1.35;
=======
            sx = sy = sz = 1.25;
>>>>>>> 787514e29c3856a12eeb7ad9c973bf3c9735b82e
            rz=180;

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/arbol_palo.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/arbol_hojas.3ds", &num_vertices);

            glNewList(ID+1, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
		}


		/********************************************** BANCO */
		case BANCO_ID: {

            sx = sy = sz = 2.15;

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/banco.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
                glBegin(GL_TRIANGLES);
                    for (int i = 0; i < num_vertices; i++)
                    {
                        // << 3 = * 8
                        glNormal3fv((float*) & modelo[i << 3] + 3);
                        glTexCoord2fv((float*) & modelo[i << 3] + 6);
                        glVertex3fv((float*) & modelo[i << 3]);
                    }
                glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
		}

	} // fin del case
}

void __fastcall TPrimitiva::Render(int seleccion, bool reflejo)
{
    switch (tipo) {

        case SUELO_ID: {

            glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
            glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);

            if(escena.textura)
            {
                glColor4fv(color_blanco);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[2]);
            }
            else
                glColor4fv(color_suelo);

            glLoadName(0);  // No seleccionable
            glCallList(ID);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            break;
        }


        case CARRETERA_ID:
        case CARRETERA_LARGA_ID:{

            glPushMatrix();
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);

            if (escena.show_road)
            {
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
                glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
                glMaterialfv(GL_FRONT, GL_SHININESS, bajoResplandor);
                glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);

                if(reflejo)
                {
                    if(escena.textura)
                    {
                        glColor4f(colores_carr_claro[0],colores_carr_claro[1],colores_carr_claro[2],0.85f);
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D, texturas[0]);
                    }
                    else
                        glColor4f(colores_carr_claro[0],colores_carr_claro[1],colores_carr_claro[2],0.7f);

                    glEnable(GL_BLEND);									// Enable Blending (Otherwise The Reflected Object Wont Show)
                    glDisable(GL_LIGHTING);								// Since We Use Blending, We Disable Lighting
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                    glLoadName(0); //No seleccionable
                    glCallList(ID);
                    glDisable(GL_BLEND);
                    glDisable(GL_TEXTURE_2D);
                    glEnable(GL_LIGHTING);								// Enable Lighting

                }
                else{
                    if(escena.textura)
                    {
                        glColor4fv(colores_carr_claro);
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D, texturas[0]);
                    }
                    else
                        glColor4fv(colores_carr_claro);

                    glLoadName(0); //No seleccionable
                    glCallList(ID);
                    glDisable(GL_TEXTURE_2D);
                }
            }

            glPopMatrix();
            break;
        }


        case COCHE_ID: {

            glPushMatrix();

            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);

            //velocidad del coche
            if( v != 0)
            {
                ry += (anguloRuedas * v);
                float angulo = (ry*PI)/180.0;


                float coseno = cos(angulo);
                float seno = sin(angulo);

                tz += v * coseno;
                tx += v * seno;


                rr += v*DESLIZ_RUEDA;

                if(v > 0){
                    v -= COEF_ROZ;

                    if(v<=0)
                        v=0;
                }
                else if(v < 0){
                    v += COEF_ROZ;

                    if(v >= 0)
                        v = 0;
                }
            }

            if (escena.show_wheels)
            {
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
                glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
                glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
                glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
                glColor4fv(colores_c[1]);
                glPushMatrix();                     //Rueda 0 DEL, DER
                    glTranslated(-1.18, 0.49, 4.04);
                    glRotated(anguloRuedas, 0, 1 ,0);
                    glRotated(rr, 1, 0 ,0);
                   // glRotated(180, 0, 0, 1);
                    glLoadName(ID);
                    glCallList(ID+RUEDA);
                glPopMatrix();

                glPushMatrix();                     //Rueda 1 DEL, IZQ
                    glTranslated(1.18, 0.49, 4.04);
                    glRotated(anguloRuedas, 0, 1 ,0);
                    glRotated(rr, 1, 0 ,0);
                    glLoadName(ID);
                    glCallList(ID+RUEDA);
                glPopMatrix();

                glPushMatrix();                     //Rueda 2 DER, DEL
                    glTranslated(-1.18, 0.49, -1.21);
                    glRotated(rr, 1, 0 ,0);
                    //glRotated(180, 0, 0, 1);
                    glLoadName(ID);
                    glCallList(ID+RUEDA);
                glPopMatrix();

                glPushMatrix();                     //Rueda 3 DER, TRAS
                    glTranslated(1.18, 0.49, -1.21);
                    glRotated(rr, 1, 0 ,0);
                    glLoadName(ID);
                    glCallList(ID+RUEDA);
                glPopMatrix();
            }


            if (escena.show_car)
            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

                if(seleccion==ID)
                {
                    glPushMatrix();
                    glTranslated(0, -0.17, 1.27);
                    glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
                    glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
                    glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
                    glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);

                    glColor4f(0.03,0.18,1.0,0.6);
                    glCallList(ID+MARCADOR);
                    glPopMatrix();
                }

                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, difCoche);

                float v[] = { espCoche[0], espCoche[1],
                                espCoche[2], espCoche[3] };

                v[0] *= brilloCoche[0];
                v[1] *= brilloCoche[0];
                v[2] *= brilloCoche[0];

                glMaterialfv(GL_FRONT, GL_SPECULAR, v);
                glMaterialfv(GL_FRONT, GL_SHININESS, lumCoche);
                glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);

                glColor4fv(colores_c[0]);
                glLoadName(ID);
                glCallList(ID);
            }

            glDisable(GL_BLEND);
<<<<<<< HEAD
            glPopMatrix();


            break;
        }


        /************************* FAROLA */
        case FAROLA_ID: {

            glPushMatrix();

            // Traslaci�n del objeto FAROLA
            glScaled(sx,sy,sz);
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);

            if (escena.show_farola_base)
            {
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
                glMaterialfv(GL_FRONT, GL_SPECULAR, esp);
                glMaterialfv(GL_FRONT, GL_SHININESS, medioResplandor);
                glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
                glColor4fv(colores_farola[0]);
                glLoadName(0);
                glCallList(ID+FAROLA_BASE);
            }

            if (escena.show_farola_capucha)
            {
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
                glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
                glMaterialfv(GL_FRONT, GL_SHININESS, bajoResplandor);
                glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
                glColor4fv(colores_farola[1]);
                glLoadName(0);
                glCallList(ID+FAROLA_CAPUCHA);

                glEnable(GL_BLEND);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
                glMaterialfv(GL_FRONT, GL_SPECULAR, esp);
                glMaterialfv(GL_FRONT, GL_SHININESS, medioResplandor);
                glMaterialfv(GL_FRONT, GL_EMISSION, matEmision);
                glColor4fv(colores_farola[2]);
                glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                glLoadName(0);
                glCallList(ID+FAROLA_CRISTAL);
                glDisable(GL_BLEND);
            }
            glPopMatrix();
            break;
        }

        case CASA_ID: {

            glPushMatrix();

            // Traslaci�n del objeto CASA
            glScaled(sx,sy,sz);
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);

            if (escena.show_casa)
            {

                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
                glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
                glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
                glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);

                if(escena.textura)
                {
                    glColor4fv(color_blanco);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texturas[3]);
                }
                else
                    glColor4fv(colores_casa[0]);

                glLoadName(0);
                glCallList(ID+CASA_BASE);
                glDisable(GL_TEXTURE_2D);


                if(escena.textura)
                {
                    glColor4fv(color_blanco);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texturas[5]);
                }
                else
                    glColor4fv(colores_casa[1]);

                glLoadName(0);
                glCallList(ID+CASA_TEJADO);
                glDisable(GL_TEXTURE_2D);

                if(escena.textura)
                {
                    glColor4fv(color_blanco);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texturas[4]);
                }
                else
                    glColor4fv(colores_casa[2]);

                glLoadName(0);
                glCallList(ID+CASA_VENTANAS);
                glDisable(GL_TEXTURE_2D);

                if(escena.textura)
                {
                    glColor4fv(color_blanco);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texturas[4]);
                }
                else
                    glColor4fv(colores_casa[2]);

                glLoadName(0);
                glCallList(ID+CASA_PUERTA);
                glDisable(GL_TEXTURE_2D);


                if(escena.textura)
                {
                    glColor4fv(color_blanco);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texturas[6]);
                }
                else
                    glColor4fv(colores_casa[3]);

                glLoadName(0);
                glCallList(ID+CASA_ENTRADA);
                glDisable(GL_TEXTURE_2D);
            }
            glPopMatrix();
            break;
        }

        case LADERA_ALTA_ID: {

            glPushMatrix();
            glTranslated(tx, ty, tz);
            glScaled(sx,sy,sz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);

            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
            glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);

            if(escena.textura)
            {
                glColor4fv(color_blanco);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[1]);
            }
            else
                glColor4fv(color_suelo);

            glLoadName(0); //No seleccionable
            glCallList(ID);

            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
            break;
        }

        case LADERA_BAJA_ID: {

            glPushMatrix();
            glTranslated(tx, ty, tz);
            glScaled(sx,sy,sz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);

            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
            glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);

            if(escena.textura)
            {
                glColor4fv(color_blanco);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[1]);
            }
            else
                glColor4fv(color_suelo);

            glLoadName(0); //No seleccionable
            glCallList(ID);

            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
            break;
        }

        /************************* SEMAFORO */
        case SEMAFORO_ID: {

            glPushMatrix();

            glScaled(sx,sy,sz);
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);
        //palo
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
            glMaterialfv(GL_FRONT, GL_SPECULAR, esp);
            glMaterialfv(GL_FRONT, GL_SHININESS, medioResplandor);
            glColor4fv(colores_semaforo[0]);
            glLoadName(0);
            glCallList(ID);
        //cabeza
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
            glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
            glColor4fv(colores_semaforo[1]);
            glLoadName(0);
            glCallList(ID+1);
        //rojo
            glColor4fv(colores_semaforo[2]);
            glLoadName(0);
            glCallList(ID+4);
        //naranja
            glColor4fv(colores_semaforo[3]);
            glLoadName(0);
            glCallList(ID+3);
        //verde
            glColor4fv(colores_semaforo[4]);
            glLoadName(0);
            glCallList(ID+2);

=======
>>>>>>> 787514e29c3856a12eeb7ad9c973bf3c9735b82e
            glPopMatrix();


            break;
<<<<<<< HEAD
        }

        /************************* ARBOL */
        case ARBOL_ID: {
=======
        }


        /************************* FAROLA */
        case FAROLA_ID: {
>>>>>>> 787514e29c3856a12eeb7ad9c973bf3c9735b82e

            glPushMatrix();

            glScaled(sx,sy,sz);
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);
        //palo
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
            glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
            if(escena.textura)
            {
<<<<<<< HEAD
                glColor4fv(color_blanco);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[8]);
=======
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
                glMaterialfv(GL_FRONT, GL_SPECULAR, esp);
                glMaterialfv(GL_FRONT, GL_SHININESS, medioResplandor);
                glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
                glColor4fv(colores_farola[0]);
                glLoadName(0);
                glCallList(ID+FAROLA_BASE);
>>>>>>> 787514e29c3856a12eeb7ad9c973bf3c9735b82e
            }
            else
                glColor4fv(colores_arbol[0]);

            glLoadName(0);
            glCallList(ID);
        //hojas
            if(escena.textura)
            {
<<<<<<< HEAD
                glColor4fv(color_blanco);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[9]);
=======
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
                glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
                glMaterialfv(GL_FRONT, GL_SHININESS, bajoResplandor);
                glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
                glColor4fv(colores_farola[1]);
                glLoadName(0);
                glCallList(ID+FAROLA_CAPUCHA);

                glEnable(GL_BLEND);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
                glMaterialfv(GL_FRONT, GL_SPECULAR, esp);
                glMaterialfv(GL_FRONT, GL_SHININESS, medioResplandor);
                glMaterialfv(GL_FRONT, GL_EMISSION, matEmision);
                glColor4fv(colores_farola[2]);
                glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                glLoadName(0);
                glCallList(ID+FAROLA_CRISTAL);
                glDisable(GL_BLEND);
>>>>>>> 787514e29c3856a12eeb7ad9c973bf3c9735b82e
            }
            else
                glColor4fv(colores_arbol[1]);

            glLoadName(0);
            glCallList(ID+1);

            glDisable(GL_TEXTURE_2D);
            glPopMatrix();
            break;
        }

        /************************* PIRAMIDE */
        case PIRAMIDE_ID: {

            glPushMatrix();

            glScaled(sx,sy,sz);
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);
        //base
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
            glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
            if(escena.textura)
            {
<<<<<<< HEAD
                glColor4fv(color_blanco);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[10]);
            }
            else
                glColor4fv(colores_piramide[0]);

            glLoadName(0);
            glCallList(ID);

        //palo
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
            glMaterialfv(GL_FRONT, GL_SPECULAR, esp);
            glMaterialfv(GL_FRONT, GL_SHININESS, medioResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
            glColor4fv(colores_piramide[0]);
            glLoadName(0);
            glCallList(ID+1);
        //bola
            glEnable(GL_BLEND);
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, colores_piramide[1]);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
            glMaterialfv(GL_FRONT, GL_SPECULAR, esp);
            glColor4fv(colores_piramide[1]);
            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            glLoadName(0);
            glCallList(ID+2);
            glDisable(GL_BLEND);

            //palo
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
                glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
                glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
                glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);

            glPushMatrix();
            glScaled(1.1,1.1,1.1);
            glRotated(180.0, 0, 0, 1);
        //Arboles
            for(int i=0; i<8; i++)
            {
                glPushMatrix();
                glTranslated(pos_arboles[i][0], 0, pos_arboles[i][1]);

=======

                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
                glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
                glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
                glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);

                if(escena.textura)
                {
                    glColor4fv(color_blanco);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texturas[3]);
                }
                else
                    glColor4fv(colores_casa[0]);

                glLoadName(0);
                glCallList(ID+CASA_BASE);
                glDisable(GL_TEXTURE_2D);


                if(escena.textura)
                {
                    glColor4fv(color_blanco);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texturas[5]);
                }
                else
                    glColor4fv(colores_casa[1]);

                glLoadName(0);
                glCallList(ID+CASA_TEJADO);
                glDisable(GL_TEXTURE_2D);

                if(escena.textura)
                {
                    glColor4fv(color_blanco);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texturas[4]);
                }
                else
                    glColor4fv(colores_casa[2]);

                glLoadName(0);
                glCallList(ID+CASA_VENTANAS);
                glDisable(GL_TEXTURE_2D);

>>>>>>> 787514e29c3856a12eeb7ad9c973bf3c9735b82e
                if(escena.textura)
                {
                    glColor4fv(color_blanco);
                    glEnable(GL_TEXTURE_2D);
<<<<<<< HEAD
                    glBindTexture(GL_TEXTURE_2D, texturas[8]);
                }
                else
                    glColor4fv(colores_arbol[0]);

                glLoadName(0);
                glCallList(ARBOL_ID);
            //hojas
=======
                    glBindTexture(GL_TEXTURE_2D, texturas[4]);
                }
                else
                    glColor4fv(colores_casa[2]);

                glLoadName(0);
                glCallList(ID+CASA_PUERTA);
                glDisable(GL_TEXTURE_2D);


>>>>>>> 787514e29c3856a12eeb7ad9c973bf3c9735b82e
                if(escena.textura)
                {
                    glColor4fv(color_blanco);
                    glEnable(GL_TEXTURE_2D);
<<<<<<< HEAD
                    glBindTexture(GL_TEXTURE_2D, texturas[9]);
                }
                else
                    glColor4fv(colores_arbol[1]);

                glLoadName(0);
                glCallList(ARBOL_ID+1);
                glPopMatrix();
            }
            glPopMatrix();

            glDisable(GL_TEXTURE_2D);
=======
                    glBindTexture(GL_TEXTURE_2D, texturas[6]);
                }
                else
                    glColor4fv(colores_casa[3]);

                glLoadName(0);
                glCallList(ID+CASA_ENTRADA);
                glDisable(GL_TEXTURE_2D);
            }
>>>>>>> 787514e29c3856a12eeb7ad9c973bf3c9735b82e
            glPopMatrix();
            break;
        }

        //********************* BANCO
        case BANCO_ID: {

            glPushMatrix();
<<<<<<< HEAD
=======
            glTranslated(tx, ty, tz);
            glScaled(sx,sy,sz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);

            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
            glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);

            if(escena.textura)
            {
                glColor4fv(color_blanco);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[1]);
            }
            else
                glColor4fv(color_suelo);

            glLoadName(0); //No seleccionable
            glCallList(ID);

            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
            break;
        }

        case LADERA_BAJA_ID: {
>>>>>>> 787514e29c3856a12eeb7ad9c973bf3c9735b82e

            glScaled(sx,sy,sz);
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);

            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
            glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
<<<<<<< HEAD
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
=======
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);

>>>>>>> 787514e29c3856a12eeb7ad9c973bf3c9735b82e
            if(escena.textura)
            {
                glColor4fv(color_blanco);
                glEnable(GL_TEXTURE_2D);
<<<<<<< HEAD
                glBindTexture(GL_TEXTURE_2D, texturas[7]);
            }
            else
                glColor4fv(colores_banco);
=======
                glBindTexture(GL_TEXTURE_2D, texturas[1]);
            }
            else
                glColor4fv(color_suelo);

            glLoadName(0); //No seleccionable
            glCallList(ID);
>>>>>>> 787514e29c3856a12eeb7ad9c973bf3c9735b82e

            glLoadName(0);
            glCallList(ID);

            glDisable(GL_TEXTURE_2D);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
            break;
        }

        /************************* SEMAFORO */
        case SEMAFORO_ID: {

            glPushMatrix();

            glScaled(sx,sy,sz);
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);
        //palo
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
            glMaterialfv(GL_FRONT, GL_SPECULAR, esp);
            glMaterialfv(GL_FRONT, GL_SHININESS, medioResplandor);
            glColor4fv(colores_semaforo[0]);
            glLoadName(0);
            glCallList(ID);
        //cabeza
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
            glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
            glColor4fv(colores_semaforo[1]);
            glLoadName(0);
            glCallList(ID+1);
        //rojo
            glColor4fv(colores_semaforo[2]);
            glLoadName(0);
            glCallList(ID+4);
        //naranja
            glColor4fv(colores_semaforo[3]);
            glLoadName(0);
            glCallList(ID+3);
        //verde
            glColor4fv(colores_semaforo[4]);
            glLoadName(0);
            glCallList(ID+2);

            glPopMatrix();
            break;
        }

        /************************* ARBOL */
        case ARBOL_ID: {

            glPushMatrix();

            glScaled(sx,sy,sz);
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);
        //palo
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
            glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
            if(escena.textura)
            {
                glColor4fv(color_blanco);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[8]);
            }
            else
                glColor4fv(colores_arbol[0]);

            glLoadName(0);
            glCallList(ID);
        //hojas
            if(escena.textura)
            {
                glColor4fv(color_blanco);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[9]);
            }
            else
                glColor4fv(colores_arbol[1]);

            glLoadName(0);
            glCallList(ID+1);

            glDisable(GL_TEXTURE_2D);
            glPopMatrix();
            break;
        }

        /************************* PIRAMIDE */
        case PIRAMIDE_ID: {

            glPushMatrix();

            glScaled(sx,sy,sz);
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);
        //base
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
            glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
            if(escena.textura)
            {
                glColor4fv(color_blanco);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[10]);
            }
            else
                glColor4fv(colores_piramide[0]);

            glLoadName(0);
            glCallList(ID);

        //palo
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
            glMaterialfv(GL_FRONT, GL_SPECULAR, esp);
            glMaterialfv(GL_FRONT, GL_SHININESS, medioResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
            glColor4fv(colores_piramide[0]);
            glLoadName(0);
            glCallList(ID+1);
        //bola
            glEnable(GL_BLEND);
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, colores_piramide[1]);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
            glMaterialfv(GL_FRONT, GL_SPECULAR, esp);
            glColor4fv(colores_piramide[1]);
            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            glLoadName(0);
            glCallList(ID+2);
            glDisable(GL_BLEND);

            glDisable(GL_TEXTURE_2D);
            glPopMatrix();
            break;
        }

        //********************* BANCO
        case BANCO_ID: {

            glPushMatrix();

            glScaled(sx,sy,sz);
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);

            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materialNulo);
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialNulo);
            glMaterialfv(GL_FRONT, GL_SHININESS, noResplandor);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialNulo);
            if(escena.textura)
            {
                glColor4fv(color_blanco);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[7]);
            }
            else
                glColor4fv(colores_banco);

            glLoadName(0);
            glCallList(ID);

            glDisable(GL_TEXTURE_2D);
            glPopMatrix();
            break;
        }
    }
}




//************************************************************** Clase TEscena

TEscena::TEscena() {

    ultimoSelec=0;

    raton=0;
    rotacionX=0;
    rotacionY=0;
    rotacionZ=0;

    seleccion = 0;
    num_objects = 0;
    num_cars = 0;
    num_floors = 0;

    show_car = 1;
    show_wheels = 1;
    show_road = 1;

    show_farola_base = 1;
    show_farola_capucha = 1;
    show_charco = 1;
    show_casa = 1;
    tipoVista = 0;

    // live variables usadas por GLUI en TGui
    textura=1;
    wireframe = 0;
    z_buffer = 1;
    culling = 0;
    sombra=1;
    sentido=0;
    luzAmbiente=1;
    camaraSeguimiento=0;
    vistaAerea=0;
    primeraPersona=0;
    factorMovCam=0.7;
    cuantaLuzAmbiente = 0.8;

    scale = 1.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;

    memcpy(view_position, view_position_c, 3*sizeof(float));
    memcpy(view_rotate, view_rotate_c, 16*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));
    memcpy(light0_diffuse, light0_diffuse_c, 4*sizeof(float));
    memcpy(light0_specular, light0_specular_c, 4*sizeof(float));
    memcpy(light0_position, light0_position_c, 4*sizeof(float));

    memcpy(light1_ambient, light1_ambient_c, 4*sizeof(float));
    memcpy(light1_diffuse, light1_diffuse_c, 4*sizeof(float));
    memcpy(light1_specular, light1_specular_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));

    memcpy(light2_ambient, light2_ambient_c, 4*sizeof(float));
    memcpy(light2_diffuse, light2_diffuse_c, 4*sizeof(float));
    memcpy(light2_specular, light2_specular_c, 4*sizeof(float));
    memcpy(light2_position, light2_position_c, 4*sizeof(float));

    memcpy(mat_ambient, mat_ambient_c, 4*sizeof(float));
    memcpy(mat_diffuse, mat_diffuse_c, 4*sizeof(float));
    memcpy(mat_specular, mat_specular_c, 4*sizeof(float));
    memcpy(high_shininess, high_shininess_c, 1*sizeof(float));
}

void __fastcall TEscena::InitGL()
{
    if (!LoadGLTextures())								// Jump To Texture Loading Routine ( NEW )
	{
		return;									// If Texture Didn't Load Return FALSE
	}

    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );

    escena.xy_aspect = (float)tw / (float)th;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, escena.xy_aspect, 1.0, 1000.0); // No se deber�an tocar estos valores

    glMatrixMode(GL_MODELVIEW);

    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.2f, 0.5f, 1.0f, 1.0f);				// Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear The Stencil Buffer To 0
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //o GL_LINE

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_AMBIENT,  light2_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  light2_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    GLfloat arrLuzAmbiente[4];
    GLfloat arrLuzAmbienteDividido[4];

    for(int i = 0; i< 4; i++)
    {
        arrLuzAmbiente[i]=escena.cuantaLuzAmbiente;
        arrLuzAmbienteDividido[i]=escena.cuantaLuzAmbiente/5;
    }


    //glClearColor(0.0, 0.5, 1.0, 1.0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, arrLuzAmbienteDividido);
    glLightfv(GL_LIGHT1, GL_AMBIENT, arrLuzAmbienteDividido );
    glLightfv(GL_LIGHT2, GL_AMBIENT, arrLuzAmbienteDividido );
    glMaterialfv(GL_FRONT, GL_AMBIENT, arrLuzAmbiente);

}


/************************** TEscena::AddCar(TPrimitiva *car) *****************/

void __fastcall TEscena::AddCar(TPrimitiva *car)
{
    cars[num_cars] = car;
    num_cars++;
}

/******************** TEscena::AddObject(TPrimitiva *object) *****************/

void __fastcall TEscena::AddObject(TPrimitiva *object)
{
    objects[num_objects] = object;
    num_objects++;
}

void __fastcall TEscena::AddFloor(TPrimitiva *object)
{
    floors[num_floors] = object;
    num_floors++;
}

/******************** TPrimitiva *TEscena::GetCar(int id) ********************/

TPrimitiva __fastcall *TEscena::GetCar(int id)
{
    TPrimitiva *p=NULL;

    for (int i=0; i<num_cars; i++)
    {
        if (cars[i]->ID==id)
        {
            p = cars[i];
        }

    }
    return(p);
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderCars(bool reflejo) {

    for (int i=0; i<num_cars; i++)
    {
        cars[i]->Render(seleccion, reflejo);
    }
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderObjects(bool reflejo) {

    for (int i=0; i<num_objects; i++)
    {
        objects[i]->Render(seleccion, reflejo);
    }
}

void __fastcall TEscena::RenderFloors(bool reflejo) {

    for (int i=0; i<num_floors; i++)
    {
        floors[i]->Render(seleccion, reflejo);
    }
}

/***************************************** TEscena::Render() *****************/

void __fastcall TEscena::Render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Clip Plane Equations para la reflexion
	double eqr[] = {0.0f,-1.0f, 0.0f, 0.0f};

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Transformaci�n del escenario
    glTranslatef( view_position[0], view_position[1], view_position[2] );   // Traslaci�n
    glMultMatrixf(view_rotate);                                             // Rotaci�n
    glScalef(scale, scale, scale);                                          // Escalado


//*********************************CAMARA SEGUIMIENTO
    if(escena.camaraSeguimiento==1)
    {
        TPrimitiva *cam = NULL;
        cam = GetCar(seleccion);   //Obtenemos el coche

        if(cam)     //Situamos camara detr�s del coche
        {
            float angulo = (cam->ry*PI)/180.0;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(cam->tx-20*sin(angulo),cam->ty+10,cam->tz-20*cos(angulo),cam->tx,cam->ty+5,cam->tz,0,1,0);
        }
    }
//*********************************VISTA AEREA
    else if(escena.vistaAerea == 1)
    {
        //Obtenemos el coche
        TPrimitiva *cam = NULL;
        cam = GetCar(seleccion);

        //Situamos camara arriba del coche
        if(cam)
        {
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            //PosCamX,PosCamY,PosCamZ,  DondeMiraX,DondeMiraY,DondeMiraZ,   0,1,0
            gluLookAt(cam->tx,cam->ty+150,cam->tz,cam->tx,cam->ty,cam->tz,0,0,1);
        }
    }

    else if(escena.primeraPersona == 1)
    {
        //Obtenemos el coche
        TPrimitiva *cam = NULL;
        cam = GetCar(seleccion);

        //Situamos camara detr�s del coche
        if(cam)
        {
            float angulo = (cam->ry*PI)/180.0;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            //PosCamX,PosCamY,PosCamZ,  DondeMiraX,DondeMiraY,DondeMiraZ,   0,1,0(direccion arriba camara)
            gluLookAt(cam->tx+sin(angulo),cam->ty+2,cam->tz+cos(angulo),cam->tx+5*sin(angulo),cam->ty+2,cam->tz+5*cos(angulo),0,1,0);
        }
    }

    if(escena.reflejo)
    {
        //Seteamos el Stencil Buffer a 0's para escribir en �l
        glColorMask(0,0,0,0);
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS, 1, 1);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glDisable(GL_DEPTH_TEST);

        //Renderizamos el suelo para que se escriba en el Stencil Buffer
        RenderFloors(0);

        //Cambiamos modo para poder escribir en el Stencil Buffer
        glEnable(GL_DEPTH_TEST);
        glColorMask(1,1,1,1);
        glStencilFunc(GL_EQUAL, 1, 1);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

        //Aplicamos plano de recortado definido por la ecuaci�n eqr
        glEnable(GL_CLIP_PLANE0);
        glClipPlane(GL_CLIP_PLANE0, eqr);

        //Pintamos todos los objetos en forma de Espejo en Y (Semitransparentes)
        glPushMatrix();
            glScalef(1.0f, -1.0f, 1.0f);
            glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
            glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
            glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
            glTranslated(0,-0.18,0);
            RenderCars(seleccion);
			RenderObjects(seleccion);
        glPopMatrix();

        //Deshabilitamos plano de recortado y dibujamos suelo semitransparente
        glDisable(GL_CLIP_PLANE0);
        glDisable(GL_STENCIL_TEST);
        RenderFloors(1);
	}
    else
        RenderFloors(0);


    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

    RenderCars(seleccion);
    // Dibujar carretera y objetos
    RenderObjects(seleccion);



    glutSwapBuffers();  //Intercambia buffers (recordar que estamos usando doble buffer)
}

// Selecciona un objeto a trav�s del rat�n
void __fastcall TEscena::Pick3D(int mouse_x, int mouse_y)
{
	// formato de buffer, cada cuatro posiciones almacena:
	//      buffer[i]   = n�mero de objetos
    //      buffer[i+1] = profundidad m�nima
    //      buffer[i+2] = profuncidad m�xima
    //      buffer[i+3] = nombre de la pila

    // Tama�o de la ventana (Viewport) [0] es <x>, [1] es <y>, [2] es <ancho>, [3] es <alto>
    GLint	viewport[4];
    GLuint	buffer[2048];
    GLint   hits;
    int     profundidad;
    char    cad[80];
    int     tx, ty, tw, th;

    seleccion = 0;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    glViewport( tx, ty, tw, th );

    // Establece el vector <viewport> al tama�o y posici�n relativa a la ventana de visualizaci�n
    glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(2048, buffer);  // usa <buffer> como nuestro vector para seleccionar

    (void) glRenderMode(GL_SELECT); // Modo Render en SELECCION

	glInitNames();				  // Inicializa la pila de nombres
    glPushName(0);				  // Apila 0 (al menos una entrada) en la pila
    glMatrixMode(GL_PROJECTION);  // Selecciona el modo proyecci�n
    glPushMatrix();				  // Apila la matriz de proyecci�n
    glLoadIdentity();			  // Resetea la matriz (matriz identidad) IMPORTANTE
    // Crea una matriz que agranda la peque�a porci�n de pantalla donde se ecuentra el rat�n
    gluPickMatrix((GLdouble) mouse_x, (GLdouble) (viewport[3]+viewport[1]-mouse_y), 1.0f, 1.0f, viewport);

    // Aplica la Matriz de Perspectiva
    //gluPerspective(45.0f, (GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 1.0, 1000.0);
    gluPerspective(45, xy_aspect, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);	   	// Selecciona la matriz de ModelView
    Render();	 		   			// Renderiza los objetos a seleccionar
    glMatrixMode(GL_PROJECTION);   	// Selecciona la matriz de Proyecci�n
    glPopMatrix();				   	// Recupera la matriz de Proyecci�n
    glMatrixMode(GL_MODELVIEW);	   	// Selecciona la matriz de ModelView
    hits=glRenderMode(GL_RENDER);  	// Cambia a modo RENDERIZAR

    if (hits > 0)				   	// Si hay m�s de un objeto
                                   	// (Hits=n�mero de objetos que se hallan en la posici�n del rat�n)
    {
        seleccion = buffer[3];		// Coge como selecci�n el primer objeto de la lista
        profundidad = buffer[1];    // Calcula su profundidad

        for (int i = 1; i < hits; i++)  // Recorre todos los objetos
        {
			// Si el objetos est� m�s cerca que el seleccionado ahora
            if (buffer[i*4+1] < GLuint(profundidad))
			{
            	seleccion = buffer[i*4+3];	    // Selecciona dicho objeto
                profundidad = buffer[i*4+1];	// Calcula su profundidad
            }
		}
    }

    if(seleccion != 0)
        escena.ultimoSelec= seleccion;

    sprintf(cad, "%03d [%03d, %03d]", seleccion, mouse_x, mouse_y);
    gui.sel_tex->set_text(cad);
}

//************************************************************** Clase TGui

TGui::TGui()
{
    enable_panel2 = 1;
    luzAmbiente = 1;
    light0_enabled = 1;
    light1_enabled = 1;
    light2_enabled = 1;
    light0_intensity = 1.0;
    light1_intensity = 1.0;
    light2_intensity = 1.0;
}

void controlCallback(int control)
{
    gui.ControlCallback(control);
}

void __fastcall TGui::Init(int main_window) {

    /****************************************************/
    /*        C�digo con el interfaz Gr�fico GLUI       */
    /****************************************************/
    printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

    window_id = main_window;

    /*** Crea a ventana lateral ***/
    glui = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_RIGHT );

    obj_panel = new GLUI_Rollout(glui, "Propiedades", true );
    GLUI_Scrollbar *sb;
    /***** Control para las propiedades de escena *****/

    new GLUI_Checkbox( obj_panel, "Modo Alambrico", &escena.wireframe, WIREFRAME_ID, controlCallback );
    new GLUI_Checkbox( obj_panel, "Z Buffer", &escena.z_buffer, ZBUFFER_ID, controlCallback );
    new GLUI_Checkbox( obj_panel, "Culling", &escena.culling, CULLING_ID, controlCallback );
    new GLUI_Checkbox( obj_panel, "Sentido AntiHorario", &escena.sentido, 1, controlCallback );
    new GLUI_Checkbox( obj_panel, "Sombra Suave", &escena.sombra, 1, controlCallback );
    new GLUI_Checkbox( obj_panel, "Texturas", &escena.textura, 1, controlCallback );
    new GLUI_Checkbox( obj_panel, "Reflejo", &escena.reflejo, 1, controlCallback );

    new GLUI_StaticText( obj_panel, "" );
    new GLUI_StaticText( obj_panel, "Factor Camara Movimiento" );
    sb = new GLUI_Scrollbar( obj_panel, "Facto MovCam",GLUI_SCROLL_HORIZONTAL,
                            &escena.factorMovCam,1,controlCallback);
    sb->set_float_limits(0.03,1);

    new GLUI_Button( glui, "Vista Seguimiento", V_SEGUIMIENTO, controlCallback );
    new GLUI_Button( glui, "Primera Persona", V_PRIMERAPERSONA, controlCallback );
    new GLUI_Button( glui, "Vista Aerea", V_AEREA, controlCallback );

    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *roll_coche = new GLUI_Rollout(glui, "Coche", false );

    GLUI_Panel *color = new GLUI_Panel( roll_coche, "Color" );

    sb = new GLUI_Scrollbar( color, "Rojo",GLUI_SCROLL_HORIZONTAL,
                            &colores_c[0][0],1,controlCallback);
    sb->set_float_limits(0,1);
    sb = new GLUI_Scrollbar( color, "Verde",GLUI_SCROLL_HORIZONTAL,
                            &colores_c[0][1],1,controlCallback);
    sb->set_float_limits(0,1);
    sb = new GLUI_Scrollbar( color, "Azul",GLUI_SCROLL_HORIZONTAL,
                            &colores_c[0][2],1,controlCallback);
    sb->set_float_limits(0,1);
    sb = new GLUI_Scrollbar( color, "Alpha",GLUI_SCROLL_HORIZONTAL,
                            &colores_c[0][3],1,controlCallback);
    sb->set_float_limits(0,1);

    GLUI_Panel *brilloC = new GLUI_Panel( roll_coche, "Brillo" );

    sb = new GLUI_Scrollbar( brilloC, "Brillo",GLUI_SCROLL_HORIZONTAL,
                            &brilloCoche[0],1,controlCallback);
    sb->set_float_limits(0,1);


    /******** A�ade controles para las luces ********/
    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Luces", false );

    GLUI_Panel *lightAmbient = new GLUI_Panel( roll_lights, "Luz Ambiente" );
    GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Luz 1" );
    GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Luz 2" );
    GLUI_Panel *light2 = new GLUI_Panel( roll_lights, "Luz 3" );

    new GLUI_Checkbox( lightAmbient, "Encendida", &escena.luzAmbiente, LUZ_AMBIENTE_ENABLED_ID, controlCallback );
    sb = new GLUI_Scrollbar( lightAmbient, "Intensidad",GLUI_SCROLL_HORIZONTAL,
                            &escena.cuantaLuzAmbiente,1,controlCallback);
    sb->set_float_limits(0,1);

    new GLUI_Checkbox( light0, "Encendida", &light0_enabled, LIGHT0_ENABLED_ID, controlCallback );
    light0_spinner = new GLUI_Spinner( light0, "Intensidad:", &light0_intensity,
                            LIGHT0_INTENSITY_ID, controlCallback );
    light0_spinner->set_float_limits( 0.0, 1.0 );

    sb = new GLUI_Scrollbar( light0, "Rojo",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_diffuse[0],LIGHT0_INTENSITY_ID,controlCallback);
    sb->set_float_limits(0,1);
    sb = new GLUI_Scrollbar( light0, "Verde",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_diffuse[1],LIGHT0_INTENSITY_ID,controlCallback);
    sb->set_float_limits(0,1);
    sb = new GLUI_Scrollbar( light0, "Azul",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_diffuse[2],LIGHT0_INTENSITY_ID,controlCallback);
    sb->set_float_limits(0,1);

    new GLUI_Checkbox( light1, "Encendida", &light1_enabled, LIGHT1_ENABLED_ID, controlCallback );
    light1_spinner = new GLUI_Spinner( light1, "Intensidad:", &light1_intensity,
                            LIGHT1_INTENSITY_ID, controlCallback );
    light1_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light1, "Rojo",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_diffuse[0],LIGHT1_INTENSITY_ID,controlCallback);
    sb->set_float_limits(0,1);
    sb = new GLUI_Scrollbar( light1, "Verde",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_diffuse[1],LIGHT1_INTENSITY_ID,controlCallback);
    sb->set_float_limits(0,1);
    sb = new GLUI_Scrollbar( light1, "Azul",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_diffuse[2],LIGHT1_INTENSITY_ID,controlCallback);
    sb->set_float_limits(0,1);

    new GLUI_Checkbox( light2, "Encendida", &light2_enabled, LIGHT2_ENABLED_ID, controlCallback );
    light2_spinner = new GLUI_Spinner( light2, "Intensidad:", &light2_intensity,
                            LIGHT2_INTENSITY_ID, controlCallback );
    light2_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light2, "Rojo",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_diffuse[0],LIGHT2_INTENSITY_ID,controlCallback);
    sb->set_float_limits(0,1);
    sb = new GLUI_Scrollbar( light2, "Verde",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_diffuse[1],LIGHT2_INTENSITY_ID,controlCallback);
    sb->set_float_limits(0,1);
    sb = new GLUI_Scrollbar( light2, "Azul",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_diffuse[2],LIGHT2_INTENSITY_ID,controlCallback);
    sb->set_float_limits(0,1);

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    /***  Rollout de Opciones ***/
    GLUI_Rollout *options = new GLUI_Rollout(glui, "Opciones", true );
    new GLUI_Checkbox( options, "Dibujar Coche", &escena.show_car );
    new GLUI_Checkbox( options, "Dibujar Ruedas", &escena.show_wheels );
    new GLUI_Checkbox( options, "Dibujar Carretera", &escena.show_road );
    new GLUI_Checkbox( options, "Dibujar Farolas", &escena.show_farola_base );
    new GLUI_Checkbox( options, "Dibujar Farolas (cap)", &escena.show_farola_capucha );

    new GLUI_Checkbox( options, "Dibujar Casas", &escena.show_casa );

    /*** Disable/Enable botones ***/
    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );
    new GLUI_Checkbox( glui, "Bloquear Movimiento", &enable_panel2 );
    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );
    new GLUI_Button( glui, "Resetear Posicion", RESET_ID, controlCallback );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    /****** A 'quit' button *****/
    new GLUI_Button( glui, "Salir", 0,(GLUI_Update_CB)exit );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    new GLUI_StaticText( glui, "Autor: Alex Jover 2013" );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    // A�ade un panel con texto con el valor de la selecci�n
    GLUI_Panel *panel0 = new GLUI_Panel( glui, "Seleccion");
    sel_tex = new GLUI_StaticText( panel0, "0");


    // Crea la subventana inferior
    glui2 = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_BOTTOM );

    /**** Link windows to GLUI, and register idle callback ******/
    glui->set_main_gfx_window( window_id );
    glui2->set_main_gfx_window( window_id );

    view_rot = new GLUI_Rotation(glui2, "Rotacion Escena", escena.view_rotate );
    view_rot->set_spin( 1.0 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Traslacion Escena XY", GLUI_TRANSLATION_XY, escena.view_position );
    trans_xy->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_x =  new GLUI_Translation(glui2, "Traslacion Escena X", GLUI_TRANSLATION_X, escena.view_position );
    trans_x->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_y = new GLUI_Translation( glui2, "Traslacion Escena Y", GLUI_TRANSLATION_Y, &escena.view_position[1] );
    trans_y->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_z = new GLUI_Translation( glui2, "Traslacion Escena Z", GLUI_TRANSLATION_Z, &escena.scale );
    trans_z->set_speed( .005 );

}

/**************************************** TGui::ControlCallback() *******************/

void __fastcall TGui::ControlCallback( int control )
{
    //SENTIDO CARAS
    if(escena.sentido)
        glFrontFace(GL_CCW);//ANTIHORARIO
    else
        glFrontFace(GL_CW);//HORARIO


    //TIPO DE SOMBREADO
    if(escena.sombra)
        glShadeModel(GL_SMOOTH);//SUAVIZADO
    else
        glShadeModel(GL_FLAT);//PLANO


    if(escena.luzAmbiente)
    {
        GLfloat arrLuzAmbiente[4];
        GLfloat arrLuzAmbienteDividido[4];

        for(int i = 0; i< 4; i++)
        {
            arrLuzAmbiente[i]=escena.cuantaLuzAmbiente;
            arrLuzAmbienteDividido[i]=escena.cuantaLuzAmbiente/5;
        }


        glClearColor(0.0, 0.5, 1.0, 1.0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, arrLuzAmbienteDividido);
        glLightfv(GL_LIGHT1, GL_AMBIENT, arrLuzAmbienteDividido );
        glLightfv(GL_LIGHT2, GL_AMBIENT, arrLuzAmbienteDividido );
        glMaterialfv(GL_FRONT, GL_AMBIENT, arrLuzAmbiente);
   }
    else
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, materialNulo );
        glLightfv(GL_LIGHT1, GL_AMBIENT, materialNulo );
        glLightfv(GL_LIGHT2, GL_AMBIENT, materialNulo );
        glMaterialfv(GL_FRONT, GL_AMBIENT, materialNulo);
    }


  if (control == ZBUFFER_ID)
  {
    if(escena.z_buffer)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
  }

  else if (control == CULLING_ID)
  {
    if(escena.culling){
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
    }
    else
        glDisable(GL_CULL_FACE);
  }

  else if ( control == LIGHT0_ENABLED_ID ) {
    if ( light0_enabled ) {
      glEnable( GL_LIGHT0 );
      light0_spinner->enable();
    }
    else {
      glDisable( GL_LIGHT0 );
      light0_spinner->disable();
    }
  }
  else if ( control == LIGHT1_ENABLED_ID ) {
    if ( light1_enabled ) {
      glEnable( GL_LIGHT1 );
      light1_spinner->enable();
    }
    else {
      glDisable( GL_LIGHT1 );
      light1_spinner->disable();
    }
  }
  else if ( control == LIGHT2_ENABLED_ID ) {
    if ( light2_enabled ) {
      glEnable( GL_LIGHT2 );
      light2_spinner->enable();
    }
    else {
      glDisable( GL_LIGHT2 );
      light2_spinner->disable();
    }
  }
  else if ( control == LIGHT0_INTENSITY_ID ) {
    float v[] = {
      escena.light0_diffuse[0],  escena.light0_diffuse[1],
      escena.light0_diffuse[2],  escena.light0_diffuse[3] };

    v[0] *= light0_intensity;
    v[1] *= light0_intensity;
    v[2] *= light0_intensity;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, v );
  }
  else if ( control == LIGHT1_INTENSITY_ID ) {
    float v[] = {
      escena.light1_diffuse[0],  escena.light1_diffuse[1],
      escena.light1_diffuse[2],  escena.light1_diffuse[3] };

    v[0] *= light1_intensity;
    v[1] *= light1_intensity;
    v[2] *= light1_intensity;

    glLightfv(GL_LIGHT1, GL_DIFFUSE, v );
  }
  else if ( control == LIGHT2_INTENSITY_ID ) {
    float v[] = {
      escena.light2_diffuse[0],  escena.light2_diffuse[1],
      escena.light2_diffuse[2],  escena.light2_diffuse[3] };

    v[0] *= light2_intensity;
    v[1] *= light2_intensity;
    v[2] *= light2_intensity;

    glLightfv(GL_LIGHT2, GL_DIFFUSE, v );
  }
  else if ( control == ENABLE_ID )
  {
    glui2->enable();
  }
  else if ( control == DISABLE_ID )
  {
    glui2->disable();
  }
  else if ( control == RESET_ID)
  {
     memcpy(escena.view_position,view_position_c,3*sizeof(float));
     memcpy(escena.view_rotate,view_rotate_c,16*sizeof(float));
     view_rot->reset();
     escena.scale = 1.0;
  }

  else if ( control == WIREFRAME_ID )
  {
    //MODO ALAMBRICO
    if(escena.wireframe)
    {
        glPolygonMode(GL_FRONT, GL_LINE);//DELANTERO
        glPolygonMode(GL_BACK, GL_LINE);//TRASERO
    }
    else
    {
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }
  }
  else if(control==V_SEGUIMIENTO){
    escena.seleccion = escena.ultimoSelec;

    if(escena.camaraSeguimiento)
    {
        escena.camaraSeguimiento=0;
        escena.seleccion=0;
    }

    else{
        if(escena.seleccion != 0) //Anulamos las otras vistas
        {
            escena.camaraSeguimiento=1;
            escena.vistaAerea=0;
            escena.primeraPersona=0;
        }
    }
  }
  else if(control==V_AEREA)
    {
        escena.seleccion = escena.ultimoSelec;

        if(escena.vistaAerea)
        {
            escena.vistaAerea=0;
            escena.seleccion=0;
        }
        else{
            //Anulamos las otras vistas
            if(escena.seleccion != 0)
            {
                escena.tipoVista=0;
                escena.vistaAerea=1;
                escena.camaraSeguimiento=0;
                escena.primeraPersona=0;
            }
        }
    }

    else if(control==V_PRIMERAPERSONA)
    {
        escena.seleccion = escena.ultimoSelec;

        if(escena.primeraPersona)
        {
            escena.primeraPersona=0;
            escena.seleccion=0;
        }
        else{
            if(escena.seleccion != 0)
            {
                escena.tipoVista=0;
                escena.primeraPersona=1;
                escena.vistaAerea=0;
                escena.camaraSeguimiento=0;
            }
        }
    }
}

/***************************************** TGui::Idle() ***********/

void __fastcall TGui::Idle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != window_id )
    glutSetWindow(window_id);

  /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                       application  */

    if (enable_panel2)

        glui2->enable();
    else
        glui2->disable();

  glutPostRedisplay();
}

/**************************************** TGui::reshape() *************/

void __fastcall TGui::Reshape( int x, int y )
{
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    glViewport( tx, ty, tw, th );

    escena.xy_aspect = (float)tw / (float)th;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(escena.tipoVista)
        glOrtho(-10*escena.xy_aspect,10*escena.xy_aspect, -10, 10, -100, 1000); //PARALELA
    else
      gluPerspective(45, escena.xy_aspect, 1.0, 1000.0);//PERSPECTIVA

    glutPostRedisplay();
}

/***************************************** gui::motion() **********/

void __fastcall TGui::Motion(int x, int y )
{
    if(escena.raton==1) //MOVERSE CON RATON
    {
        if(x > escena.last_x)           //Der
            escena.view_position[0]+=escena.factorMovCam;
        else if (x < escena.last_x)     //Izq
            escena.view_position[0]-=escena.factorMovCam;
        if(y > escena.last_y)           //Up
            escena.view_position[1]-=escena.factorMovCam;
        else if (y < escena.last_y)     //Down
            escena.view_position[1]+=escena.factorMovCam;
    }
    else if(escena.raton==2)  //MOVIMIENTO EN Z
    {
        if(y < escena.last_y)
            escena.view_position[2]+=escena.factorMovCam*2;
        else if(y > escena.last_y)
            escena.view_position[2]-=escena.factorMovCam*2;
    }
    else if(escena.raton==3) //ROTAR EN X Y
    {
        float rot[16];
        float rotacion_X = x - escena.last_x;
        float rotacion_Y = y - escena.last_y;
        escena.rotacionX += rotacion_X;
        escena.rotacionY += rotacion_Y;

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glRotated(escena.rotacionX * escena.factorMovCam, 0, 1, 0);
        glRotated(escena.rotacionY * escena.factorMovCam, 1, 0, 0);

        glGetFloatv(GL_MODELVIEW_MATRIX, rot);

        for(int i=0; i<16; i++)
            if(escena.view_rotate[i] != rot[i])
                escena.view_rotate[i]=rot[i];

        glPopMatrix();


    }

    else if(escena.raton==4) //ROTAR EN Z
    {
        float rot[16];
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        float rotacion_Z = (y - escena.last_y) - (x - escena.last_x);
        escena.rotacionZ += rotacion_Z;

        glRotated(escena.rotacionZ * escena.factorMovCam, 0, 0, 1);

        glGetFloatv(GL_MODELVIEW_MATRIX, rot);

        for(int i=0; i<16; i++)
            if(escena.view_rotate[i] != rot[i])
                escena.view_rotate[i]=rot[i];

        glPopMatrix();
    }
    else if(escena.raton==5)
    {
        if(y < escena.last_y)
            escena.scale+=escena.factorMovCam*0.05;
        else if(y > escena.last_y)
            escena.scale-=escena.factorMovCam*0.05;
    }


    escena.last_x=x;
    escena.last_y=y;

    glutPostRedisplay();
}

/***************************************** gui::Mouse() **********/

void __fastcall TGui::Mouse(int button, int button_state, int x, int y )
{
    //Si no estamos en vista aerea ni seguimiento, accionamos rat�n
    if(button_state==GLUT_DOWN && escena.vistaAerea==0 && escena.camaraSeguimiento == 0 && escena.primeraPersona == 0)
	{
        //glutGetModifiers() devuelve GLUT_ACTIVE_CTRL, GLUT_ACTIVE_SHIFT, y GLUT_ACTIVE_ALT
		if(button==GLUT_LEFT_BUTTON && glutGetModifiers()!=GLUT_ACTIVE_CTRL && glutGetModifiers()!=GLUT_ACTIVE_SHIFT)
			escena.raton = 1;
        else if(button == GLUT_LEFT_BUTTON && glutGetModifiers()==GLUT_ACTIVE_CTRL)
            escena.raton = 2;
		else if(button == GLUT_RIGHT_BUTTON && glutGetModifiers()!=GLUT_ACTIVE_CTRL)
			escena.raton=3;
        else if(button == GLUT_RIGHT_BUTTON && glutGetModifiers()==GLUT_ACTIVE_CTRL)
            escena.raton=4;
        else if(button == GLUT_LEFT_BUTTON && glutGetModifiers()==GLUT_ACTIVE_SHIFT)
            escena.raton=5;

        escena.last_x=x;
        escena.last_y=y;
	}
	else if(button_state==GLUT_UP) //Liberar tecla
	{
	    escena.raton=0;
	    if(button==GLUT_LEFT_BUTTON && escena.vistaAerea==0 && escena.camaraSeguimiento == 0 && escena.primeraPersona == 0)
			escena.Pick3D(x, y);
	}
}


/****************************************************************************

    CarGL (Objects.cpp)

    Pr�ctica de Gr�ficos por Computador (Grado Ingenier�a Multimedia)
  -----------------------------------------------------------------------

    Noviembre 2012 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)

****************************************************************************/

#include "Objects.h"
#include <GL/glui.h>

#include "load3ds.c"
#include "loadjpeg.c"

unsigned char *dataTextura;
int tex_width;
int tex_height;
GLuint texturas[5];  //S�lo estas globales

// Variable para inicializar los vectores correpondientes con los valores iniciales
GLfloat light0_ambient_c[4]  = {   0.2f, 0.2f, 0.2f, 1.0f };
GLfloat light0_diffuse_c[4]  = {   0.8f, 0.8f, 0.8f, 1.0f };
GLfloat light0_specular_c[4] = {   1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light0_position_c[4] = { -50.0f, 5.0f, 0.0f, 1.0f };

GLfloat light1_ambient_c[4]  = { 0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light1_diffuse_c[4]  = { 0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light1_specular_c[4] = { 1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light1_position_c[4] = { 0.0f, 100.0f, 10.0f, 1.0f };

GLfloat mat_ambient_c[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse_c[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular_c[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat high_shininess_c[1] = { 100.0f };

// Matriz de 4x4 = (I)
float view_rotate_c[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_position_c[3] = { 0.0, -2.0, -25.0 };


//MATERIALES
float color_suelo[4] = {0.15,1,0.15, 1};
float colores_c[2][4] = { {0.8, 0.5, 0.0, 1.0}, {0.5, 0.5, 0.5, 1.0}}; //Coche, rueda
float colores_farola[3][4] = {{0.75, 0.75, 0.75, 1.0},{0.5, 0.5, 0.5, 1.0},{1.0, 1.0, 1.0, 1.0}}; //Base, capucha, y cristal de la farola
float colores_carr[4] = {0.95,0.8,0.9, 0.4};
float colores_casa[4][4] = {
                                {1.0 , 1.0, 1.0, 1.0},      //Casa
                                {1.0, 0.15, 0.0, 1.0},      //Tejado
                                {0.93, 0.65, 0.05, 1.0},    //Puerta y Ventanas
                                {0.93, 0.8, 0.25, 1.0}      //Entrada
                            };

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
		    tx = ty = tz = 0;
            glNewList(ID, GL_COMPILE);
                glBegin(GL_QUADS);
                    // La perpendicular al suelo es el eje Y
                    glNormal3f(0.0, 1.0, 0.0);
                    glColor4fv(color_suelo);
                    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                    glVertex3f( 1000, -0.001, -1000);
                    glVertex3f(-1000, -0.001, -1000);
                    glVertex3f(-1000, -0.001,  1000);
                    glVertex3f( 1000, -0.001,  1000);

                glEnd();
            glEndList();
            break;
		}


		case CARRETERA_ID: {  // Creaci�n de la carretera
		    tx = 0;
		    ty = 0;
		    tz = 0;
		    rx = -90;
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
		    ty = 0;
		    tz = 0;
		    rx = -90;
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
		    ty = 0.2;
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

            tx = ty = tz = 0;

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
		    ty = -1.5;
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
		    ty = -1.5;
		    sx = sy = sz = 3.7;

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

	} // fin del case
}

void __fastcall TPrimitiva::Render(int seleccion, bool reflejo)
{
    switch (tipo) {

        case SUELO_ID: {
            glPushMatrix();
            glLoadName(0);  // No seleccionable
            glCallList(ID);
            glPopMatrix();

            break;
        }


        case CARRETERA_ID: {

            glPushMatrix();
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);

            if (escena.show_road)
            {
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores_carr);

                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[0]);
                glLoadName(0); //No seleccionable
                glCallList(ID);
                glDisable(GL_TEXTURE_2D);
            }

            glPopMatrix();
            break;
        }

        case CARRETERA_LARGA_ID: {

            glPushMatrix();
            glTranslated(tx, ty, tz);
            glRotated(rx, 1, 0, 0);
            glRotated(ry, 0, 1, 0);
            glRotated(rz, 0, 0, 1);

            if (escena.show_road)
            {
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores_carr);

                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturas[0]);
                glLoadName(0); //No seleccionable
                glCallList(ID);
                glDisable(GL_TEXTURE_2D);
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
            float ang=PI*(ry)/180.0;

            tz+=v*cos(ang);
            tx+=v*sin(ang);


            if( v != 0)
            {
                float desp_lateral = anguloRuedas * v * 0.4;

                ry += desp_lateral;
                rr += v*45;
            }
            if( v > 0)
            {
                v -= 0.05;


                if(v < 0){
                    v=0;
                }
            }
            else if(v < 0)
            {
                v += 0.05;

                if(v > 0)
                    v = 0;
            }


            if (escena.show_car)
            {

                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores_c[0]);
                glLoadName(ID);
                glCallList(ID);

                if(seleccion==ID)
                {
                    glPushMatrix();
                    glTranslated(0, -0.17, 1.27);
                    glColor4f(0.0,0.0,1.0,0.9);
                    glCallList(ID+MARCADOR);
                    glPopMatrix();
                }
            }

            if (escena.show_wheels)
            {
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
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
                glColor4fv(colores_farola[0]);
                glLoadName(0);
                glCallList(ID+FAROLA_BASE);
            }

            if (escena.show_farola_capucha)
            {
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores_farola[1]);
                glLoadName(0);
                glCallList(ID+FAROLA_CAPUCHA);

                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores_farola[2]);
                glLoadName(0);
                glCallList(ID+FAROLA_CRISTAL);
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
                glColor4fv(colores_casa[0]);
                glLoadName(0);
                glCallList(ID+CASA_BASE);

                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores_casa[1]);
                glLoadName(0);
                glCallList(ID+CASA_TEJADO);

                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores_casa[2]);
                glLoadName(0);
                glCallList(ID+CASA_VENTANAS);

                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores_casa[2]);
                glLoadName(0);
                glCallList(ID+CASA_PUERTA);

                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores_casa[3]);
                glLoadName(0);
                glCallList(ID+CASA_ENTRADA);
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
            glColor4fv(color_suelo);

            glLoadName(0); //No seleccionable
            glCallList(ID);

            glPopMatrix();
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
            glColor4fv(color_suelo);

            glLoadName(0); //No seleccionable
            glCallList(ID);

            glPopMatrix();
            break;
        }
    }
}




//************************************************************** Clase TEscena

TEscena::TEscena() {

    seleccion = 0;
    num_objects = 0;
    num_cars = 0;

    show_car = 1;
    show_wheels = 1;
    show_road = 1;

    show_farola_base = 1;
    show_farola_capucha = 1;

    show_casa = 1;

    // live variables usadas por GLUI en TGui
    wireframe = 0;
    z_buffer = 1;
    culling = 0;

    scale = 1.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;

    memcpy(view_position, view_position_c, 3*sizeof(float));
    memcpy(view_rotate, view_rotate_c, 16*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));
    memcpy(light0_diffuse, light0_diffuse_c, 4*sizeof(float));
    memcpy(light0_specular, light0_specular_c, 4*sizeof(float));
    memcpy(light0_position, light0_position_c, 4*sizeof(float));

    memcpy(light1_ambient, light1_ambient_c, 4*sizeof(float));
    memcpy(light1_diffuse, light1_diffuse_c, 4*sizeof(float));
    memcpy(light1_specular, light1_specular_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));

    memcpy(mat_ambient, mat_ambient_c, 4*sizeof(float));
    memcpy(mat_diffuse, mat_diffuse_c, 4*sizeof(float));
    memcpy(mat_specular, mat_specular_c, 4*sizeof(float));
    memcpy(high_shininess, high_shininess_c, 1*sizeof(float));
}

void __fastcall TEscena::InitGL()
{
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );

    escena.xy_aspect = (float)tw / (float)th;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, escena.xy_aspect, 1.0, 1000.0); // No se deber�an tocar estos valores

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH); //o GL_FLAT

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

    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    //TEXTURAS
    //CAMINO

    glGenTextures(5,&texturas[0]);

    dataTextura = LoadJPEG("../../Texturas/camino.jpg", &tex_width, &tex_height);
    glBindTexture( GL_TEXTURE_2D, texturas[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex_width, tex_height, 0, GL_RGB,GL_UNSIGNED_BYTE, dataTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    free(dataTextura);

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

/***************************************** TEscena::Render() *****************/

void __fastcall TEscena::Render()
{
    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Transformaci�n del escenario
    glTranslatef( view_position[0], view_position[1], view_position[2] );   // Traslaci�n
    glMultMatrixf(view_rotate);                                             // Rotaci�n
    glScalef(scale, scale, scale);                                          // Escalado

    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    // Dibujar carretera y objetos
    RenderObjects(seleccion);

    // Dibujar coches
    RenderCars(seleccion);

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
    sprintf(cad, "%03d [%03d, %03d]", seleccion, mouse_x, mouse_y);
    gui.sel_tex->set_text(cad);
}

//************************************************************** Clase TGui

TGui::TGui()
{
    enable_panel2 = 1;
    light0_enabled = 1;
    light1_enabled = 1;
    light0_intensity = 0.8;
    light1_intensity = 0.8;
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

    /***** Control para las propiedades de escena *****/

    new GLUI_Checkbox( obj_panel, "Modo Alambrico", &escena.wireframe, 1, controlCallback );
    new GLUI_Checkbox( obj_panel, "Z Buffer", &escena.z_buffer, 1, controlCallback );
    new GLUI_Checkbox( obj_panel, "Culling", &escena.culling, 1, controlCallback );

    /******** A�ade controles para las luces ********/

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Luces", false );

    GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Luz 1" );
    GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Luz 2" );

    new GLUI_Checkbox( light0, "Encendida", &light0_enabled, LIGHT0_ENABLED_ID, controlCallback );
    light0_spinner = new GLUI_Spinner( light0, "Intensidad:", &light0_intensity,
                            LIGHT0_INTENSITY_ID, controlCallback );
    light0_spinner->set_float_limits( 0.0, 1.0 );
    GLUI_Scrollbar *sb;
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
  if ( control == LIGHT0_ENABLED_ID ) {
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
     //memcpy(escena.view_rotate,view_rotate_c,16*sizeof(float));
     view_rot->reset();
     escena.scale = 1.0;
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
    gluPerspective(45, escena.xy_aspect, 1.0, 1000.0);

    glutPostRedisplay();
}

/***************************************** gui::motion() **********/

void __fastcall TGui::Motion(int x, int y )
{
    glutPostRedisplay();
}

/***************************************** gui::Mouse() **********/

void __fastcall TGui::Mouse(int button, int button_state, int x, int y )
{
    escena.Pick3D(x, y);
}

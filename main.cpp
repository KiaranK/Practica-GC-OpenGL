/****************************************************************************

    CarGL (main.cpp)

    Práctica de Gráficos por Computador (Grado Ingeniería Multimedia)
  -----------------------------------------------------------------------

    Noviembre 2012 (C) Juan Antonio Puchol García (puchol@dccia.ua.es)

    NOTA:   Para que esta aplicación compile se necesita tener copiados los
            siguientes ficheros:

            Si es un Windows de 32 bits:
            libgui32.a -> C:\Program Files\CodeBlocks\MinGW\lib
            glut32.lib -> C:\Program Files\CodeBlocks\MinGW\lib

            Si es un Windows de 64 bits:
            libgui32.a -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glut32.lib -> C:\Program Files (x86)\CodeBlocks\MinGW\lib

            glui.h     -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glut.h     -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL

            glut32.dll -> C:\Windows\system

****************************************************************************/

#include "Objects.h"
#include <GL\glui.h>


// Otras Variables Globales

/**************************************** myGlutKeyboard() **********/

void Keyboard(unsigned char Key, int x, int y)
{
    switch(Key)
    {
        case 27:
        case 'q':
            exit(0);
            break;

    }

    glutPostRedisplay();
}

/**************************************** mySpecialKey() *************/
//Teclas que no tienen codigo ASCI asociado
static void SpecialKey(int key, int x, int y)
{
    //Si hay algun objeto seleccionado
    if(escena.seleccion != 0){

        TPrimitiva *car = escena.GetCar(escena.seleccion);

        switch (key)
        {
            case GLUT_KEY_UP:   // El coche avanza
                car->v += VEL;
                break;
            case GLUT_KEY_DOWN:   // El coche retrocede
                car->v -= VEL;
                break;

            case GLUT_KEY_LEFT:   // Giramos ruedas
                if(car->anguloRuedas < 24)
                    car->anguloRuedas += 1;
                break;
            case GLUT_KEY_RIGHT:
                if(car->anguloRuedas > -24)
                    car->anguloRuedas -= 1;
                break;
        }

        /*switch (key)
        {
            case GLUT_KEY_UP:   // El coche avanza
                car->rr+=20;         //Rotamos rueda
                car->tz += 0.15;    //Avanzamos coche
                break;
            case GLUT_KEY_DOWN:   // El coche retrocede
                car->rr-=20;
                car->tz -= 0.15;
                break;

            case GLUT_KEY_LEFT:   // Giramos ruedas
                if(car->anguloRuedas < 25)
                    car->anguloRuedas += 1;
                break;
            case GLUT_KEY_RIGHT:
                if(car->anguloRuedas > -25)
                    car->anguloRuedas -= 1;
                break;
        }*/

        glutPostRedisplay();

    }

}

/***************************************** myGlutMenu() ***********/

void Menu( int value )
{
  Keyboard( value, 0, 0 );
}

void Mouse(int button, int button_state, int x, int y )
{
    gui.Mouse(button, button_state, x, y);
}

void Render()
{
    escena.Render();
}

void Idle()
{
    gui.Idle();
}

void Reshape(int x, int y){
    gui.Reshape(x, y);
}

void Motion(int x, int y){
    gui.Motion(x, y);
}




/**************************************** main() ********************/

int main(int argc, char* argv[])
{
    // Inicializa GLUT and crea la ventana principal
    glutInit(&argc, argv);
    //queremos utilizar RGBA, double buffer, zBuffer, stencilBuffer
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE );
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( 1000, 600 );

    int main_window = glutCreateWindow( "CarGL V1.1 (2012)" );

    // Inicializa los valores de OpenGL para esta Aplicación
    escena.InitGL();
    gui.Init(main_window);

    //funciones para renderizar, escalar, teclas especiales...
    glutDisplayFunc( Render );
    GLUI_Master.set_glutReshapeFunc( Reshape );
    GLUI_Master.set_glutKeyboardFunc( Keyboard );
    GLUI_Master.set_glutSpecialFunc( SpecialKey );
    GLUI_Master.set_glutMouseFunc( Mouse );
    glutMotionFunc( Motion );

    /**** We register the idle callback with GLUI, *not* with GLUT ****/
    GLUI_Master.set_glutIdleFunc( Idle );

    // Crea los objetos
    TPrimitiva *suelo = new TPrimitiva(SUELO_ID, SUELO_ID);

    TPrimitiva *carrLarga1 = new TPrimitiva(CARRETERA_LARGA_ID, CARRETERA_LARGA_ID);
    TPrimitiva *carrCorta1 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta2 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);

    TPrimitiva *casa0 = new TPrimitiva(CASA_ID, CASA_ID);
	TPrimitiva *casa1 = new TPrimitiva(CASA_ID, CASA_ID);
	TPrimitiva *casa2 = new TPrimitiva(CASA_ID, CASA_ID);

    TPrimitiva *car1 = new TPrimitiva(COCHE_ID*1, COCHE_ID);

	TPrimitiva *farola0 = new TPrimitiva(FAROLA_ID, FAROLA_ID);
	TPrimitiva *farola1 = new TPrimitiva(FAROLA_ID, FAROLA_ID);
	TPrimitiva *farola2 = new TPrimitiva(FAROLA_ID, FAROLA_ID);
	TPrimitiva *farola3 = new TPrimitiva(FAROLA_ID, FAROLA_ID);
	TPrimitiva *farola4 = new TPrimitiva(FAROLA_ID, FAROLA_ID);
	TPrimitiva *farola5 = new TPrimitiva(FAROLA_ID, FAROLA_ID);
	TPrimitiva *farola6 = new TPrimitiva(FAROLA_ID, FAROLA_ID);

	TPrimitiva *farola_calle0 = new TPrimitiva(FAROLA_ID, FAROLA_ID);
	TPrimitiva *farola_calle1 = new TPrimitiva(FAROLA_ID, FAROLA_ID);

	TPrimitiva *farola_calle2 = new TPrimitiva(FAROLA_ID, FAROLA_ID); //Otra calle

	TPrimitiva *ladera_baja0 = new TPrimitiva(LADERA_BAJA_ID, LADERA_BAJA_ID);
	TPrimitiva *ladera_baja1 = new TPrimitiva(LADERA_BAJA_ID, LADERA_BAJA_ID);

	TPrimitiva *ladera_alta0 = new TPrimitiva(LADERA_ALTA_ID, LADERA_ALTA_ID);
	TPrimitiva *ladera_alta1 = new TPrimitiva(LADERA_ALTA_ID, LADERA_ALTA_ID);


//POSICIONES

    ladera_alta0->tx = 90;
    ladera_alta0->tz = -110;

    ladera_alta1->tx = -150;
    ladera_alta1->tz = 200;

    ladera_baja0->tx = -60;
    ladera_baja0->tz = -75;

    ladera_baja1->tx = 65;
    ladera_baja1->tz = 65;

    carrCorta1->tx = 35;
    carrCorta1->ty = 20;
    carrCorta1->tz = 25;
    carrCorta1->rz = 0;

    carrCorta2->tx = -35;
    carrCorta2->tz = -25;
    carrCorta2->rz = 0;


    //Farolas (carretera principal)
    farola0->tx = -10;
    farola0->tz = -50*3;
    farola0->rz = -90;

	farola1->tx = 10;
    farola1->tz = -50*2;
    farola1->rz = 90;

    farola2->tx = -10;
    farola2->tz = -50*1;
    farola2->rz = -90;

    farola3->tx = 10;
    farola3->tz = 50*0;
    farola3->rz = 90;

    farola4->tx = -10;
    farola4->tz = 50*1;
    farola4->rz = -90;

    farola5->tx = 10;
    farola5->tz = 50*2;
    farola5->rz = 90;

    farola6->tx = -10;
    farola6->tz = 50*3;
    farola6->rz = -90;

    //Farolas calles laterales
    farola_calle0->tx = 45*1;
    farola_calle0->tz = 28;
    farola_calle0->rz = 180;

    farola_calle1->tx = 45*2;
    farola_calle1->tz = 48;
    farola_calle1->rz = 0;

    farola_calle2->tx = -60;
    farola_calle2->tz = -49;
    farola_calle2->rz = 180;

    casa0->tx = -73;
    casa0->tz = -25;
    casa0->ry = 90;

    casa1->tx = 14;
    casa1->tz = 100;
    casa1->ry = -90;

    casa2->tx = 65;
    casa2->tz = 10;

//Añadimos objetos
    escena.AddObject(suelo);

    escena.AddObject(carrLarga1);
    escena.AddObject(carrCorta1);
    escena.AddObject(carrCorta2);

    escena.AddObject(casa0);
    escena.AddObject(casa1);
    escena.AddObject(casa2);

    escena.AddObject(farola0);
    escena.AddObject(farola1);
    escena.AddObject(farola2);
    escena.AddObject(farola3);
    escena.AddObject(farola4);
    escena.AddObject(farola5);
    escena.AddObject(farola6);
    escena.AddObject(farola_calle0);
    escena.AddObject(farola_calle1);
    escena.AddObject(farola_calle2);

    escena.AddObject(ladera_baja0);
    escena.AddObject(ladera_baja1);
    escena.AddObject(ladera_alta0);
    escena.AddObject(ladera_alta1);

    escena.AddCar(car1);

    /**** Regular GLUT main loop ****/
    glutMainLoop();

    return EXIT_SUCCESS;
}


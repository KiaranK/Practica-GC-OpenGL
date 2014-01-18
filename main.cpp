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

        case 'O':
        case 'o':
            //Como no se ve bien, desactivamos la vista Ortog para PrimeraPersona y VistaAerea
            if(escena.primeraPersona==0 && escena.vistaAerea==0)
            {
                escena.tipoVista=1;
                gui.Reshape(x,y);//Paralela
            }

            break;

        case 'P':
        case 'p':
            escena.tipoVista=0;
            gui.Reshape(x,y);//Perspectiva
            break;

        //Teclas para la rotacion

        case 'x':
        case 'X':
            escena.rotacionX=1;
            escena.rotacionY=0;
            escena.rotacionZ=0;
        break;

        case 'y':
        case 'Y':
            escena.rotacionX=0;
            escena.rotacionY=1;
            escena.rotacionZ=0;
        break;

        case 'z':
        case 'Z':
            escena.rotacionX=0;
            escena.rotacionY=0;
            escena.rotacionZ=1;
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
    glutInitWindowPosition( 50, 25 );
    glutInitWindowSize( 1100, 710 );

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
    TPrimitiva *carrLarga2 = new TPrimitiva(CARRETERA_LARGA_ID, CARRETERA_LARGA_ID);

    TPrimitiva *carrCorta1 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta2 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta3 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta4 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta5 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta6 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta7 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta8 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta9 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta10 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta11 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta12 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta13 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta14 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *carrCorta15 = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);

    TPrimitiva *casa0 = new TPrimitiva(CASA_ID, CASA_ID);
	TPrimitiva *casa1 = new TPrimitiva(CASA_ID, CASA_ID);
	TPrimitiva *casa2 = new TPrimitiva(CASA_ID, CASA_ID);
	TPrimitiva *casa3 = new TPrimitiva(CASA_ID, CASA_ID);
	TPrimitiva *casa4 = new TPrimitiva(CASA_ID, CASA_ID);
	TPrimitiva *casa5 = new TPrimitiva(CASA_ID, CASA_ID);
    TPrimitiva *casa6 = new TPrimitiva(CASA_ID, CASA_ID);
    TPrimitiva *casa7 = new TPrimitiva(CASA_ID, CASA_ID);
    TPrimitiva *casa8 = new TPrimitiva(CASA_ID, CASA_ID);
    TPrimitiva *casa9 = new TPrimitiva(CASA_ID, CASA_ID);
    TPrimitiva *casa10 = new TPrimitiva(CASA_ID, CASA_ID);
    TPrimitiva *casa11 = new TPrimitiva(CASA_ID, CASA_ID);
    TPrimitiva *casa12 = new TPrimitiva(CASA_ID, CASA_ID);
    TPrimitiva *casa13 = new TPrimitiva(CASA_ID, CASA_ID);

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


	TPrimitiva *semaforo0 = new TPrimitiva(SEMAFORO_ID, SEMAFORO_ID);

	TPrimitiva *piramide0 = new TPrimitiva(PIRAMIDE_ID, PIRAMIDE_ID);

	TPrimitiva *arbol0 = new TPrimitiva(ARBOL_ID, ARBOL_ID);

	TPrimitiva *banco0 = new TPrimitiva(BANCO_ID, BANCO_ID);


//POSICIONES
    semaforo0->tx = 9;

    arbol0->tx = -9;

    banco0->tx = 9;
    banco0->tz = 10;

    piramide0->tx = -12;
    piramide0->tz = 20;



    ladera_alta0->tx = 90;
    ladera_alta0->tz = -110;

    ladera_alta1->tx = -150;
    ladera_alta1->tz = 200;

    ladera_baja0->tx = -60;
    ladera_baja0->tz = -75;

    ladera_baja1->tx = 65;
    ladera_baja1->tz = 65;


    carrLarga2->tx = 129.5;
    carrLarga2->tz = 62;

//derecha
    carrCorta1->tx = 36;
    carrCorta1->tz = 25;
    carrCorta1->rz = 0;     //en horizontal

    carrCorta3->tx = 36;
    carrCorta3->tz = 110;
    carrCorta3->rz = 0;

    carrCorta5->tx = 95;
    carrCorta5->tz = 110;
    carrCorta5->rz = 0;

    carrCorta7->tx = 60;
    carrCorta7->tz = 141.3;

    carrCorta9->tx = 24.5;
    carrCorta9->tz = 166;
    carrCorta9->ty = 0.03;
    carrCorta9->rz = 0;

    carrCorta11->tx = 95;
    carrCorta11->tz = 166;
    carrCorta11->ty = 0.03;
    carrCorta11->rz = 0;

    carrCorta10->tz = 140;

    carrCorta12->tx = 95;
    carrCorta12->tz = 25;
    carrCorta12->ty = 0.03;
    carrCorta12->rz = 0;

//izquierda
    carrCorta2->tx = -35;
    carrCorta2->tz = -25;
    carrCorta2->rz = 0;

    carrCorta4->tx = -35;
    carrCorta4->tz = 48;
    carrCorta4->rz = 0;

    carrCorta6->tx = -59.65;
    carrCorta6->tz = 11.3;

    carrCorta8->tx = -35;
    carrCorta8->tz = 110;
    carrCorta8->rz = 0;

    carrCorta13->tx = -59.65;
    carrCorta13->tz = 135;
    carrCorta13->ty = 0.025;

    carrCorta14->tx = -59.65;
    carrCorta14->tz = 81;

    carrCorta15->tx = -35;
    carrCorta15->tz = 166;
    carrCorta15->rz = 0;
    carrCorta15->ty = 0.027;


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


    casa0->tx = -74.9;
    casa0->tz = -10;
    casa0->ry = 90;

    casa6->tx = -74.9;
    casa6->tz = 30;
    casa6->ry = 90;

    casa7->tx = -74.9;
    casa7->tz = 66;
    casa7->ry = 90;

    casa8->tx = -74.9;
    casa8->tz = 90;
    casa8->ry = 90;

    casa9->tx = -74.9;
    casa9->tz = 140;
    casa9->ry = 90;



    casa1->tx = 15;
    casa1->tz = 85;
    casa1->ry = -90;

    casa2->tx = 63.6; //mira al revés que la camara
    casa2->tz = 9.9;

    casa3->tx = 25;
    casa3->tz = 9.9;

    casa4->tx = 35;
    casa4->tz = 95;

    casa5->tx = 45;
    casa5->tz = 140;
    casa5->ry = 90;    //mira hacia el mismo sitio donde mira la camara(inicialmente)

    casa10->tx = -30;
    casa10->tz = 181.1;
    casa10->ry = 180;

    casa11->tx = 30;
    casa11->tz = 181.1;
    casa11->ry = 180;


//Añadimos objetos
    escena.AddObject(suelo);

    escena.AddFloor(carrLarga1);
    escena.AddFloor(carrLarga2);
    escena.AddFloor(carrCorta1);
    escena.AddFloor(carrCorta2);
    escena.AddFloor(carrCorta3);
    escena.AddFloor(carrCorta4);
    escena.AddFloor(carrCorta5);
    escena.AddFloor(carrCorta6);
    escena.AddFloor(carrCorta7);
    escena.AddFloor(carrCorta8);
    escena.AddFloor(carrCorta9);
    escena.AddFloor(carrCorta10);
    escena.AddFloor(carrCorta11);
    escena.AddFloor(carrCorta12);
    escena.AddFloor(carrCorta13);

    escena.AddObject(casa0);
    escena.AddObject(casa1);
    escena.AddObject(casa2);
    escena.AddObject(casa3);
    escena.AddObject(casa4);
    escena.AddObject(casa5);
    escena.AddObject(casa6);
    escena.AddObject(casa7);
    escena.AddObject(casa8);
    escena.AddObject(casa9);
    escena.AddObject(casa10);
    escena.AddObject(casa11);
    //escena.AddObject(casa12);
    //escena.AddObject(casa13);

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

    escena.AddObject(piramide0);
    escena.AddObject(banco0);
    escena.AddObject(semaforo0);
    escena.AddObject(arbol0);

    escena.AddCar(car1);
    escena.ultimoSelec=COCHE_ID;

    /**** Regular GLUT main loop ****/
    glutMainLoop();

    return EXIT_SUCCESS;
}


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
                car->rr+=8;         //Rotamos rueda
                car->tz += 0.05;    //Avanzamos coche
                break;
            case GLUT_KEY_DOWN:   // El coche retrocede
                car->rr-=8;
                car->tz -= 0.05;
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
    TPrimitiva *road = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *car1 = new TPrimitiva(COCHE_ID*1, COCHE_ID);
    TPrimitiva *car2 = new TPrimitiva(COCHE_ID*2, COCHE_ID);
    TPrimitiva *farola1 = new TPrimitiva(FAROLA_ID*1, FAROLA_ID);

    //cambiamos características de los coches
    car2->colores[0][0] = 0.3;
    car2->colores[0][1] = 0.8;
    car2->colores[0][2] = 0.4;
    car2->colores[0][3] = 1.0;
    car2->tx = 2;
    car2->tz = -3;

    escena.AddObject(road);
    escena.AddObject(farola1);
    escena.AddCar(car1);
    escena.AddCar(car2);

    /**** Regular GLUT main loop ****/
    glutMainLoop();

    return EXIT_SUCCESS;
}


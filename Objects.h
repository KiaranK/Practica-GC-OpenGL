
/****************************************************************************

    CarGL (Objects.h)

    Práctica de Gráficos por Computador (Grado Ingeniería Multimedia)
  -----------------------------------------------------------------------

    Noviembre 2012 (C) Juan Antonio Puchol García (puchol@dccia.ua.es)

****************************************************************************/

//---------------------------------------------------------------------------
#ifndef ObjectsH
#define ObjectsH
//---------------------------------------------------------------------------

#include <GL\glui.h>

#define VEL 0.15
#define PI  3.14159265358979
#define COEF_ROZ    0.006
#define DESLIZ_RUEDA    45

// Identificadores internos de los objetos
#define SUELO_ID        105
#define CARRETERA_ID    110
#define CARRETERA_LARGA_ID    115

#define CASA_ID         120

#define CASA_BASE       0
#define CASA_TEJADO     1
#define CASA_VENTANAS   2
#define CASA_PUERTA     3
#define CASA_ENTRADA    4


#define COCHE_ID	    99 // Un coche cada 100

#define COCHE           0   //Estas variables se suman a coche, para así poder identificar varias partes de un objeto
#define RUEDA	        1
#define MARCADOR        2


#define FAROLA_ID       125

#define FAROLA_BASE     0
#define FAROLA_CAPUCHA  1
#define FAROLA_CRISTAL  2

#define LADERA_BAJA_ID  130

#define LADERA_ALTA_ID  135



// IDs para los callbacks de TGui
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT2_ENABLED_ID    202
#define LIGHT0_INTENSITY_ID  250
#define LIGHT1_INTENSITY_ID  260
#define LIGHT2_INTENSITY_ID  270

#define ENABLE_ID            300
#define DISABLE_ID           301

#define RESET_ID             400

#define WIREFRAME_ID         410
#define V_AEREA              411

//************************************************************** Clase TPrimtiva

class TPrimitiva
{
public: // Atributos
		int ID;				    // DisplayLists del objeto
		int tipo;               // Tipo de Objeto
		float tx,ty,tz; 	    // Posición del objeto
		float sx,sy,sz; 	    // Escalado del objeto
		float rx,ry,rz;     	// Rotación del objeto
		float rr;               // Rotación de las ruedas
		float v;
		float t_luz_z;            // Posicion Z en caso que sea una farola
		float colores[2][4];    // Color RGB y canal Alfa
		float anguloCoche;
		float anguloRuedas;

public: // Métodos
 		TPrimitiva(int DL, int tipo);
        void __fastcall Render(int seleccion, bool reflejo=false);
};

//************************************************************** Clase TEscena

class TEscena
{
public: // Atributos
        int raton;
        int rotacionX;
        int rotacionY;
        int rotacionZ;
		int   	seleccion;   	// Objeto seleccionado, 0=ninguno
        int		num_objects;    // Número de objetos (excepto coches)
        int     num_cars;       // Número de coches

        TPrimitiva  *cars[10];
        TPrimitiva  *objects[150];

        int sombra;
        int sentido;
        int perspectiva;
        int luzAmbiente;
        int camaraSeguimiento;

        //variables de estado
        int show_car;
        int show_wheels;
        int show_road;

        int show_farola_base;
        int show_farola_capucha;
        int show_charco;
        int show_casa;

        GLfloat view_position[3];
        GLfloat view_rotate[16];

        // Vectores de luces y materiales
        GLfloat light0_ambient[4];
        GLfloat light0_diffuse[4];
        GLfloat light0_specular[4];
        GLfloat light0_position[4];

        GLfloat light1_ambient[4];
        GLfloat light1_diffuse[4];
        GLfloat light1_specular[4];
        GLfloat light1_position[4];

        GLfloat light2_ambient[4];
        GLfloat light2_diffuse[4];
        GLfloat light2_specular[4];
        GLfloat light2_position[4];

        GLfloat mat_ambient[4];
        GLfloat mat_diffuse[4];
        GLfloat mat_specular[4];
        GLfloat high_shininess[1];

        float   xy_aspect;
        int     last_x, last_y;

        // live variables usadas por GLUI en TGui
        // luego las usaremos para utilizarlo en un código estilo a:
        // if(culling) EnableGL(...);
        int     wireframe;
        int     z_buffer;
        int     culling;
        float   scale;

public: // Métodos
		TEscena();

        void __fastcall InitGL();
		void __fastcall Render();
		void __fastcall RenderCars(bool reflejo=false);
		void __fastcall RenderObjects(bool reflejo=false);

		void __fastcall AddCar(TPrimitiva *car);
		void __fastcall AddObject(TPrimitiva *object);

		TPrimitiva __fastcall *GetCar(int id);

		void __fastcall Pick3D(int mouse_x, int mouse_y);


};

//************************************************************** Clase TGui

class TGui
{
public:
        int             window_id;

        // live variables usadas por GLUI
        int             enable_panel2;
        int             light0_enabled;
        int             light1_enabled;
        int             light2_enabled;
        float           light0_intensity;
        float           light1_intensity;
        float           light2_intensity;

        GLUI            *glui, *glui2;
        GLUI_Spinner    *light0_spinner;
        GLUI_Spinner    *light1_spinner;
        GLUI_Spinner    *light2_spinner;
        GLUI_RadioGroup *radio;
        GLUI_Panel      *obj_panel;
        GLUI_Rotation   *view_rot;
        GLUI_StaticText *sel_tex;

public:
        TGui();
        void __fastcall Init(int main_window);
        void __fastcall ControlCallback(int control);
        void __fastcall Idle( void ); //Gestor de eventos
        void __fastcall Reshape( int x, int y  );
        void __fastcall Motion( int x, int y  );
        void __fastcall Mouse(int button, int button_state, int x, int y );
};

//************************************************************** Variables de clase

extern TEscena  escena;
extern TGui     gui;

#endif

#define _WIN32_WINNT 0x0502
#define WIN32
#include "GLee.h"
#include "GL/glut.h"
#include "loader.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <vfw.h>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <windows.h>
#include <Commctrl.h>
#include <iostream>
#include <fstream>

#include <sstream>


using namespace std;
using namespace cv;


//VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.

extern HGLRC hglrc;		// OpenGL rendering context
HDC g_HDC;
DCB config_;
float degreeZ;

#define ImageX 600
#define ImageY 480

int Xexpand=1240,Yexpand=980;
char Buffer[]="pos X 10\r";
static int stepR =35;
#define IDC_MAIN_BUTTON	101			// Button identifier
#define IDC_MAIN_EDIT	102			// Edit box identifier
#define IDC_SLIDER_BUTTON 103
#define IDC_SLIDER_BUTTON2 104
#define IDC_GRPBUTTONS 105
#define IDC_CHK1 106
#define IDC_CHK2 107
#define IDC_CHK3 108
#define IDC_CHK4 109
#define IDC_MAIN_BUTTON2 110
#define IDC_SLIDER_BUTTON3 111
#define IDC_MAIN_EDIT2 112
#define IDC_UP_BUTTON 113
#define IDC_DOWN_BUTTON 114
#define FEED_DOWN_BUTTON 115
#define IDC_FRONT_BUTTON 116
#define IDC_BACK_BUTTON 117
#define IDC_RIGTH_BUTTON 118
#define IDC_LEFT_BUTTON 119
#define IDC_CALCULATE_BUTTON 120

#define RED 0xFF3333
#define GREEN 0x99FF33
#define BLACK 0x0
#define YELLOW 0xFFFF00
#define GRAY 0xC0C0C0
#define WHITE 0xFFFFFF
#define BLUE 0x0000FF
#define ratio 4.0909

HWND hEdit;
HWND hWndSlider1,hWndSlider2,hWndSlider3;
HWND hGrpButtons;
HWND handlePort;
HWND camhwnd;

int yPOS=0;
int xPOS=0;
int zPOS=0;


LRESULT pos,pos2,pos3;
float angle = 0.0f;
float legAngle[2] = {0.0f, 0.0f};
float armAngle[2] = {0.0f, 0.0f};

  GLfloat light0_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
  GLfloat light0_diffuse[] =  {.6f, .6f, 1.0f, 1.0f};
  GLfloat light0_specular[]=  {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat light0_position[] = {1.0f, 1.0f, 1.0f, 0.0f};

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

//class Bad PLANE("plane.stl",0xCCE5FF,0,0,0);
//class Bad ARM1("arm1.stl",GREEN,0,0,0);
/*class Bad ARM2("arm2.stl",RED,9.08634,0.7075696,0);
class Bad ARM3("arm3.stl",GREEN,0,0,0);
class Bad RIGHT_PLATE("right_plate.stl",GREEN,-50.41,52.23,15.25);
class Bad MAIN_GEAR("main_gear.stl",GREEN,0,52.12,-24.63);
class Bad MAIN_GEAR2("Gear2.stl",YELLOW,0,52.12,-24.63);
class Bad SMALL_GEAR1("small_gear1.stl",GREEN,-8.49083, 12.44, -45.99);
class Bad SMALL_GEAR2("small_gear2.stl",YELLOW,-27.71, 13.85, -44.70);
class Bad MAIN_BAR("main_bar.stl",GREEN,-5.95044,51.90681,-24.81742);
class Bad HORIZONTAL("horizontal.stl",GREEN,-25.57822,49.49273,94.69026);
class Bad MOTOR1("motor1.stl",BLACK,0,0,0);
class Bad MOTOR2("motor2.stl",BLACK,0,52,0);
class Bad BOTTOM_PLATE1("bottom.stl",GREEN,0,0,0);
class Bad LEFT_PLATE("left_plate.stl",YELLOW,0,52.07864,15.50329);
class Bad BEARING("bearing.stl",GRAY,-5.95044,51.90681,-24.81742);
*/
//

class Bad plane("plane.stl",WHITE,-15.69123,9.69769,-113.6832);//done
class Bad gear2("main_gear2.stl",WHITE,-6.27026,26.1353,-24.29232);//done
class Bad main_gear("main_gear1.stl",GREEN,21.32011,26.63316,-24.63571);//done
class Bad main_gear3("main_gear3.stl",RED,0.1657748,-13.9068,-87.19798);//done
class Bad arm1("arm1.stl",GREEN,13.17923,64.80094,121.3165);//done
class Bad arm2("arm2.stl",GREEN,-6.9115,-37.98584,-24.18324);//done
class Bad arm3("arm3.stl",RED,30.40645,-25.20684,2.76064);//done
class Bad palanca2("palanca2.stl",WHITE,-12.51398,26.9935,-24.56469);//
class Bad main_bar("main_bar.stl",GREEN,0.5358276,26.40598,-24.07585);//done
class Bad small_gear1("small_gear1.stl",GREEN,12.82928,-12.99233,-45.99202);//done
class Bad small_gear2("small_gear2.stl",YELLOW,-5.84519,-11.63362,-45.63098 );//done
class Bad small_gear3("small_gear3.stl",RED,0.0344124,-61.65918 ,-78.58023);//done
class Bad upper_triangle("upper_triangle.stl",GREEN,0.5358181,24.30385,95.92947);//done
class Bad motor1("motor1.stl",BLACK,47.34509,-12.99106,-45.59805);//done
class Bad motor2("motor2.stl",BLACK,-46.27036,-10.68593,-46.34775);//done
class Bad motor3("motor3.stl",BLACK,0.4358006,-61.57526,-70.05495);//done
class Bad horizontal("horizontal.stl",GREEN,7.61905,24.53701,95.57565);//done
class Bad base("base.stl",GREEN,-0.328019,-16.33702,-58.00608);//done
class Bad bottom_plate("bottom.stl",RED,-13.79333,33.5328,3.79485);//done
class Bad left1("left.stl",RED,-30.85771,26.58718,15.50329);//done
class Bad rigth1("rigth.stl",RED,21.32011,26.58718,15.50329 );//done
class Bad sphere("sphere.stl",RED,0,0,0);
class Bad secondtriangle("secondtriangle.stl",GREEN,14.91295,143.89566,93.21524);//done
class Bad SG90("SG90.stl",BLUE,25.16291,186.04488,72.00875);//done
class Bad SG90holder("SG90holder.stl",YELLOW,19.18367,211.53325,93.99998);//done

//


void loadFile (const char* fn,std::string& str)
{
    std::ifstream in(fn);
    if(!in.is_open())
    {
        std::cout <<"the file" << fn << " cannot be opened \n";
        return;
    }
    char tmp[300];
    while(in.eof())
    {
        in.getline(tmp,300);
        str+=tmp;
        str+='\n';
    }


}

unsigned int  loadShader(std::string& source, unsigned int mode )
{
    unsigned int id;
    id=glCreateShader(mode);
    const char* csource=source.c_str();
    glShaderSource(id,1,&csource,NULL);
    glCompileShader(id);
    char error[1000];
    glGetShaderInfoLog(id,1000,NULL,error);
    std::cout <<"Compile status:\n" << error << std::endl;
    return id;
}
unsigned vs,fs,program;

void initShader(const char* vname,const char* fname)
{
    std::string source;
    loadFile(vname,source);
    vs=loadShader(source,GL_VERTEX_SHADER);
    source="";
    loadFile(fname,source);
    fs=loadShader(source,GL_FRAGMENT_SHADER);

    program=glCreateProgram();
    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glUseProgram(program);


}

void clean()
{
    glDetachShader(program,vs);
    glDetachShader(program,fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteProgram(program);


}
/*
int countCameras()
{
   cv::VideoCapture temp_camera;
   int maxTested = 10;
   for (int i = 0; i < maxTested; i++){
     cv::VideoCapture temp_camera(i);
     bool res = (!temp_camera.isOpened());
     temp_camera.release();
     if (res)
     {
       return i;
     }
   }
   return maxTested;
}
*/

DWORD WriteCom(char *buf, int len)
{
	DWORD nSend;

	int m=0,i;
	for (i=0;i<len-1;i++)
    {
        WriteFile(handlePort, &buf[i], 1, &nSend, NULL);
        //printf("[%c]\n",buf[i]);
        m=m+(int)nSend;

    }
    PurgeComm(handlePort, PURGE_TXCLEAR | PURGE_RXABORT |PURGE_RXCLEAR | PURGE_TXABORT);
	return nSend;
}

int ReadCom(char *bufq, int len)
{
	DWORD nRec;
	ReadFile(handlePort, bufq, 80, &nRec, NULL);
        if (nRec>0)
        {


       //     printf("[dARM says: %s]\n",bufq);
    FlushFileBuffers(handlePort);
    PurgeComm(handlePort, PURGE_TXCLEAR | PURGE_RXABORT |PURGE_RXCLEAR | PURGE_TXABORT);
    return (int)nRec;
        }
	return 0;
}

void Render()
{
        //glEnable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 100.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        //Enable (GL_LINE_SMOOTH);
        gluLookAt(-1.5, 1.0, 7.0,0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        //glLoadIdentity();
        angle =  pos;
        if (angle >= 360.0f)
        {
                angle = 0.0f;
        }

        glPushMatrix();
                glLoadIdentity();

                glTranslatef(0.0f, 0.0f, -280.0f+pos2);
                glRotatef(angle-160, 0.0f, 1.0f, 0.0f);
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                glRotatef(90, 0.0f, 0.0f, 1.0f);
                glRotatef(180,1.0f, 0.0f, 0.0f);
                /*
                PLANE.draw();
                ARM1.draw();
                LEFT_PLATE.draw();
                MAIN_GEAR.draw();
                MAIN_BAR.draw();
                SMALL_GEAR1.draw();
                SMALL_GEAR2.draw();
                BEARING.draw();
                RIGHT_PLATE.draw();
                HORIZONTAL.draw();
                ARM2.draw();
                ARM3.draw();
                MOTOR1.draw();
                MOTOR2.draw();
                MAIN_GEAR2.draw();
                */
///////////
                plane.draw();
                gear2.draw();
                main_gear.draw();
                main_gear3.draw();//done
                arm1.draw();//done
                arm2.draw();//done
                arm3.draw();//done
                palanca2.draw();//
                main_bar.draw();//done
                small_gear1.draw();//done
                small_gear2.draw();//done
                small_gear3.draw();//done
                upper_triangle.draw();//done
                motor1.draw();//done
                motor2.draw();//done
                motor3.draw();//done
                horizontal.draw();//done
                base.draw();//done
                bottom_plate.draw();//done
                left1.draw();//done
                rigth1.draw();//done
                sphere.draw();
                secondtriangle.draw();//done
                SG90.draw();//done
                SG90holder.draw();//done







//////////

        glPopMatrix();
        glFlush();
        SwapBuffers(g_HDC);
}

void SetupPixelFormat(HDC hDC)
{
        /*      Pixel format index
        */
        int nPixelFormat;

        static PIXELFORMATDESCRIPTOR pfd = {
                sizeof(PIXELFORMATDESCRIPTOR),          //size of structure
                1,                                      //default version
                PFD_DRAW_TO_WINDOW |                    //window drawing support
                PFD_SUPPORT_OPENGL |                    //opengl support
                PFD_DOUBLEBUFFER,                       //double buffering support
                PFD_TYPE_RGBA,                          //RGBA color mode
                32,                                     //32 bit color mode
                0, 0, 0, 0, 0, 0,                       //ignore color bits
                0,                                      //no alpha buffer
                0,                                      //ignore shift bit
                0,                                      //no accumulation buffer
                0, 0, 0, 0,                             //ignore accumulation bits
                16,                                     //16 bit z-buffer size
                0,                                      //no stencil buffer
                0,                                      //no aux buffer
                PFD_MAIN_PLANE,                         //main drawing plane
                0,                                      //reserved
                0, 0, 0 };                              //layer masks ignored

                /*      Choose best matching format*/
                nPixelFormat = ChoosePixelFormat(hDC, &pfd);

                /*      Set the pixel format to the device context*/
                SetPixelFormat(hDC, nPixelFormat, &pfd);
}


LRESULT CALLBACK WinProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR lpCmdLine,int nShowCmd)
{

//////////////////


/*
if (!stream1.isOpened()) { //check if video device has been initialised
cout << "cannot open camera";
}
Mat cameraFrame;
//unconditional loop
while (true) {

stream1.read(cameraFrame);
imshow("cam", cameraFrame);
if (waitKey(30) >= 0)
break;
}
*/
//////////////////
	WNDCLASSEX wClass;
	ZeroMemory(&wClass,sizeof(WNDCLASSEX));
	wClass.cbClsExtra=NULL;
	wClass.cbSize=sizeof(WNDCLASSEX);
	wClass.cbWndExtra=NULL;
	wClass.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wClass.hIcon=NULL;
	wClass.hIconSm=NULL;
	wClass.hInstance=hInst;
	wClass.lpfnWndProc=(WNDPROC)WinProc;
	wClass.lpszClassName="Window Class";
	wClass.lpszMenuName=NULL;
	wClass.style=CS_HREDRAW|CS_VREDRAW;

	if(!RegisterClassEx(&wClass))
	{
		int nResult=GetLastError();
		MessageBox(NULL,
			"Window class creation failed\r\n",
			"Window Class Failed",
			MB_ICONERROR);
	}

	HWND hWnd=CreateWindowEx(NULL,
			"Window Class",
			"Windows application",
			WS_OVERLAPPEDWINDOW,
			10,
			10,
			1900,
			980,
			NULL,
			NULL,
			hInst,
			NULL);



	if(!hWnd)
	{
		int nResult=GetLastError();

		MessageBox(NULL,
			"Window creation failed\r\n",
			"Window Creation Failed",
			MB_ICONERROR);
	}


	handlePort = CreateFile("\\\\.\\COM9",  // Specify port device: default "COM1"
        GENERIC_READ | GENERIC_WRITE ,       // Specify mode that open device.
        0,                                  // the devide isn't shared.
        NULL,                               // the object gets a default security.
        OPEN_EXISTING,                      // Specify which action to take on file.
        0,                                  // default.
        NULL);

///////////Serial port Config ////////////
    if(!handlePort)
	{
		int nResult=GetLastError();

		MessageBox(NULL,
			"Windows port failed",
			"Failed",
			MB_ICONERROR);
	}
        if (GetCommState(handlePort,&config_) == 0)
        {
        MessageBox(NULL,"Could not open the serial port.","problem",MB_ICONERROR);

        }
    memset(&config_, 0, sizeof(config_));
    config_.DCBlength = sizeof(config_);
    if ( !GetCommState(handlePort, &config_))
        printf("getting comm state");
    if (!BuildCommDCB("baud=57600 parity=n data=8 stop=1", &config_))
        printf("building comm DCB");
    if (!SetCommState(handlePort, &config_))
        printf("adjusting port settings");



    // instance an object of COMMTIMEOUTS.
    COMMTIMEOUTS comTimeOut;

    comTimeOut.ReadIntervalTimeout = 3;
    comTimeOut.ReadTotalTimeoutMultiplier = 3;
    comTimeOut.ReadTotalTimeoutConstant = 2;
    comTimeOut.WriteTotalTimeoutMultiplier = 3;
    comTimeOut.WriteTotalTimeoutConstant = 2;
    SetCommTimeouts(handlePort,&comTimeOut);

    if (!SetCommTimeouts(handlePort, &comTimeOut))
        printf("setting port time-outs.");


char init[] = "";
DWORD written;

    if (!EscapeCommFunction(handlePort, CLRDTR))
        printf("clearing DTR");
    Sleep(200);
    if (!EscapeCommFunction(handlePort, SETDTR))
        printf("setting DTR");

    if ( !WriteFile(handlePort, init, sizeof(init), &written, NULL))
        printf("writing data to port");

    if (written != sizeof(init))
        printf("not all data written to port");


SetCommMask( handlePort,EV_RXCHAR);


///////////Serial port Config ////////////


    ShowWindow(hWnd,nShowCmd);

	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));

   int done =0;
	while (!done)
        {
                GetMessage(&msg,NULL,0,0);

                        if (msg.message == WM_QUIT)     //did we receive a quit message?
                        {
                                done = true;
                        }
                        else
                        {
                                Render();

                                TranslateMessage(&msg);
                                DispatchMessage(&msg);
                        }
        }







////////////////////

	return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
const  unsigned char* texta;
    int width, height;
	switch(msg)
	{
		case WM_CREATE:
		{
			// Create an edit box
			hEdit=CreateWindowEx(WS_EX_CLIENTEDGE,
				"EDIT",
				"",
				WS_CHILD|WS_VISIBLE|
				ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,
				5,
				10,
				1600,
				900,
				hWnd,
				(HMENU)IDC_MAIN_EDIT,
				GetModuleHandle(NULL),
				NULL);
			HGDIOBJ hfDefault=GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(hEdit,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));
			SendMessage(hEdit,
				WM_SETTEXT,
				NULL,
				(LPARAM)"OpenGL");

			// Create a push button
			HWND hWndButton=CreateWindowEx(NULL,
				"BUTTON",
				"Enabled",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				450+Xexpand,
				220,
				100,
				24,
				hWnd,
				(HMENU)IDC_MAIN_BUTTON,
				GetModuleHandle(NULL),
				NULL);


			SendMessage(hWndButton,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

				static HGLRC hRC;
                static HDC hDC;

			  hDC = GetDC(hEdit);  //get current windows device context
                        g_HDC = hDC;
                        SetupPixelFormat(hDC); //call our pixel format setup function
                        hRC = wglCreateContext(hDC);
                        wglMakeCurrent(hDC, hRC);
//////////DISABLED BUTTON/////////////////////

HWND hWndButton2=CreateWindowEx(NULL,
				"BUTTON",
				"Disabled",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				450+Xexpand,
				250,
				100,
				24,
				hWnd,
				(HMENU)IDC_MAIN_BUTTON2,
				GetModuleHandle(NULL),
				NULL);


			SendMessage(hWndButton2,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));


///////////////////////////////
            hWndSlider1=CreateWindowEx(NULL,
				"msctls_trackbar32",
				"Rotation",
				 SS_CENTER | WS_CHILD | WS_VISIBLE|TBS_HORZ,
				420+Xexpand,
				10,
				200,
				30,
				hWnd,
				(HMENU)IDC_SLIDER_BUTTON,
                GetModuleHandle(NULL),
				NULL);

            if( hWndSlider1 == NULL )
            {
                TCHAR errbuf[300];
                wsprintf( errbuf, TEXT("error de codigo #%d"), GetLastError() );
                FatalAppExit( 0, errbuf );
            }
              SendMessage(hWndSlider1, TBM_SETRANGE,  TRUE, MAKELONG(-180, 180));
              SendMessage(hWndSlider1, TBM_SETPAGESIZE, 0,  10);
              SendMessage(hWndSlider1, TBM_SETTICFREQ, 10, 0);
              SendMessage(hWndSlider1, TBM_SETPOS, FALSE, 0);

            hWndSlider2=CreateWindowEx(NULL,
				"msctls_trackbar32",
				"Rotation",
				 SS_CENTER | WS_CHILD | WS_VISIBLE|TBS_HORZ,
				420+Xexpand,
				50,
				200,
				30,
				hWnd,
				(HMENU)IDC_SLIDER_BUTTON2,
                GetModuleHandle(NULL),
				NULL);

            if( hWndSlider2 == NULL )
            {
                TCHAR errbuf[300];
                wsprintf( errbuf, TEXT("error de codigo #%d"), GetLastError() );
                FatalAppExit( 0, errbuf );
            }
              SendMessage(hWndSlider2, TBM_SETRANGE,  TRUE, MAKELONG(-400, 400));
              SendMessage(hWndSlider2, TBM_SETPAGESIZE, 0,  10);
              SendMessage(hWndSlider2, TBM_SETTICFREQ, 10, 0);
              SendMessage(hWndSlider2, TBM_SETPOS, FALSE, 0);

            hWndSlider3=CreateWindowEx(NULL,
				"msctls_trackbar32",
				"Rotation2",
				 SS_CENTER | WS_CHILD | WS_VISIBLE|TBS_HORZ,
				420+Xexpand,
				280,
				200,
				30,
				hWnd,
				(HMENU)IDC_SLIDER_BUTTON3,
                GetModuleHandle(NULL),
				NULL);

            if( hWndSlider3 == NULL )
            {
                TCHAR errbuf[300];
                wsprintf( errbuf, TEXT("error de codigo #%d"), GetLastError() );
                FatalAppExit( 0, errbuf );
            }
              SendMessage(hWndSlider3, TBM_SETRANGE,  TRUE, MAKELONG(00, 100));
              SendMessage(hWndSlider3, TBM_SETPAGESIZE, 0,  10);
              SendMessage(hWndSlider3, TBM_SETTICFREQ, 10, 0);
              SendMessage(hWndSlider3, TBM_SETPOS, FALSE, 0);

              //////////// Second edit

              hEdit=CreateWindowEx(WS_EX_CLIENTEDGE,
				"EDIT",
				"",
				WS_CHILD|WS_VISIBLE|
				ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,
				420+Xexpand,
				330,
				190,
				90,
				hWnd,
				(HMENU)IDC_MAIN_EDIT2,
				GetModuleHandle(NULL),
				NULL);


              //////////////

              hGrpButtons=CreateWindowEx(WS_EX_WINDOWEDGE,
                    "BUTTON",
                    "Select Object:",
                    WS_VISIBLE | WS_CHILD|BS_GROUPBOX,// <----BS_GROUPBOX does nothing on the grouping
                    420+Xexpand,
                    90,
                    200,
                    110,
                    hWnd,
                    (HMENU)IDC_GRPBUTTONS,
                    GetModuleHandle(NULL),
                    NULL);
            CreateWindowEx(WS_EX_WINDOWEDGE,
                    "BUTTON",
                    "first ",
                    WS_VISIBLE | WS_CHILD|BS_AUTORADIOBUTTON|WS_GROUP,  // <---- WS_GROUP group the following radio buttons 1st,2nd button
                    430+Xexpand,
                    110,
                    150,
                    20,
                    hWnd, //<----- Use main window handle
                    (HMENU)IDC_CHK1,
                    GetModuleHandle(NULL), NULL);
            CreateWindowEx(WS_EX_WINDOWEDGE,
                    "BUTTON",
                    "Small Gear",
                    WS_VISIBLE | WS_CHILD|BS_AUTORADIOBUTTON,  // Styles
                    430+Xexpand,
                    130,
                    150,
                    20,
                    hWnd,
                    (HMENU)IDC_CHK2,
                    GetModuleHandle(NULL), NULL);
            CreateWindowEx(WS_EX_WINDOWEDGE,
                    "BUTTON",
                    "third",
                    WS_VISIBLE | WS_CHILD|BS_AUTORADIOBUTTON, //|WS_GROUP,  //<---Start second group for 3rd,4th button
                    430+Xexpand,
                    150,
                    150,
                    20,
                    hWnd,
                    (HMENU)IDC_CHK3,
                    GetModuleHandle(NULL), NULL);
            CreateWindowEx(WS_EX_WINDOWEDGE,
                    "BUTTON",
                    "forth radio button",
                    WS_VISIBLE | WS_CHILD|BS_AUTORADIOBUTTON,  // Styles
                    430+Xexpand,
                    170,
                    150,
                    20,
                    hWnd,
                    (HMENU)IDC_CHK4,
                    GetModuleHandle(NULL), NULL);

//////////UP BUTTON/////////////////////

HWND hWndButton3=CreateWindowEx(NULL,
				"BUTTON",
				"UP 10",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				420+Xexpand,
				420,
				100,
				24,
				hWnd,
				(HMENU)IDC_UP_BUTTON,
				GetModuleHandle(NULL),
				NULL);


			SendMessage(hWndButton3,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

///////////////////////////////

//////////Down BUTTON/////////////////////

HWND hWndButton4=CreateWindowEx(NULL,
				"BUTTON",
				"Down",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				420+Xexpand+100+3,
				420,
				100,
				24,
				hWnd,
				(HMENU)IDC_DOWN_BUTTON,
				GetModuleHandle(NULL),
				NULL);


			SendMessage(hWndButton4,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));


///////////////////////////////




//////////Feedback BUTTON/////////////////////

HWND hWndButton5=CreateWindowEx(NULL,
				"BUTTON",
				"Feedback",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				420+Xexpand+100+3,
				520,
				100,
				24,
				hWnd,
				(HMENU)FEED_DOWN_BUTTON,
				GetModuleHandle(NULL),
				NULL);


			SendMessage(hWndButton5,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));


///////////////////////////////


//////////Front BUTTON/////////////////////

HWND hWndButton6=CreateWindowEx(NULL,
				"BUTTON",
				"Front",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				420+Xexpand,
				460,
				110,
				24,
				hWnd,
				(HMENU)IDC_FRONT_BUTTON,
				GetModuleHandle(NULL),
				NULL);


			SendMessage(hWndButton6,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

///////////////////////////////

//////////Back BUTTON/////////////////////

HWND hWndButton7=CreateWindowEx(NULL,
				"BUTTON",
				"Back",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				420+Xexpand+100+3,
				460,
				110,
				24,
				hWnd,
				(HMENU)IDC_BACK_BUTTON,
				GetModuleHandle(NULL),
				NULL);


			SendMessage(hWndButton7,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

//////////Right BUTTON/////////////////////

HWND hWndButton8=CreateWindowEx(NULL,
				"BUTTON",
				"Right",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				420+Xexpand,
				490,
				110,
				24,
				hWnd,
				(HMENU)IDC_RIGTH_BUTTON,
				GetModuleHandle(NULL),
				NULL);


			SendMessage(hWndButton8,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));
//////////Left BUTTON/////////////////////
HWND hWndButton9=CreateWindowEx(NULL,
				"BUTTON",
				"Left",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				420+Xexpand+100+3,
				490,
				110,
				24,
				hWnd,
				(HMENU)IDC_LEFT_BUTTON,
				GetModuleHandle(NULL),
				NULL);


			SendMessage(hWndButton9,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

//////////Calculate BUTTON/////////////////////
HWND hWndButton10=CreateWindowEx(NULL,
				"BUTTON",
				"Calculate",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				420+Xexpand+100+3,
				520,
				110,
				24,
				hWnd,
				(HMENU)IDC_CALCULATE_BUTTON,
				GetModuleHandle(NULL),
				NULL);


			SendMessage(hWndButton10,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));


		}
		break;
///////////////////////////////


		case WM_SIZE:

                        /*      Retrieve width and height*/
                        height = HIWORD(lParam);
                        width = LOWORD(lParam);
                        Xexpand= height;
                        Yexpand=width;

                        if (height == 0)
                        {
                                height = 1;
                        }
                        glViewport(0, 0, width, height);
                        glMatrixMode(GL_PROJECTION);
                        glLoadIdentity(); //reset projection matrix
                        gluPerspective(50.0f, (GLfloat)width/(GLfloat)height, 1.0f, 1000.0f);
                        glMatrixMode(GL_MODELVIEW); //set modelview matrix
                        glLoadIdentity(); //reset modelview matrix
                         glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
                          glEnable(GL_LIGHTING);
                          glEnable(GL_LIGHT0);
                          glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
                          glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
                          glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
                          glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
                          glEnable(GL_DEPTH_TEST);
                          initShader("vertex.vs","fragment.frag");
                         glEnable(GL_COLOR_MATERIAL);

                        return 0;
                        break;


		case WM_COMMAND:
			switch(LOWORD(wParam))
            {
				 case 1:

                {
                    ShowWindow(camhwnd,SW_SHOW);
                    SendMessage(camhwnd,WM_CAP_DRIVER_CONNECT,0,0);
                    SendMessage(camhwnd, WM_CAP_SET_SCALE, true , 0);
                    SendMessage(camhwnd, WM_CAP_SET_PREVIEWRATE, 66, 0);
                    SendMessage(camhwnd, WM_CAP_SET_PREVIEW, true , 0);
                    break;
                }
                case 2:
                {
                    ShowWindow(camhwnd,SW_HIDE);
                    SendMessage(camhwnd, WM_CAP_DRIVER_DISCONNECT, 0, 0);
                    break;
                }



				case IDC_MAIN_BUTTON:
				{
					char buffer[256];

                    ReadCom(buffer,13);
					WriteCom("M17\r",sizeof("M17\r"));

					MessageBox(NULL,
						buffer,
						"Motor Enabled",
						MB_ICONINFORMATION);
					break;
				}

				case IDC_MAIN_BUTTON2:
				{
					char buffer[256];

                    ReadCom(buffer,13);
					WriteCom("M18\r",sizeof("M18\r"));
					MessageBox(NULL,
						buffer,
						"Motor disabled",
						MB_ICONINFORMATION);
                    break;
				}
                case IDC_UP_BUTTON:
				{
                    yPOS--;
                    std::string s;
                    s= patch::to_string((float)yPOS);
                    //= QString::number((float)yPOS);
                    std::cout << "In xMOverD "<<std::endl;
                    s="pos Y "+s+"\r";
                    small_gear2.degree=yPOS*ratio;
                    gear2.degree=-yPOS;
                    horizontal.degree=gear2.degree;
                    palanca2.degree=gear2.degree;
                    arm1.degree=horizontal.degree;
                    arm2.deltaZ=-65*sin(gear2.degree*2*3.1416/360);
                    arm2.deltaY=65-65*cos(gear2.degree*2*3.1416/360);
                    secondtriangle.deltaY=-120+120*cos(horizontal.degree*3.1416/180)+horizontal.deltaY;
                    secondtriangle.deltaZ=120*sin(horizontal.degree*3.1416/180)+horizontal.deltaZ;
                    SG90.deltaY=secondtriangle.deltaY;
                    SG90.deltaZ=secondtriangle.deltaZ;
                    SG90holder.deltaY=secondtriangle.deltaY;
                    SG90holder.deltaZ=secondtriangle.deltaZ;

					break;
				}

				case IDC_DOWN_BUTTON:
				{
/*

					char uffer[]="wewewe";
                    pos3=pos3-stepR;
                    //if(pos3>90)
                        //pos3=90;
                    small_gear1.degree=pos3;
                    main_gear.degree=small_gear1.degree*20/45;// the teeth ratio
                    main_bar.degree=main_gear.degree;
                    //BEARING.degree=main_gear.degree;
                    horizontal.degree=main_gear.degree;
                    arm2.degree=main_bar.degree;
                    snprintf(Buffer, sizeof(Buffer),"pos X %d\r\n",pos3);
                    const char *ptr = strchr(Buffer, '\r');
                    int index = ptr-Buffer;
                    ReadCom(uffer,13);
					WriteCom(Buffer,index+2);
                    texta=glGetString(GL_VERSION);

                    std::cout <<texta <<std::endl;
                    */
                    /////////
                    yPOS++;
                    std::string s;
                    //= QString::number((float)yPOS);
                    std::cout << "In xMOverD "<<std::endl;
                    s="pos Y "+s+"\r";
                    small_gear2.degree=yPOS*ratio;
                    gear2.degree=-yPOS;
                    horizontal.degree=gear2.degree;
                    palanca2.degree=gear2.degree;
                    arm1.degree=horizontal.degree;
                    arm2.deltaZ=-65*sin(gear2.degree*2*3.1416/360);
                    arm2.deltaY=65-65*cos(gear2.degree*2*3.1416/360);
                    secondtriangle.deltaY=-120+120*cos(horizontal.degree*3.1416/180)+horizontal.deltaY;
                    secondtriangle.deltaZ=120*sin(horizontal.degree*3.1416/180)+horizontal.deltaZ;
                    SG90.deltaY=secondtriangle.deltaY;
                    SG90.deltaZ=secondtriangle.deltaZ;
                    SG90holder.deltaY=secondtriangle.deltaY;
                    SG90holder.deltaZ=secondtriangle.deltaZ;

					break;
				}

				case FEED_DOWN_BUTTON:
				{


					char uffer[]="wewewewe";
					char Uffer[]="wewewewe";
                    snprintf(Buffer, sizeof(Buffer),"backr\r\n",pos3);
                    const char *ptr = strchr(Buffer, '\r');
                    int index = ptr-Buffer;
                    ReadCom(uffer,6);
					WriteCom(Buffer,index+2);
					Sleep(30);
					ReadCom(uffer,5);uffer[0]="wererwre";
					printf("%s",uffer);
					SendMessage(hEdit,EM_REPLACESEL,NULL,uffer);



					snprintf(Buffer, sizeof(Buffer),"backl\r\n",pos3);
                    ptr = strchr(Buffer, '\r');
                    index = ptr-Buffer;
                    ReadCom(uffer,6);
					WriteCom(Buffer,index+2);
					Sleep(30);
					ReadCom(uffer,5);
					printf("%s",uffer);
                    SendMessage(hEdit,EM_REPLACESEL,NULL,uffer);


					break;
				}

				case IDC_FRONT_BUTTON:
				{

                    /////////
                    xPOS--;
                    string s;
                    //= QString::number((float)xPOS/1);
                    std::cout << "In Front "<<std::endl;
                    s="pos X "+s+"\r";
                    small_gear1.degree=-xPOS*ratio;
                    main_gear.degree=xPOS;
                    main_bar.degree=main_gear.degree;
                    arm3.degree=main_bar.degree;
                    upper_triangle.deltaY=-120*sin( main_bar.degree*2*3.1416/360);
                    upper_triangle.deltaZ=-120+120*cos( main_bar.degree*2*3.1416/360);
                    horizontal.deltaY=-120*sin( main_bar.degree*2*3.1416/360);
                    horizontal.deltaZ=-120+120*cos( main_bar.degree*2*3.1416/360);
                    arm2.degree=arm3.degree;
                    horizontal.deltaY=-120*sin( main_bar.degree*2*3.1416/360);
                    horizontal.deltaZ=-120+120*cos( main_bar.degree*2*3.1416/360);
                    arm1.deltaY=horizontal.deltaY;
                    arm1.deltaZ=horizontal.deltaZ;
                    secondtriangle.deltaY=-120+120*cos(horizontal.degree*3.1416/180)+horizontal.deltaY;
                    secondtriangle.deltaZ=120*sin(horizontal.degree*3.1416/180)+horizontal.deltaZ;
                    SG90.deltaY=secondtriangle.deltaY;
                    SG90.deltaZ=secondtriangle.deltaZ;
                    SG90holder.deltaY=secondtriangle.deltaY;
                    SG90holder.deltaZ=secondtriangle.deltaZ;


                    //////////////////
					break;
				}

				case IDC_BACK_BUTTON:
				{
                    /////////
                    xPOS++;
                    string s;
                    //= QString::number((float)xPOS/1);
                    std::cout << "In Front "<<std::endl;
                    s="pos X "+s+"\r";
                    small_gear1.degree=-xPOS*ratio;
                    main_gear.degree=xPOS;
                    main_bar.degree=main_gear.degree;
                    arm3.degree=main_bar.degree;
                    upper_triangle.deltaY=-120*sin( main_bar.degree*2*3.1416/360);
                    upper_triangle.deltaZ=-120+120*cos( main_bar.degree*2*3.1416/360);
                    horizontal.deltaY=-120*sin( main_bar.degree*2*3.1416/360);
                    horizontal.deltaZ=-120+120*cos( main_bar.degree*2*3.1416/360);
                    arm2.degree=arm3.degree;
                    horizontal.deltaY=-120*sin( main_bar.degree*2*3.1416/360);
                    horizontal.deltaZ=-120+120*cos( main_bar.degree*2*3.1416/360);
                    arm1.deltaY=horizontal.deltaY;
                    arm1.deltaZ=horizontal.deltaZ;
                    secondtriangle.deltaY=-120+120*cos(horizontal.degree*3.1416/180)+horizontal.deltaY;
                    secondtriangle.deltaZ=120*sin(horizontal.degree*3.1416/180)+horizontal.deltaZ;
                    SG90.deltaY=secondtriangle.deltaY;
                    SG90.deltaZ=secondtriangle.deltaZ;
                    SG90holder.deltaY=secondtriangle.deltaY;
                    SG90holder.deltaZ=secondtriangle.deltaZ;
                    //////////////////
					break;
				}
				case IDC_RIGTH_BUTTON:
				{
                    /////////
                    zPOS--;
                    degreeZ=zPOS;
                    string s;
                    //= QString::number((float)zPOS/1);
                    s="pos Z "+s+"\r";
                    small_gear2.degreeZ=degreeZ;
                    gear2.degreeZ=degreeZ;;
                    horizontal.degreeZ=degreeZ;
                    palanca2.degreeZ=degreeZ;
                    arm1.degreeZ=degreeZ;
                    arm2.degreeZ=degreeZ;
                    arm3.degreeZ=degreeZ;
                    left1.degreeZ=degreeZ;
                    rigth1.degreeZ=degreeZ;
                    small_gear1.degreeZ=degreeZ;
                    small_gear3.degreeZ=degreeZ;
                    motor1.degreeZ=motor2.degreeZ=motor3.degreeZ=degreeZ;
                    palanca2.degreeZ=degreeZ;
                    bottom_plate.degreeZ=degreeZ;
                    main_bar.degreeZ=secondtriangle.degreeZ=degreeZ;
                    main_gear.degreeZ=upper_triangle.degreeZ=degreeZ;
                    SG90.degreeZ=upper_triangle.degreeZ=degreeZ;
                    SG90holder.degreeZ=upper_triangle.degreeZ=degreeZ;
                    //////////////////
					break;
				}
				case IDC_LEFT_BUTTON:
				{
                    /////////
                    zPOS++;
                    degreeZ=zPOS;
                    string s;
                    //= QString::number((float)zPOS/1);
                    s="pos Z "+s+"\r";
                    small_gear2.degreeZ=degreeZ;
                    gear2.degreeZ=degreeZ;;
                    horizontal.degreeZ=degreeZ;
                    palanca2.degreeZ=degreeZ;
                    arm1.degreeZ=degreeZ;
                    arm2.degreeZ=degreeZ;
                    arm3.degreeZ=degreeZ;
                    left1.degreeZ=degreeZ;
                    rigth1.degreeZ=degreeZ;
                    small_gear1.degreeZ=degreeZ;
                    small_gear3.degreeZ=degreeZ;
                    motor1.degreeZ=motor2.degreeZ=motor3.degreeZ=degreeZ;
                    palanca2.degreeZ=degreeZ;
                    bottom_plate.degreeZ=degreeZ;
                    main_bar.degreeZ=secondtriangle.degreeZ=degreeZ;
                    main_gear.degreeZ=upper_triangle.degreeZ=degreeZ;
                    SG90.degreeZ=upper_triangle.degreeZ=degreeZ;
                    SG90holder.degreeZ=upper_triangle.degreeZ=degreeZ;
                    //////////////////
					break;
				}

				case IDC_CALCULATE_BUTTON:
				{
                    /////////
                   /* float x,y,y1,z,alpha,beta,gamma,m,l,c,n,phi,s,theta;
                    QString str;
                    l=12;
                    str=ui->X->toPlainText();
                    x=str.toDouble();
                    str=ui->Y->toPlainText();
                    y=str.toDouble();
                    str=ui->Z->toPlainText();
                    z=str.toDouble();
                    s=sqrt(x*x+y*y);
                    theta=atan(y/x);
                    //// Then change y by s
                    m=sqrt(s*s+z*z);
                    alpha=acos(m/(2*l));
                    //QString M = QString::number(alpha*180/3.1416);
                    //ui->m->setText(M);
                    gamma=atan(z/s);
                    beta=3.1416/2-alpha-gamma;
                    c=3.1416/2-beta;
                    phi=acos((m*m-2*l*l)/(-2*l*l));
                    n=-(3.1416-c-phi);
                   QString BETA = QString::number(beta*180/3.1416);
                   QString ALPHA = QString::number(n*180/3.1416);
                   QString GAMMA = QString::number(gamma*180/3.1416);
                   QString PHI = QString::number(phi*180/3.1416);
                   QString THETA =QString::number(90-theta*180/3.1416);
                   QString S =QString::number(s);
                   QString M = QString::number(m);
                   ui->alpha->setText(ALPHA);
                   ui->beta->setText(BETA);
                   ui->gamma->setText(GAMMA);
                   ui->theta->setText(THETA);
                   ui->m->setText(M);
                   ui->s->setText(S);
                   ui->phi->setText(PHI);
                   xPOS=-beta*180/(3.1416);
                   yPOS=-n*180/(3.1416);
                   zPOS=90-theta*180/3.1416;
                   xMoverD();
                   yMoverD();
                   zMoverD();

                    //////////////////*/
					break;
				}

				case IDC_CHK1:
				{
				    printf("Rad buto 1\n");
				    small_gear1.select=false;
				    break;
				}
				case IDC_CHK2:
				{
				    printf("\nMain Gear selected\n");
				    small_gear1.select=true;

				    break;
				}
				case IDC_CHK3:
				{
				    printf("Small Gear selected\n");
				    small_gear1.select=false;
				    break;
				}
                case IDC_CHK4:
				{
				    printf("Rad buto 4\n");
				    break;
				}

				break;
			}
			break;


		case WM_HSCROLL:
		    {


		    pos = SendMessageW(hWndSlider1, TBM_GETPOS, 0, 0);
		    pos2= SendMessageW(hWndSlider2, TBM_GETPOS, 0, 0);
		    pos3= SendMessageW(hWndSlider3, TBM_GETPOS, 0, 0);

                  break;
		    }


		case WM_DESTROY:
		{
			PostQuitMessage(0);
			CloseHandle(handlePort);
			return 0;
		}
		break;
	}

	return DefWindowProc(hWnd,msg,wParam,lParam);
}

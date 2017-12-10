#include <windows.h>
#include <gl/gl.h>
#include"ClaseOpenGL.h"
///Copyright (C) <2017>  <Eliseo Rivera> curso.tareas@gmail.com
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
vector3d d1,d2,d3,d4,d5,d6,d7;

float dtheta(3);
 ClaseOpenGL* Miclase=NULL;
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{

    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;


    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;

Miclase = new ClaseOpenGL;  //agregar código opengl

    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "Robótica. Configuración  Denavit–Hartenberg ",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          800,
                          600,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
EnableOpenGL(hwnd, &hDC, &hRC); //va primero esto
ShowWindow(hwnd, nCmdShow); // y despues mostrar ventana
UpdateWindow(hwnd);					// update the window

    /* enable OpenGL for the window */

Miclase->inicializar();
SwapBuffers(hDC);
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            Miclase->renderizar();
            SwapBuffers(hDC);
            Miclase->preparar(0.001);

            Sleep (1);
        }
    }
delete Miclase;
Miclase=NULL;
    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{int height, width;
    switch (uMsg)
    {
    case WM_CREATE:


    break;
        case WM_CLOSE:
            PostQuitMessage(0);
        break;
    case WM_SIZE:
		height = HIWORD(lParam);		// retrieve width and height
		width = LOWORD(lParam);

	Miclase->Resize(width, height);

    break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
                Matrix P({0,0,0.0},1);
    ( Miclase->SSRMS.TH*P).mostrar();
            switch (wParam)
            {

          case 'R':

                Miclase->SSRMS.theta1=Miclase->SSRMS.theta1+dtheta;
                Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta1, {0,0,6});     //b1
                Miclase->SSRMS.THList[2]=Miclase->SSRMS.THz;

                break;
            case 'T':

                Miclase->SSRMS.theta1=Miclase->SSRMS.theta1-dtheta;
                Miclase->SSRMS.AplicarTHz( Miclase->SSRMS.theta1, {0,0,6});     //b1
              Miclase->SSRMS.THList[2]=Miclase->SSRMS.THz;


                break;

             case 'F':

                Miclase->SSRMS.theta2=Miclase->SSRMS.theta2+dtheta;
                Miclase->SSRMS.AplicarTHz(   Miclase->SSRMS.theta2, {0,0,-1});  //b2
                Miclase->SSRMS.THList[4]=Miclase->SSRMS.THz;

                break;
            case 'G':

                Miclase->SSRMS.theta2=Miclase->SSRMS.theta2-dtheta;
                Miclase->SSRMS.AplicarTHz(   Miclase->SSRMS.theta2, {0,0,-1});     //b2
                Miclase->SSRMS.THList[4]=Miclase->SSRMS.THz;


                break;

         case 'V':

                Miclase->SSRMS.z3=Miclase->SSRMS.z3+.1;
                Miclase->SSRMS.AplicarTHz(   Miclase->SSRMS.theta3, {0,0,Miclase->SSRMS.z3});     //b3
                Miclase->SSRMS.THList[6]=Miclase->SSRMS.THz;

                break;
            case 'B':

         Miclase->SSRMS.z3=Miclase->SSRMS.z3-.1;
                Miclase->SSRMS.AplicarTHz(   Miclase->SSRMS.theta3, {0,0,Miclase->SSRMS.z3});     //b3
                Miclase->SSRMS.THList[6]=Miclase->SSRMS.THz;

                break;


             case 'U':

                Miclase->SSRMS.theta4=Miclase->SSRMS.theta4+dtheta;
                Miclase->SSRMS.AplicarTHz(   Miclase->SSRMS.theta4, {0,0,0});     //b4
                Miclase->SSRMS.THList[8]=Miclase->SSRMS.THz;

                break;
            case 'I':

                Miclase->SSRMS.theta4=Miclase->SSRMS.theta4-dtheta;
                Miclase->SSRMS.AplicarTHz(   Miclase->SSRMS.theta4,{0,0,0});       //b4
                Miclase->SSRMS.THList[8]=Miclase->SSRMS.THz;

                break;


            case 'J':

                Miclase->SSRMS.theta5=Miclase->SSRMS.theta5+dtheta;
                Miclase->SSRMS.AplicarTHz(   Miclase->SSRMS.theta5, {0,0,3.0});     //b4
                Miclase->SSRMS.THList[10]=Miclase->SSRMS.THz;

                break;
            case 'K':

                Miclase->SSRMS.theta5=Miclase->SSRMS.theta5-dtheta;
                Miclase->SSRMS.AplicarTHz(   Miclase->SSRMS.theta5,{0,0,3.0});       //b4
                Miclase->SSRMS.THList[10]=Miclase->SSRMS.THz;

                break;

   case 97:


 Miclase->SSRMS.t=Miclase->SSRMS.t+0.1;
  Miclase->SSRMS.parametrica();
 Miclase->SSRMS.PrepararNewtonRapshon();

                break;

 case 99:


 Miclase->SSRMS.t=Miclase->SSRMS.t-0.1;
  Miclase->SSRMS.parametrica();
 Miclase->SSRMS.PrepararNewtonRapshon();

                break;



                ///Camara/


                case 'A':
                Miclase->thetaCamera=Miclase->thetaCamera+0.05;
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT );
                break;
                  case 'D':
                Miclase->thetaCamera=Miclase->thetaCamera-0.05;
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT );
                break;

                case 'W':
                Miclase->phiCamera=Miclase->phiCamera+0.05;
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT );
                break;
                  case 'S':
                Miclase->phiCamera=Miclase->phiCamera-0.05;
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT );
                break;
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}


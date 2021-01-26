#include <windows.h>
#include <gl/gl.h>

#pragma comment(lib, "opengl32.lib")

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

float vertex[] = { -1, -1,1, 1,-1,1, 1,1,1, -1,1,1 };
float normal[] = { -1,-1,3,   1,-1,3,   1,1,3,   -1,-1,3 };
float normalOnPoints[] = {-1,-1,1,   1,-1,1,   1,1,1,   -1,1,1};


void DrawBlue()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glNormalPointer(GL_FLOAT, 0, normalOnPoints);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawRed()
{
    glEnable(GL_NORMALIZE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glNormalPointer(GL_FLOAT, 0, normal);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawGreen()
{
    glNormal3f(0, 0, 1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawBlueCube()
{
    glPushMatrix();
    glScalef(0.1, 0.1, 0.1);
    DrawBlue();
    glRotatef(90, 1, 0, 0);
    DrawBlue();
    glRotatef(90, 1, 0, 0);
    DrawBlue();
    glRotatef(90, 1, 0, 0);
    DrawBlue();
    glRotatef(90, 0, 1, 0);
    DrawBlue();
    glRotatef(180, 0, 1, 0);
    DrawBlue();
    glPopMatrix();
}

void DrawRedCube()
{
    glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        DrawRed();
        glRotatef(90, 1, 0, 0);
        DrawRed();
        glRotatef(90, 1, 0, 0);
        DrawRed();
        glRotatef(90, 1, 0, 0);
        DrawRed();
        glRotatef(90, 0, 1, 0);
        DrawRed();
        glRotatef(180, 0, 1, 0);
        DrawRed();
    glPopMatrix();
}

void DrawGreenCube()
{
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    DrawGreen();
    glRotatef(90, 1, 0, 0);
    DrawGreen();
    glRotatef(90, 1, 0, 0);
    DrawGreen();
    glRotatef(90, 1, 0, 0);
    DrawGreen();
    glRotatef(90, 0, 1, 0);
    DrawGreen();
    glRotatef(180, 0, 1, 0);
    DrawGreen();
    glPopMatrix();
}


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
    float theta = 0.0f;

    /* регистрирует класс окна */
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


    if (!RegisterClassEx(&wcex))
        return 0;

    /* создает основное окно */
    hwnd = CreateWindowEx(0,
        "GLSample",
        "OpenGL Sample",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        600,
        600,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hwnd, nCmdShow);

    EnableOpenGL(hwnd, &hDC, &hRC);     //включает OpenGL

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.2, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_COLOR_MATERIAL);

    while (!bQuit)      //основной цикл программы
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
            /* код анимации OpenGL  */
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //синий куб
            glPushMatrix();

                float position3[] = { 1,0,0,0 };
                glLightfv(GL_LIGHT2, GL_POSITION, position3);
                glColor3f(1, 1, 1);


                glPushMatrix();
                    glRotatef(-60, 1, 0, 0);
                    glRotatef(33, 0, 0, 1);
                    glTranslatef(3, 3, -2);

                    glRotatef(theta, 0, 1, 0);
                    glColor3f(0, 0, 1);
                    DrawBlueCube();
                glPopMatrix();

            glPopMatrix();

             //красный куб
            glPushMatrix();

            float position2[] = { 0,1,0,0 };
            glLightfv(GL_LIGHT1, GL_POSITION, position2);
            glColor3f(1, 1, 1);

            glPushMatrix();
            glRotatef(-60, 1, 0, 0);
            glRotatef(33, 0, 0, 1);
            glTranslatef(2, 3, -2);

            glRotatef(theta, 0, 1, 0);
            glColor3f(1, 0, 0);
            DrawRedCube();
            glPopMatrix();

            glPopMatrix();

                //зеленый куб
            glPushMatrix();

            float position1[] = { 0,0,1,0 };
            glLightfv(GL_LIGHT0, GL_POSITION, position1);
            glColor3f(1, 1, 1);

                glPushMatrix();
                    glRotatef(-60, 1, 0, 0);
                    glRotatef(33, 0, 0, 1);
                    glTranslatef(1, 3, -2);

                    glRotatef(theta, 0, 1, 0);
                    glColor3f(0, 1, 0);
                    DrawGreenCube();
                glPopMatrix();

            glPopMatrix();

            SwapBuffers(hDC);

            theta += 1.0f;
            Sleep(1);
        }
    }

    DisableOpenGL(hwnd, hDC, hRC);      //выключает OpenGL

    DestroyWindow(hwnd);        //явно закрывает окно

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
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

    *hDC = GetDC(hwnd);     //get the device context (DC)

    ZeroMemory(&pfd, sizeof(pfd));      //set the pixel format for the DC

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

    *hRC = wglCreateContext(*hDC);      //create and enable the render context (RC)

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

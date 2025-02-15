#include <windows.h>
#include <gl/gl.h>

#pragma comment(lib, "opengl32.lib")

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hwnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	BOOL bQuit = FALSE;
	float theta = 0.0f;

	/* ðåãèñòðèðóåò êëàññ îêíà */
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
	wcex.lpszClassName = L"GLSample";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


	if (!RegisterClassEx(&wcex))
		return 0;

	/* ñîçäàåò îñíîâíîå îêíî */
	hwnd = CreateWindowEx(0,
		L"GLSample",
		L"OpenGL Sample",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		720,
		480,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);

	EnableOpenGL(hwnd, &hDC, &hRC);     //âêëþ÷àåò OpenGL

	while (!bQuit)      //îñíîâíîé öèêë ïðîãðàììû
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
			/* êîä àíèìàöèè OpenGL */

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glPushMatrix();
			glRotatef(theta, 1.0f, 1.0f, 0.0f);
			//                y     x     z
			glBegin(GL_TRIANGLES);

			glColor3f(0.4f, 0.0f, 0.0f);        //êðàñíûé öâåò
			glVertex3f(0.0f, 0.4f, 0.0f);       //âåðõíÿÿ òî÷êà òðåóãîëüíèêà íà ïåðåäíåé ñòîðîíå
			glColor3f(0.4f, 0.0f, 0.0f);
			glVertex3f(-0.4f, -0.4f, 0.4f);     //ëåâàÿ òî÷êà
			glColor3f(0.4f, 0.0f, 0.0f);
			glVertex3f(0.4f, -0.4f, 0.4f);      //ïðàâàÿ òî÷êà

			glColor3f(0.0f, 0.0f, 0.4f);        //ñèíèé öâåò
			glVertex3f(0.0f, 0.4f, 0.0f);       //âåðõíÿÿ òî÷êà òðåóãîëüíèêà íà ïðàâîé ñòîðîíå
			glColor3f(0.0f, 0.0f, 0.4f);
			glVertex3f(0.4f, -0.4f, 0.4f);      //ëåâàÿ òî÷êà
			glColor3f(0.0f, 0.0f, 0.4f);
			glVertex3f(0.4f, -0.4f, -0.4f);     //ïðàâàÿ òî÷êà

			glColor3f(0.0f, 0.4f, 0.0f);        //çåëåíûé öâåò
			glVertex3f(0.0f, 0.4f, 0.0f);       //íèç òðåóãîëüíèêà íà çàäíåé ñòîðîíå
			glColor3f(0.0f, 0.4f, 0.0f);
			glVertex3f(0.4f, -0.4f, -0.4f);     //ëåâàÿ òî÷êà
			glColor3f(0.0f, 0.4f, 0.0f);
			glVertex3f(-0.4f, -0.4f, -0.4f);        //ïðàâàÿ òî÷êà

			glColor3f(0.4f, 0.0f, 0.0f);        //êðàñíûé öâåò
			glVertex3f(0.0f, 0.4f, 0.0f);       //âåðõíÿÿ òî÷êà òðåóãîëüíèêà íà ëåâîé ñòîðîíå
			glColor3f(0.0f, 0.0f, 0.4f);        //ñèíèé öâåò
			glVertex3f(-0.4f, -0.4f, -0.4f);        //ëåâàÿ òî÷êà
			glColor3f(0.0f, 0.4f, 0.0f);        //çåëåíûé öâåò
			glVertex3f(-0.4f, -0.4f, 0.4f);     //ïðàâàÿ òî÷êà

			glEnd();

			glPopMatrix();

			SwapBuffers(hDC);

			theta += 0.3f;
			Sleep(1);
		}
	}

	DisableOpenGL(hwnd, hDC, hRC);      //çàêðûâàåò OpenGL

	DestroyWindow(hwnd);        //ÿâíî çàêðûâàåò îêíî

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

	*hDC = GetDC(hwnd);     //get the device context (DC

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

﻿#include "iostream"
#include "framework.h"
#include "rocket.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
int cent(int z);
int size(int z);
void multMutr(double matr[3][3]);
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного 
const int qPoints = 11;
double myCoord [qPoints][3] = { {240,20,1},{260,60,1},{260,200,1}, // Матрица координат объекта
                                {220,200,1}, {220,60,1},{200,140,1},
                                {200,240,1} ,{220,180,1},{260,180,1},
                                {280,140,1},{280,240,1} };

double back[qPoints][3] = { {240,20,1},{260,60,1},{260,200,1}, // Матрица начальных координат
                                {220,200,1}, {220,60,1},{200,140,1},
                                {200,240,1} ,{220,180,1},{260,180,1},
                                {280,140,1},{280,240,1} };

double mReduse[3][3] = { {0.25,0,0},{0,0.25,0},{0,0,1} }; // Матрица уменьшение объекта
double mReflect[3][3] = { {1,0,0},{0,-1,0},{0,(cent(1)*2),1} }; // Матрица отражения относительно оси X
double mtanf[3][3] = { {1,0,0},{0,1,0},{-size(0),size(1)*2,1}}; // Матрица переноса

void origin() //Функция возвращения к оригинальным координатам
{
    for (int i = 0; i < qPoints; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            myCoord[i][j] = back[i][j];
        }
    }

}
//----------------------------------------------------------------------------------------------------------------------------------------------
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//----------------------------------------------------------------------------------------------------------------------------------------------


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ROCKET, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROCKET));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//----------------------------------------------------------------------------------------------------------------------------------------------


//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROCKET));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ROCKET);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_MOVE:    // Перемещение объекта   
                mtanf[2][0] = -size(0);
                mtanf[2][1] = size(1)*2;
                multMutr(mtanf);
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
            case IDM_SCALE:  // Уменьшение объекта в 4 раза   
                multMutr(mReduse);
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
            case IDM_ORIGIN: // Возвращения к оригинальным координатам 
                origin();
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
            case IDM_MIRROR: // Отражение относительно оси X
                mReflect[2][1] = cent(1)*2;
                multMutr(mReflect);
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:

        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);                    //Построение объекта
            MoveToEx(hdc, myCoord[0][0], myCoord[0][1], 0);
            LineTo(hdc, myCoord[1][0], myCoord[1][1]);
            LineTo(hdc, myCoord[2][0], myCoord[2][1]);
            LineTo(hdc, myCoord[3][0], myCoord[3][1]);
            LineTo(hdc, myCoord[4][0], myCoord[4][1]);
            LineTo(hdc, myCoord[0][0], myCoord[0][1]);
            MoveToEx(hdc, myCoord[5][0], myCoord[5][1], 0);
            LineTo(hdc, myCoord[6][0], myCoord[6][1]);
            LineTo(hdc, myCoord[7][0], myCoord[7][1]);
            LineTo(hdc, myCoord[5][0], myCoord[5][1]);
            MoveToEx(hdc, myCoord[8][0], myCoord[8][1], 0);
            LineTo(hdc, myCoord[9][0], myCoord[9][1]);
            LineTo(hdc, myCoord[10][0], myCoord[10][1]);
            LineTo(hdc, myCoord[8][0], myCoord[8][1]);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
void multMutr(double matr[3][3]) {                       //Функция перемножения матриц
    double d[11][3];
    for (int row = 0; row < qPoints; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            d[row][col] = 0;
            for (int inner = 0; inner < 3; inner++)
            {               
                d[row][col] += myCoord[row][inner] * matr[inner][col];
            }                                       
        }        
    } 
    for (int i = 0; i < qPoints; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            myCoord[i][j] = d[i][j];
        }
    }
}

int cent(int z) {                                      //Функция нахождения цента объекта

    int max, min;
    max=min = myCoord[0][z];
    
    for (int i = 0; i < qPoints; i++)
    {
        if (min> myCoord[i][z])
        {
            min = myCoord[i][z];
        } 

        if (max< myCoord[i][z])
        {
            max = myCoord[i][z];
        }
    }    
    return (max+min)/2;
}
int size(int z) {                                      //Функция нахождения длины объекта

    int max, min;
    max = min = myCoord[0][z];

    for (int i = 0; i < qPoints; i++)
    {
        if (min > myCoord[i][z])
        {
            min = myCoord[i][z];
        }

        if (max < myCoord[i][z])
        {
            max = myCoord[i][z];
        }
    }
    return max-min;
}
//----------------------------------------------------------------------------------------------------------------------------------------------
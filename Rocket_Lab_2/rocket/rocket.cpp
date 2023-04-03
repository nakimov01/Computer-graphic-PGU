// Computer graphic 2 lab.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Computer graphic 2 lab.h"

#define MAX_LOADSTRING 100
#define RESTART 21
#define UP 123
#define DOWN 223

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hwndButton, hwndButtonUp, hwndButtonDown;  // кнопка
void Addcontrol(HWND hWnd);                     // создание кнопок
int pX = 50, pY = 150;                          // позиция по X и Y
int i = 0, j = 1;                               // кол-во повторений циклов

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_COMPUTERGRAPHIC2LAB, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COMPUTERGRAPHIC2LAB));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COMPUTERGRAPHIC2LAB));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_COMPUTERGRAPHIC2LAB);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

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
    case WM_CREATE:
        Addcontrol(hWnd);
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case RESTART: // старт анимации
                j = 21;
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
            case UP: // перемещение вверх
                pY -= 20;
                j = 1;
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
            case DOWN: // перемещение вниз
                pY += 20;
                j = 1;
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
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            
            HBITMAP bmw;
            HDC memdc;
            LPCWSTR path[4] = { L"resource/house.bmp", L"resource/house1.bmp", L"resource/house2.bmp", L"resource/house3.bmp" }; // названия спрайтов
            memdc = CreateCompatibleDC(hdc);

            bmw = (HBITMAP)LoadImage(NULL, L"resource/sity.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            SelectObject(memdc, bmw);
            BitBlt(hdc, 400, 200, 1000, 250, memdc, 0, 0, SRCCOPY);

            bmw = (HBITMAP)LoadImage(NULL, L"resource/sun.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            SelectObject(memdc, bmw);
            BitBlt(hdc, 900, 20, 100, 100, memdc, 0, 0, SRCCOPY);
            bmw = (HBITMAP)LoadImage(NULL, path[1], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            SelectObject(memdc, bmw);
            while (j)
            {
                bmw = (HBITMAP)LoadImage(NULL, path[i++], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                SelectObject(memdc, bmw);
                BitBlt(hdc, pX, pY, 200, 300, memdc, 0, 0, SRCINVERT);
                Sleep(250);
                BitBlt(hdc, pX, pY, 200, 300, memdc, 0, 0, SRCINVERT);
                i = i % 4;
                j--;
            }
            i = 0;
            BitBlt(hdc, pX, pY, 200, 300, memdc, 0, 0, SRCINVERT);
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

void Addcontrol(HWND hWnd) {
    hwndButton = CreateWindowW(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Start",      // Button text 
        WS_VISIBLE | WS_CHILD,  // Styles 
        300,         // x position 
        100,         // y position 
        100,        // Button width
        25,        // Button height
        hWnd,     // Parent window
        (HMENU)RESTART,       // No menu.
        NULL,
        NULL);

    hwndButtonUp = CreateWindowW(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Up",      // Button text 
        WS_VISIBLE | WS_CHILD,  // Styles 
        300,         // x position 
        130,         // y position 
        100,        // Button width
        25,        // Button height
        hWnd,     // Parent window
        (HMENU)UP,       // No menu.
        NULL,
        NULL);

    hwndButtonDown = CreateWindowW(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Down",      // Button text 
        WS_VISIBLE | WS_CHILD,  // Styles 
        300,         // x position 
        160,         // y position 
        100,        // Button width
        25,        // Button height
        hWnd,     // Parent window
        (HMENU)DOWN,       // No menu.
        NULL,
        NULL);
}
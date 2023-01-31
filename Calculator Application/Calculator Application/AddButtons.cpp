#include "AddButtons.h"

void AddButtons::button(HWND hWnd)
{
    DWORD dwStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON;
    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    //HWND test = CreateWindow(L"Static", L"", WS_CHILD | WS_VISIBLE| WS_BORDER, 0, 100, 684, 540, hWnd, NULL, NULL, NULL); -> total area the buttons are allowed to take up
    //15 is the space inbetween the buttons
    //each button can be 72.5 units tall and each button can be 96.5 units wide


    //first row
    HWND h_Left_Parentheses = CreateWindow(L"BUTTON", L"(", dwStyle, 15, 115, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND h_Right_Parantheses = CreateWindow(L"BUTTON", L")", dwStyle, 126.5, 115, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND h_Left_Parenthes = CreateWindow(L"BUTTON", L"", dwStyle, 238, 115, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND h_Left_Parentses = CreateWindow(L"BUTTON", L"", dwStyle, 349.5, 115, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND h_Left_Pareheses = CreateWindow(L"BUTTON", L"History", dwStyle, 461, 115, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND h_Left_Pantheses = CreateWindow(L"BUTTON", L"Clear", dwStyle, 572.5, 115, 96.5, 72.5, hWnd, NULL, hInstance, NULL);

    //second row
    HWND h_Left_Pare = CreateWindow(L"BUTTON", L"", dwStyle, 15, 202.5, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND h_Left_Parees = CreateWindow(L"BUTTON", L"", dwStyle, 126.5, 202.5, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND h_Left_Parenthe = CreateWindow(L"BUTTON", L"", dwStyle, 238, 202.5, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND h_Left_Parentss = CreateWindow(L"BUTTON", L"", dwStyle, 349.5, 202.5, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND h_Left_Parehees = CreateWindow(L"BUTTON", L"", dwStyle, 461, 202.5, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND h_Left_Panthses = CreateWindow(L"BUTTON", L"", dwStyle, 572.5, 202.2, 96.5, 72.5, hWnd, NULL, hInstance, NULL);

    //third row
    HWND a = CreateWindow(L"BUTTON", L"", dwStyle, 15, 290, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND b = CreateWindow(L"BUTTON", L"", dwStyle, 126.5, 290, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND c = CreateWindow(L"BUTTON", L"", dwStyle, 238, 290, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND d = CreateWindow(L"BUTTON", L"", dwStyle, 349.5, 290, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND e = CreateWindow(L"BUTTON", L"", dwStyle, 461, 290, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND f = CreateWindow(L"BUTTON", L"", dwStyle, 572.5, 290, 96.5, 72.5, hWnd, NULL, hInstance, NULL);

    //fourth row
    HWND g = CreateWindow(L"BUTTON", L"", dwStyle, 15, 377.5, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND h = CreateWindow(L"BUTTON", L"", dwStyle, 126.5, 377.5, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND i = CreateWindow(L"BUTTON", L"", dwStyle, 238, 377.5, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND j = CreateWindow(L"BUTTON", L"", dwStyle, 349.5, 377.5, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND k = CreateWindow(L"BUTTON", L"", dwStyle, 461, 377.5, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND l = CreateWindow(L"BUTTON", L"", dwStyle, 572.5, 377.5, 96.5, 72.5, hWnd, NULL, hInstance, NULL);

    //fifth row
    HWND m = CreateWindow(L"BUTTON", L"", dwStyle, 15, 465, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND n = CreateWindow(L"BUTTON", L"", dwStyle, 126.5, 465, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND o = CreateWindow(L"BUTTON", L"", dwStyle, 238, 465, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND p = CreateWindow(L"BUTTON", L"", dwStyle, 349.5, 465, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND q = CreateWindow(L"BUTTON", L"", dwStyle, 461, 465, 96.5, 72.5, hWnd, NULL, hInstance, NULL);
    HWND r = CreateWindow(L"BUTTON", L"", dwStyle, 572.5, 465, 96.5, 72.5, hWnd, NULL, hInstance, NULL);

    //sixth row
    HWND s = CreateWindow(L"BUTTON", L"", dwStyle, 15, 552.5, 152.25, 72.5, hWnd, NULL, hInstance, NULL);
    HWND t = CreateWindow(L"BUTTON", L"", dwStyle, 182.25, 552.5, 152.25, 72.5, hWnd, NULL, hInstance, NULL);
    HWND u = CreateWindow(L"BUTTON", L"", dwStyle, 349.5, 552.5, 152.25, 72.5, hWnd, NULL, hInstance, NULL);
    HWND v = CreateWindow(L"BUTTON", L"", dwStyle, 516.75, 552.5, 152.25, 72.5, hWnd, NULL, hInstance, NULL);
}
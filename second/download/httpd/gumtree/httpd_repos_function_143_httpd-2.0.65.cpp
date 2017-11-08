HWND CreateMainWindow(HINSTANCE hInstance)
{
    HWND hWnd = NULL;
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = (WNDPROC)WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon   = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_APSRVMON),
                                    IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
    wcex.hCursor        = g_hCursorArrow;
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = g_szWindowClass;
    wcex.hIconSm = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_APSRVMON),
                                    IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);

    if (RegisterClassEx(&wcex)) {
        hWnd = CreateWindow(g_szWindowClass, g_szTitle,
                            0, 0, 0, 0, 0,
                            NULL, NULL, hInstance, NULL);
    }
    return hWnd;
}
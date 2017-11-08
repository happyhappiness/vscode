LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
    if (message == g_bUiTaskbarCreated)
    {
        /* restore the tray icon on shell restart */
        ShowNotifyIcon(hWnd, NIM_ADD);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    switch (message)
    {
    case WM_CREATE:
        GetApacheServicesStatus();
        ShowNotifyIcon(hWnd, NIM_ADD);
        SetTimer(hWnd, WM_TIMER_REFRESH, REFRESH_TIME, NULL);
        SetTimer(hWnd, WM_TIMER_RESCAN,  RESCAN_TIME, NULL);
        break;

    case WM_TIMER:
        switch (wParam)
        {
        case WM_TIMER_RESCAN:
        {
            int nPrev = 0, nNew = 0;
            EnterCriticalSection(&g_stcSection);
            if (FindRunningServices() || g_bRescanServices)
            {
                ShowNotifyIcon(hWnd, NIM_MODIFY);
                if (g_hwndServiceDlg)
                    PostMessage(g_hwndServiceDlg, WM_UPDATEMESSAGE, 0, 0);
            }
            /* check if services list changed */
            while (g_stServices[nPrev].szServiceName != NULL)
                ++nPrev;
            GetApacheServicesStatus();
            while (g_stServices[nNew].szServiceName != NULL)
                ++nNew;
            if (nPrev != nNew)
            {
                ShowNotifyIcon(hWnd, NIM_MODIFY);
                if (g_hwndServiceDlg) {
                    PostMessage(g_hwndServiceDlg, WM_UPDATEMESSAGE, 0, 0);
                }
            }
            LeaveCriticalSection(&g_stcSection);
            break;
        }

        case WM_TIMER_REFRESH:
        {
            int nPrev = 0, nNew = 0;
            EnterCriticalSection(&g_stcSection);
            if (g_bRescanServices)
            {
                GetApacheServicesStatus();
                ShowNotifyIcon(hWnd, NIM_MODIFY);
                if (g_hwndServiceDlg) {
                    PostMessage(g_hwndServiceDlg, WM_UPDATEMESSAGE, 0, 0);
                }
            }
            else if (FindRunningServices())
            {
                ShowNotifyIcon(hWnd, NIM_MODIFY);
                if (g_hwndServiceDlg) {
                    PostMessage(g_hwndServiceDlg, WM_UPDATEMESSAGE, 0, 0);
                }
            }
            LeaveCriticalSection(&g_stcSection);
            break;
        }
        }
        break;

    case WM_QUIT:
        ShowNotifyIcon(hWnd, NIM_DELETE);
        break;

    case WM_TRAYMESSAGE:
        switch (lParam)
        {
        case WM_LBUTTONDBLCLK:
            if (!g_bDlgServiceOn)
            {
                g_bDlgServiceOn = TRUE;
                DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_DLGSERVICES),
                          hWnd, (DLGPROC)ServiceDlgProc);
                g_bDlgServiceOn = FALSE;
                g_hwndServiceDlg = NULL;
            }
            else if (IsWindow(g_hwndServiceDlg))
            {
                /* Dirty hack to bring the window to the foreground */
                SetWindowPos(g_hwndServiceDlg, HWND_TOPMOST, 0, 0, 0, 0,
                             SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);
                SetWindowPos(g_hwndServiceDlg, HWND_NOTOPMOST, 0, 0, 0, 0,
                             SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);
                SetFocus(g_hwndServiceDlg);
            }
            break;

        case WM_LBUTTONUP:
            ShowTryServicesMenu(hWnd);
            break;

        case WM_RBUTTONUP:
            ShowTryPopupMenu(hWnd);
            break;
        }
        break;

    case WM_COMMAND:
        if ((LOWORD(wParam) & IDM_SM_START) == IDM_SM_START)
        {
            ApacheManageService(g_stServices[LOWORD(wParam)
                                           - IDM_SM_START].szServiceName,
                                g_stServices[LOWORD(wParam)
                                           - IDM_SM_START].szImagePath,
                                g_stServices[LOWORD(wParam)
                                           - IDM_SM_START].szComputerName,
                                SERVICE_CONTROL_CONTINUE);
      
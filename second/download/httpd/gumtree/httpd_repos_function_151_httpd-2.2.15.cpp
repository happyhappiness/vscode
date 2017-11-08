LRESULT CALLBACK ServiceDlgProc(HWND hDlg, UINT message,
                                WPARAM wParam, LPARAM lParam)
{
    TCHAR szBuf[MAX_PATH];
    HWND hListBox;
    static HWND hStatusBar;
    TEXTMETRIC tm;
    int i, y;
    HDC hdcMem;
    RECT rcBitmap;
    LRESULT nItem;
    LPMEASUREITEMSTRUCT lpmis;
    LPDRAWITEMSTRUCT lpdis;

    memset(szBuf, 0, sizeof(szBuf));
    switch (message)
    {
    case WM_INITDIALOG:
        ShowWindow(hDlg, SW_HIDE);
        g_hwndServiceDlg = hDlg;
        SetWindowText(hDlg, g_szTitle);
        Button_Enable(GetDlgItem(hDlg, IDC_SSTART), FALSE);
        Button_Enable(GetDlgItem(hDlg, IDC_SSTOP), FALSE);
        Button_Enable(GetDlgItem(hDlg, IDC_SRESTART), FALSE);
        Button_Enable(GetDlgItem(hDlg, IDC_SDISCONN), FALSE);
        SetWindowText(GetDlgItem(hDlg, IDC_SSTART),
                      g_lpMsg[IDS_MSG_SSTART - IDS_MSG_FIRST]);
        SetWindowText(GetDlgItem(hDlg, IDC_SSTOP),
                      g_lpMsg[IDS_MSG_SSTOP - IDS_MSG_FIRST]);
        SetWindowText(GetDlgItem(hDlg, IDC_SRESTART),
                      g_lpMsg[IDS_MSG_SRESTART - IDS_MSG_FIRST]);
        SetWindowText(GetDlgItem(hDlg, IDC_SMANAGER),
                      g_lpMsg[IDS_MSG_SERVICES - IDS_MSG_FIRST]);
        SetWindowText(GetDlgItem(hDlg, IDC_SCONNECT),
                      g_lpMsg[IDS_MSG_CONNECT - IDS_MSG_FIRST]);
        SetWindowText(GetDlgItem(hDlg, IDC_SEXIT),
                      g_lpMsg[IDS_MSG_MNUEXIT - IDS_MSG_FIRST]);
        if (g_dwOSVersion < OS_VERSION_WINNT)
        {
            ShowWindow(GetDlgItem(hDlg, IDC_SMANAGER), SW_HIDE);
            ShowWindow(GetDlgItem(hDlg, IDC_SCONNECT), SW_HIDE);
            ShowWindow(GetDlgItem(hDlg, IDC_SDISCONN), SW_HIDE);
        }
        hListBox = GetDlgItem(hDlg, IDL_SERVICES);
        g_hwndStdoutList = GetDlgItem(hDlg, IDL_STDOUT);
        hStatusBar = CreateStatusWindow(0x0800 /* SBT_TOOLTIPS */
                                      | WS_CHILD | WS_VISIBLE,
                                        _T(""), hDlg, IDC_STATBAR);
        if (GetApacheServicesStatus())
        {
            i = 0;
            while (g_stServices[i].szServiceName != NULL)
            {
                addListBoxItem(hListBox, g_stServices[i].szDisplayName,
                               g_stServices[i].dwPid == 0 ? g_hBmpStop
                                                          : g_hBmpStart);
                ++i;
            }
        }
        CenterWindow(hDlg);
        ShowWindow(hDlg, SW_SHOW);
        SetFocus(hListBox);
        SendMessage(hListBox, LB_SETCURSEL, 0, 0);
        return TRUE;
        break;

    case WM_MANAGEMESSAGE:
        ApacheManageService(g_stServices[LOWORD(wParam)].szServiceName,
                    g_stServices[LOWORD(wParam)].szImagePath,
                    g_stServices[LOWORD(wParam)].szComputerName,
                    LOWORD(lParam));

        return TRUE;
        break;

    case WM_UPDATEMESSAGE:
        hListBox = GetDlgItem(hDlg, IDL_SERVICES);
        SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
        SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)_T(""));
        Button_Enable(GetDlgItem(hDlg, IDC_SSTART), FALSE);
        Button_Enable(GetDlgItem(hDlg, IDC_SSTOP), FALSE);
        Button_Enable(GetDlgItem(hDlg, IDC_SRESTART), FALSE);
        Button_Enable(GetDlgItem(hDlg, IDC_SDISCONN), FALSE);
        i = 0;
        while (g_stServices[i].szServiceName != NULL)
        {
            addListBoxItem(hListBox, g_stServices[i].szDisplayName,
                g_stServices[i].dwPid == 0 ? g_hBmpStop : g_hBmpStart);
            ++i;
        }
        SendMessage(hListBox, LB_SETCURSEL, 0, 0);
        /* Dirty hack to bring the window to the foreground */
        SetWindowPos(hDlg, HWND_TOPMOST, 0, 0, 0, 0,
                                SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);
        SetWindowPos(hDlg, HWND_NOTOPMOST, 0, 0, 0, 0,
                                SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);
        SetFocus(hListBox);
        return TRUE;
        break;

    case WM_MEASUREITEM:
        lpmis = (LPMEASUREITEMSTRUCT) lParam;
        lpmis->itemHeight = YBITMAP;
        return TRUE;

    case WM_SETCURSOR:
        if (g_bConsoleRun) {
            SetCursor(g_hCursorHourglass);
        }
        else {
            SetCursor(g_hCursorArrow);
        }
        return TRUE;

    case WM_DRAWITEM:
        lpdis = (LPDRAWITEMSTRUCT) lParam;
        if (lpdis->itemID == -1) {
            break;
        }
        switch (lpdis->itemAction)
        {
        case ODA_SELECT:
        case ODA_DRAWENTIRE:
            g_hBmpPicture = (HBITMAP)SendMessage(lpdis->hwndItem,
                                                 LB_GETITEMDATA,
                                                 lpdis->itemID, (LPARAM) 0);

            hdcMem = CreateCompatibleDC(lpdis->hDC);
            g_hBmpOld = SelectObject(hdcMem, g_hBmpPicture);

            BitBlt(lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top,
                   lpdis->rcItem.right - lpdis->rcItem.left,
                   lpdis->rcItem.bottom - lpdis->rcItem.top,
                   hdcMem, 0, 0, SRCCOPY);
            SendMessage(lpdis->hwndItem, LB_GETTEXT,
                        lpdis->itemID, (LPARAM) szBuf);

            GetTextMetrics(lpdis->hDC, &tm);
            y = (lpdis->rcItem.bottom + lpdis->rcItem.top - tm.tmHeight) / 2;

            SelectObject(hdcMem, g_hBmpOld);
            DeleteDC(hdcMem);

            rcBitmap.left = lpdis->rcItem.left + XBITMAP + 2;
            rcBitmap.top = lpdis->rcItem.top;
            rcBitmap.right = lpdis->rcItem.right;
            rcBitmap.bottom = lpdis->rcItem.top + YBITMAP;

            if (lpdis->itemState & ODS_SELECTED)
            {
                if (g_hBmpPicture == g_hBmpStop)
                {
                    Button_Enable(GetDlgItem(hDlg, IDC_SSTART), TRUE);
                    Button_Enable(GetDlgItem(hDlg, IDC_SSTOP), FALSE);
                    Button_Enable(GetDlgItem(hDlg, IDC_SRESTART), FALSE);
                }
                else if (g_hBmpPicture == g_hBmpStart)
                {
                    Button_Enable(GetDlgItem(hDlg, IDC_SSTART), FALSE);
                    Button_Enable(GetDlgItem(hDlg, IDC_SSTOP), TRUE);
                    Button_Enable(GetDlgItem(hDlg, IDC_SRESTART), TRUE);
                }
                else {
                    Button_Enable(GetDlgItem(hDlg, IDC_SSTART), FALSE);
                    Button_Enable(GetDlgItem(hDlg, IDC_SSTOP), FALSE);
                    Button_Enable(GetDlgItem(hDlg, IDC_SRESTART), FALSE);
                }
                if (_tcscmp(g_stServices[lpdis->itemID].szComputerName,
                           g_szLocalHost) == 0) {
                    Button_Enable(GetDlgItem(hDlg, IDC_SDISCONN), FALSE);
                }
                else {
                    Button_Enable(GetDlgItem(hDlg, IDC_SDISCONN), TRUE);
                }

                if (g_stServices[lpdis->itemID].szDescription) {
                    SendMessage(hStatusBar, SB_SETTEXT, 0,
                            (LPARAM)g_stServices[lpdis->itemID].szDescription);
                }
                else {
                    SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)_T(""));
                }
                SetTextColor(lpdis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
                SetBkColor(lpdis->hDC, GetSysColor(COLOR_HIGHLIGHT));
                FillRect(lpdis->hDC, &rcBitmap, (HBRUSH)(COLOR_HIGHLIGHTTEXT));
            }
            else
            {
               SetTextColor(lpdis->hDC, GetSysColor(COLOR_MENUTEXT));
               SetBkColor(lpdis->hDC, GetSysColor(COLOR_WINDOW));
               FillRect(lpdis->hDC, &rcBitmap, (HBRUSH)(COLOR_WINDOW+1));
            }
            TextOut(lpdis->hDC, XBITMAP + 6, y, szBuf, (int)_tcslen(szBuf));
            break;

        case ODA_FOCUS:
            break;
        }
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDL_SERVICES:
            switch (HIWORD(wParam))
            {
            case LBN_DBLCLK:
                /* if started then stop, if stopped then start */
   
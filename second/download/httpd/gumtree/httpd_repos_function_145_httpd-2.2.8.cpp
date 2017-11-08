LRESULT CALLBACK ConnectDlgProc(HWND hDlg, UINT message,
                                WPARAM wParam, LPARAM lParam)
{
    CHAR szCmp[MAX_COMPUTERNAME_LENGTH+4];
    switch (message)
    {
    case WM_INITDIALOG:
        ShowWindow(hDlg, SW_HIDE);
        g_hwndConnectDlg = hDlg;
        CenterWindow(hDlg);
        ShowWindow(hDlg, SW_SHOW);
        SetFocus(GetDlgItem(hDlg, IDC_COMPUTER));
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            memset(szCmp, 0, MAX_COMPUTERNAME_LENGTH+4);
            strcpy(szCmp, "\\\\");
            SendMessage(GetDlgItem(hDlg, IDC_COMPUTER), WM_GETTEXT,
                        (WPARAM) MAX_COMPUTERNAME_LENGTH,
                        (LPARAM) szCmp+2);

            strupr(szCmp);
            if (strlen(szCmp) < 3) {
                EndDialog(hDlg, TRUE);
                return TRUE;
            }
            am_ConnectComputer(szCmp);
            SendMessage(g_hwndMain, WM_TIMER, WM_TIMER_RESCAN, 0);

        case IDCANCEL:
            EndDialog(hDlg, TRUE);
            return TRUE;

        case IDC_LBROWSE:
        {
            BROWSEINFO bi;
            ITEMIDLIST *il;
            LPMALLOC pMalloc;
            memset(&bi, 0, sizeof(BROWSEINFO));
            SHGetSpecialFolderLocation(hDlg, CSIDL_NETWORK, &il);

            bi.lpszTitle      = "ApacheMonitor :\nSelect Network Computer!";
            bi.pszDisplayName = szCmp;
            bi.hwndOwner =      hDlg;
            bi.ulFlags =        BIF_BROWSEFORCOMPUTER;
            bi.lpfn =           NULL;
            bi.lParam =         0;
            bi.iImage =         0;
            bi.pidlRoot =       il;

            if (SHBrowseForFolder(&bi) != NULL) {
                SendMessage(GetDlgItem(hDlg, IDC_COMPUTER),
                            WM_SETTEXT,
                            (WPARAM) NULL, (LPARAM) szCmp);
            }
            if (SHGetMalloc(&pMalloc)) {
                pMalloc->lpVtbl->Free(pMalloc, il);
                pMalloc->lpVtbl->Release(pMalloc);
            }
            return TRUE;
        }
        }
        break;

    case WM_QUIT:
    case WM_CLOSE:
        EndDialog(hDlg, TRUE);
        return TRUE;

    default:
        return FALSE;
    }
    return FALSE;

}
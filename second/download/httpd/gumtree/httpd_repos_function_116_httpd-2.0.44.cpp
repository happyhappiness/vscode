static VOID ShowNotifyIcon(HWND hWnd, DWORD dwMessage)
{
    NOTIFYICONDATA nid;
    int i = 0, n = 0;

    memset(&nid, 0, sizeof(nid));
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hWnd;
    nid.uID = 0xFF;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYMESSAGE;

    while (g_stServices[i].szServiceName != NULL)
    {
        if (g_stServices[i].dwPid != 0) {
            ++n;
        }
        ++i;
    }
    if (dwMessage != NIM_DELETE)
    {
        if (n) {
            nid.hIcon = g_icoRun;
        }
        else {
            nid.hIcon = g_icoStop;
        }
    }
    else {
        nid.hIcon = NULL;
    }
    if (n == i && n > 0) {
        lstrcpy(nid.szTip, g_lpMsg[IDS_MSG_RUNNINGALL - IDS_MSG_FIRST]);
    }
    else if (n) {
        sprintf(nid.szTip, g_lpMsg[IDS_MSG_RUNNING - IDS_MSG_FIRST], n, i);
    }
    else if (i) {
        sprintf(nid.szTip, g_lpMsg[IDS_MSG_RUNNINGNONE - IDS_MSG_FIRST], i);
    }
    else {
        lstrcpy(nid.szTip, g_lpMsg[IDS_MSG_NOSERVICES - IDS_MSG_FIRST]);
    }
    Shell_NotifyIcon(dwMessage, &nid);
}
static int KillAWindow(HWND appwindow)
{
    HANDLE appproc;
    DWORD procid;
    BOOL postres;

    SetLastError(0);
    GetWindowThreadProcessId(appwindow, &procid);
    if (GetLastError())
        return(2);

    appproc = OpenProcess(SYNCHRONIZE, 0, procid);
    postres = PostMessage(appwindow, WM_COMMAND, IDM_EXIT, 0);
    if (appproc && postres) {
        if (WaitForSingleObject(appproc, 10 /* seconds */ * 1000)
                == WAIT_OBJECT_0) {
            CloseHandle(appproc);
            return (0);
        }
    }
    if (appproc)
        CloseHandle(appproc);

    if ((appproc = OpenProcess(PROCESS_TERMINATE, 0, procid)) != NULL) {
        if (TerminateProcess(appproc, 0)) {
            CloseHandle(appproc);
            return (0);
        }
        CloseHandle(appproc);
    }

    /* Perhaps we were short of permissions? */
    return (2);
}
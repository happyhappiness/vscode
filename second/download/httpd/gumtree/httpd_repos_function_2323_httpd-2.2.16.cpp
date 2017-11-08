static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
                                WPARAM wParam, LPARAM lParam)
{
    WNDPROC origproc = (WNDPROC) GetProp(hwnd, origwndprop);
    if (!origproc)
        return 0;

    if (msg == WM_NCDESTROY
        || (msg == hookwndmsg && !LOWORD(wParam) && (HWND)lParam == hwnd))
    {
        if (is_subclassed) {
#ifdef DBG
            DbgPrintf("W proc %08x hwnd:%08x Subclass removed\r\n",
                      GetCurrentProcessId(), hwnd);
#endif
            if (is_service)
                RegisterWindows9xService(FALSE);
            SetWindowLong(hwnd, GWL_WNDPROC, (LONG)origproc);
            RemoveProp(hwnd, origwndprop);
            RemoveProp(hwnd, hookwndprop);
            is_subclassed = FALSE;
            //if (hmodLock)
            //    FreeLibrary(hmodLock);
            //hmodLock = NULL;
        }
    }
    else if (msg == WM_CLOSE || msg == WM_ENDSESSION
                             || msg == WM_QUERYENDSESSION)
    {
        HWND child = (HWND)GetProp(hwnd, hookwndprop);
        if (child) {
#ifdef DBG
            DbgPrintf("W proc %08x hwnd:%08x forwarded msg:%d\r\n",
                      GetCurrentProcessId(), hwnd, msg);
#endif
            return SendMessage(child, msg, wParam, lParam);
        }
    }
    return CallWindowProc(origproc, hwnd, msg, wParam, lParam);
}
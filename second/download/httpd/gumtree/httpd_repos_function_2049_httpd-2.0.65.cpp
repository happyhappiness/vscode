int HookProc(int hc, HWND *hwnd, UINT *msg, WPARAM *wParam, LPARAM *lParam)
{
    if (is_tty == -1 && *hwnd) 
    {
        char ttybuf[8];
        HWND htty;
        hwtty = *hwnd;
        while (htty = GetParent(hwtty))
            hwtty = htty;
        is_tty = (GetClassName(hwtty, ttybuf, sizeof(ttybuf)) 
                  && !strcmp(ttybuf, "tty"));
#ifdef DBG
        if (is_tty)
            DbgPrintf("H proc %08x tracking hwnd %08x\r\n", 
                      GetCurrentProcessId(), hwtty);
#endif
    }

    if (*msg == hookwndmsg && *wParam && *lParam == (LPARAM)hwtty && is_tty)
    {
        WNDPROC origproc = (WNDPROC)GetWindowLong(hwtty, GWL_WNDPROC);
        //char myname[MAX_PATH];
        //if (GetModuleFileName(hmodThis, myname, sizeof(myname)))
        //    hmodLock = LoadLibrary(myname);        
        SetProp(hwtty, origwndprop, origproc);
        SetWindowLong(hwtty, GWL_WNDPROC, (LONG)WndProc);
        is_subclassed = TRUE;
#ifdef DBG
        DbgPrintf("H proc %08x hwnd:%08x Subclassed\r\n", 
                  GetCurrentProcessId(), hwtty);
#endif
        if (LOWORD(*wParam) == 2)
            RegisterWindows9xService(TRUE);
    }

    return -1;
}
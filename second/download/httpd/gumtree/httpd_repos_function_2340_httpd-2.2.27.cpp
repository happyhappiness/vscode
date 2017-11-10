static LRESULT CALLBACK ttyConsoleCtrlWndProc(HWND hwnd, UINT msg,
                                              WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_CREATE)
    {
        tty_info *tty = (tty_info*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
        SetWindowLong(hwnd, gwltty_phandler, (LONG)tty->phandler);
        SetWindowLong(hwnd, gwltty_ttywnd, (LONG)tty->parent);
#ifdef DBG
        DbgPrintf("A proc %8.8x created %8.8x %s for tty wnd %8.8x\r\n",
                  GetCurrentProcessId(), hwnd,
                  tty->name, tty->parent);
#endif
        if (tty->parent) {
            SetProp(tty->parent, hookwndprop, hwnd);
            PostMessage(tty->parent, hookwndmsg,
                        tty->type, (LPARAM)tty->parent);
        }
        return 0;
    }
    else if (msg == WM_DESTROY)
    {
        HWND parent = (HWND)GetWindowLong(hwnd, gwltty_ttywnd);
#ifdef DBG
        DbgPrintf("A proc %8.8x destroyed %8.8x ttyConHookChild\r\n",
                  GetCurrentProcessId(), hwnd);
#endif
        if (parent) {
            RemoveProp(parent, hookwndprop);
            SendMessage(parent, hookwndmsg, 0, (LPARAM)parent);
        }
        monitor_hwnd = NULL;
    }
    else if (msg == WM_CLOSE)
    {
        PHANDLER_ROUTINE phandler =
            (PHANDLER_ROUTINE)GetWindowLong(hwnd, gwltty_phandler);
        LRESULT rv = phandler(CTRL_CLOSE_EVENT);
#ifdef DBG
        DbgPrintf("A proc %8.8x invoked CTRL_CLOSE_EVENT "
                  "returning %d\r\n",
                  GetCurrentProcessId(), rv);
#endif
        if (rv)
            return !rv;
    }
    else if ((msg == WM_QUERYENDSESSION) || (msg == WM_ENDSESSION))
    {
        if (lParam & ENDSESSION_LOGOFF)
        {
            PHANDLER_ROUTINE phandler =
                (PHANDLER_ROUTINE)GetWindowLong(hwnd, gwltty_phandler);
            LRESULT rv = phandler(CTRL_LOGOFF_EVENT);
#ifdef DBG
            DbgPrintf("A proc %8.8x invoked CTRL_LOGOFF_EVENT "
                      "returning %d\r\n",
                      GetCurrentProcessId(), rv);
#endif
            if (rv)
                return ((msg == WM_QUERYENDSESSION) ? rv : !rv);
        }
        else
        {
            PHANDLER_ROUTINE phandler =
                (PHANDLER_ROUTINE)GetWindowLong(hwnd, gwltty_phandler);
            LRESULT rv = phandler(CTRL_SHUTDOWN_EVENT);
#ifdef DBG
            DbgPrintf("A proc %8.8x invoked CTRL_SHUTDOWN_EVENT "
                      "returning %d\r\n", GetCurrentProcessId(), rv);
#endif
            if (rv)
                return ((msg == WM_QUERYENDSESSION) ? rv : !rv);
        }
    }
    return (DefWindowProc(hwnd, msg, wParam, lParam));
}
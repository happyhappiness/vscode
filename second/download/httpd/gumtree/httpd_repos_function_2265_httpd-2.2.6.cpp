static LRESULT CALLBACK monitor_service_9x_proc(HWND hWnd, UINT msg,
                                                WPARAM wParam, LPARAM lParam)
{
/* This is the WndProc procedure for our invisible window.
 * When the user shuts down the system, this window is sent
 * a signal WM_ENDSESSION. We clean up by signaling Apache
 * to shut down, and idle until Apache's primary thread quits.
 */
    if ((msg == WM_ENDSESSION)
            && (die_on_logoff || (lParam != ENDSESSION_LOGOFF)))
    {
        ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
        if (wParam)
            /* Don't leave this message until we are dead! */
            WaitForSingleObject(globdat.mpm_thread, 30000);
        return 0;
    }
    return (DefWindowProc(hWnd, msg, wParam, lParam));
}
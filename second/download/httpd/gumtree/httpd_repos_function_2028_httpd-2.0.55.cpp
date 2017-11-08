void mpm_nt_eventlog_stderr_open(char *argv0, apr_pool_t *p)
{
    SECURITY_ATTRIBUTES sa;
    HANDLE hProc = GetCurrentProcess();
    HANDLE hPipeRead = NULL;
    HANDLE hPipeWrite = NULL;
    HANDLE hDup = NULL;
    DWORD  threadid;
    int    fd;

    display_name = argv0;

    /* Create a pipe to send stderr messages to the system error log.
     *
     * _dup2() duplicates the write handle inheritable for us.
     */
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = FALSE;
    CreatePipe(&hPipeRead, &hPipeWrite, NULL, 0); 
    ap_assert(hPipeRead && hPipeWrite);

    stderr_ready = CreateEvent(NULL, FALSE, FALSE, NULL);
    stderr_thread = CreateThread(NULL, 0, service_stderr_thread,
                                 (LPVOID) hPipeRead, 0, &threadid);
    ap_assert(stderr_ready && stderr_thread);

    WaitForSingleObject(stderr_ready, INFINITE);

    /* Flush stderr and unset its buffer, then commit and replace stderr.
     * This is typically a noop for Win2K/XP since services with NULL std 
     * handles [but valid FILE *'s, oddly enough], but is required 
     * for NT 4.0 and to use this code outside of services.
     */
    fflush(stderr);
    setvbuf(stderr, NULL, _IONBF, 0);
    _commit(2 /* stderr */);
    fd = _open_osfhandle((long) hPipeWrite, 
                         _O_WRONLY | _O_BINARY);
    _dup2(fd, 2);
    _close(fd);
    _setmode(2, _O_BINARY);

    /* hPipeWrite was _close()'ed above, and _dup2()'ed
     * to fd 2 creating a new, inherited Win32 handle.
     * Recover that real handle from fd 2.
     */
    hPipeWrite = (HANDLE)_get_osfhandle(2);

    SetStdHandle(STD_ERROR_HANDLE, hPipeWrite);

    /* The code above _will_ corrupt the StdHandle... 
     * and we must do so anyways.  We set this up only
     * after we initialized the posix stderr API.
     */
    ap_open_stderr_log(p);
}
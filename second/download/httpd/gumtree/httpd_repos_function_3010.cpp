void mpm_nt_eventlog_stderr_open(char *argv0, apr_pool_t *p)
{
    SECURITY_ATTRIBUTES sa;
    HANDLE hProc = GetCurrentProcess();
    HANDLE hPipeRead = NULL;
    HANDLE hPipeWrite = NULL;
    HANDLE hDup = NULL;
    DWORD  threadid;
    apr_file_t *eventlog_file;
    apr_file_t *stderr_file;

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
    stderr_thread = CreateThread(NULL, 65536, service_stderr_thread,
                                 (LPVOID)hPipeRead, stack_res_flag, &threadid);
    ap_assert(stderr_ready && stderr_thread);

    WaitForSingleObject(stderr_ready, INFINITE);

    if ((apr_file_open_stderr(&stderr_file, p) 
             == APR_SUCCESS)
     && (apr_os_file_put(&eventlog_file, &hPipeWrite, APR_WRITE, p)
             == APR_SUCCESS))
        apr_file_dup2(stderr_file, eventlog_file, p);

    /* The code above _will_ corrupt the StdHandle...
     * and we must do so anyways.  We set this up only
     * after we initialized the posix stderr API.
     */
    ap_open_stderr_log(p);
}
                               lpWSAProtocolInfo) == SOCKET_ERROR) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), ap_server_conf,
                         "Parent: WSADuplicateSocket failed for socket %d. Check the FAQ.", lr->sd );
            return -1;
        }

        if (!WriteFile(hPipeWrite, lpWSAProtocolInfo, (DWORD) sizeof(WSAPROTOCOL_INFO),
                       &BytesWritten,
                       (LPOVERLAPPED) NULL)
                || BytesWritten != sizeof(WSAPROTOCOL_INFO)) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                         "Parent: Unable to write duplicated socket %d to the child.", lr->sd );
            return -1;
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                 "Parent: Sent %d listeners to child %d", lcnt, dwProcessId);
    return 0;
}

static int create_process(apr_pool_t *p, HANDLE *child_proc, HANDLE *child_exit_event, 
                          DWORD *child_pid)
{
    int rv;
    char buf[1024];
    char *pCommand;
    char *pEnvVar;
    char *pEnvBlock;
    int i;
    int iEnvBlockLen;
    STARTUPINFO si;           /* Filled in prior to call to CreateProcess */
    PROCESS_INFORMATION pi;   /* filled in on call to CreateProcess */
    HANDLE hDup;
    HANDLE hPipeRead;
    HANDLE hPipeWrite;
    HANDLE hNullOutput;
    HANDLE hShareError;
    HANDLE hExitEvent;
    HANDLE hCurrentProcess = GetCurrentProcess();
    SECURITY_ATTRIBUTES sa;

    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    /* Build the command line. Should look something like this:
     * C:/apache/bin/apache.exe -f ap_server_confname 
     * First, get the path to the executable...
     */
    rv = GetModuleFileName(NULL, buf, sizeof(buf));
    if (rv == sizeof(buf)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, ERROR_BAD_PATHNAME, ap_server_conf,
                     "Parent: Path to Apache process too long");
        return -1;
    } else if (rv == 0) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: GetModuleFileName() returned NULL for current process.");
        return -1;
    }

    /* Build the command line */
    pCommand = apr_psprintf(p, "\"%s\"", buf);  
    for (i = 1; i < ap_server_conf->process->argc; i++) {
        pCommand = apr_pstrcat(p, pCommand, " \"", ap_server_conf->process->argv[i], "\"", NULL);
    }

    /* Create a pipe to send socket info to the child */
    if (!CreatePipe(&hPipeRead, &hPipeWrite, &sa, 0)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Unable to create pipe to child process.");
        return -1;
    }

    /* Make our end of the handle non-inherited */
    if (DuplicateHandle(hCurrentProcess, hPipeWrite, hCurrentProcess,
                        &hDup, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
        CloseHandle(hPipeWrite);
        hPipeWrite = hDup;
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Unable to duplicate pipe to child.\n");
        CloseHandle(hPipeWrite);
        CloseHandle(hPipeRead);
        return -1;
    }

    /* Open a null handle to soak info from the child */
    hNullOutput = CreateFile("nul", GENERIC_READ | GENERIC_WRITE, 
                             FILE_SHARE_READ | FILE_SHARE_WRITE, 
                             &sa, OPEN_EXISTING, 0, NULL);
    if (hNullOutput == INVALID_HANDLE_VALUE) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Unable to create null output pipe for child process.\n");
        CloseHandle(hPipeWrite);
        CloseHandle(hPipeRead);
        return -1;
    }

    /* Child's initial stderr -> our main server error log (or, failing that, stderr) */
    if (ap_server_conf->error_log) { /* Is this check really necessary?*/
        rv = apr_os_file_get(&hShareError, ap_server_conf->error_log);
        if (rv == APR_SUCCESS && hShareError != INVALID_HANDLE_VALUE) {
            if (DuplicateHandle(hCurrentProcess, hShareError, 
                                hCurrentProcess, &hDup, 
                                GENERIC_WRITE, TRUE, 0)) {
                hShareError = hDup;
            }
            else {
                rv = apr_get_os_error();
            }
        }
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                         "Parent: Unable to share error log with child.\n");
            CloseHandle(hPipeWrite);
            CloseHandle(hPipeRead);
            CloseHandle(hNullOutput);
            return -1;
        }
        else if (hShareError == INVALID_HANDLE_VALUE) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf,
                         "Parent: Failed to share error log with child.\n");
            CloseHandle(hPipeWrite);
            CloseHandle(hPipeRead);
            CloseHandle(hNullOutput);
            return -1;
        }
    }
    else {
        hShareError = GetStdHandle(STD_ERROR_HANDLE);
    }

    /* Create the child_exit_event */
    hExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!hExitEvent) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Could not create exit event for child process");
        CloseHandle(hPipeWrite);
        CloseHandle(hPipeRead);
        CloseHandle(hNullOutput);
        if (GetStdHandle(STD_ERROR_HANDLE) != hShareError) {
            CloseHandle(hShareError);
        }
        return -1;
    }
    
    /*
     * Build the environment
     * Win32's CreateProcess call requires that the environment
     * be passed in an environment block, a null terminated block of
     * null terminated strings.
     */  
    _putenv(apr_psprintf(p,"AP_PARENT_PID=%i", parent_pid));

    i = 0;
    iEnvBlockLen = 1;
    while (_environ[i]) {
        iEnvBlockLen += strlen(_environ[i]) + 1;
        i++;
    }
    pEnvBlock = (char *)apr_pcalloc(p, iEnvBlockLen);
    pEnvVar = pEnvBlock;
    i = 0;
    while (_environ[i]) {
        strcpy(pEnvVar, _environ[i]);
        pEnvVar = strchr(pEnvVar, '\0') + 1;
        i++;
    }
    pEnvVar = '\0';

    /* Give the read end of the pipe (hPipeRead) to the child as stdin. The 
     * parent will write the socket data to the child on this pipe.
     */
    memset(&si, 0, sizeof(si));
    memset(&pi, 0, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;
    si.hStdInput   = hPipeRead;
    si.hStdOutput  = hNullOutput;
    si.hStdError   = hShareError;

    rv = CreateProcess(NULL, pCommand, NULL, NULL, 
                       TRUE,               /* Inherit handles */
                       0,                  /* Creation flags */
                       pEnvBlock,          /* Environment block */
                       NULL,
                       &si, &pi);

    /* Undo everything created for the child alone
     */
    CloseHandle(pi.hThread);
    CloseHandle(hPipeRead);
    CloseHandle(hNullOutput);
    if (GetStdHandle(STD_ERROR_HANDLE) != hShareError) {
        /* Handles opened with GetStdHandle are psuedo handles
         * and should not be closed else bad things will happen.
         */
        CloseHandle(hShareError);
    }
    _putenv("AP_PARENT_PID=");

    if (!rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Failed to create the child process.");
        CloseHandle(hExitEvent);
        CloseHandle(hPipeWrite);
        CloseHandle(pi.hProcess);
        return -1;
    }

    ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                 "Parent: Created child process %d", pi.dwProcessId);

    if (send_handles_to_child(p, hExitEvent, pi.hProcess, hPipeWrite)) {
        /*
         * This error is fatal, mop up the child and move on
         * We toggle the child's exit event to cause this child 
         * to quit even as it is attempting to start.
         */
        SetEvent(hExitEvent);
        CloseHandle(hExitEvent);
        CloseHandle(hPipeWrite);
        CloseHandle(pi.hProcess);
        return -1;
    }

    /* Important:
     * Give the child process a chance to run before dup'ing the sockets.
     * We have already set the listening sockets noninheritable, but if 
     * WSADuplicateSocket runs before the child process initializes
     * the listeners will be inherited anyway.
     *
     * XXX: This is badness; needs some mutex interlocking
     */
    Sleep(1000);

    if (send_listeners_to_child(p, pi.dwProcessId, hPipeWrite)) {
        /*
         * This error is fatal, mop up the child and move on
         * We toggle the child's exit event to cause this child 
         * to quit even as it is attempting to start.
         */
        SetEvent(hExitEvent);
        CloseHandle(hExitEvent);
        CloseHandle(hPipeWrite);        
        CloseHandle(pi.hProcess);
        return -1;
    }

    CloseHandle(hPipeWrite);        

    *child_proc = pi.hProcess;
    *child_exit_event = hExitEvent;
    *child_pid = pi.dwProcessId;

    return 0;
}

/***********************************************************************
 * master_main()

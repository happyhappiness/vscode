static int create_process(apr_pool_t *p, HANDLE *child_proc, HANDLE *child_exit_event,
                          DWORD *child_pid)
{
    /* These NEVER change for the lifetime of this parent
     */
    static char **args = NULL;
    static char pidbuf[28];

    apr_status_t rv;
    apr_pool_t *ptemp;
    apr_procattr_t *attr;
    apr_proc_t new_child;
    HANDLE hExitEvent;
    HANDLE waitlist[2];  /* see waitlist_e */
    char *cmd;
    char *cwd;
    char **env;
    int envc;

    apr_pool_create_ex(&ptemp, p, NULL, NULL);

    /* Build the command line. Should look something like this:
     * C:/apache/bin/httpd.exe -f ap_server_confname
     * First, get the path to the executable...
     */
    apr_procattr_create(&attr, ptemp);
    apr_procattr_cmdtype_set(attr, APR_PROGRAM);
    apr_procattr_detach_set(attr, 1);
    if (((rv = apr_filepath_get(&cwd, 0, ptemp)) != APR_SUCCESS)
           || ((rv = apr_procattr_dir_set(attr, cwd)) != APR_SUCCESS)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                     "Parent: Failed to get the current path");
    }

    if (!args) {
        /* Build the args array, only once since it won't change
         * for the lifetime of this parent process.
         */
        if ((rv = ap_os_proc_filepath(&cmd, ptemp))
                != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, ERROR_BAD_PATHNAME, ap_server_conf,
                         "Parent: Failed to get full path of %s",
                         ap_server_conf->process->argv[0]);
            apr_pool_destroy(ptemp);
            return -1;
        }

        args = malloc((ap_server_conf->process->argc + 1) * sizeof (char*));
        memcpy(args + 1, ap_server_conf->process->argv + 1,
               (ap_server_conf->process->argc - 1) * sizeof (char*));
        args[0] = malloc(strlen(cmd) + 1);
        strcpy(args[0], cmd);
        args[ap_server_conf->process->argc] = NULL;
    }
    else {
        cmd = args[0];
    }

    /* Create a pipe to send handles to the child */
    if ((rv = apr_procattr_io_set(attr, APR_FULL_BLOCK,
                                  APR_NO_PIPE, APR_NO_PIPE)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                        "Parent: Unable to create child stdin pipe.");
        apr_pool_destroy(ptemp);
        return -1;
    }

    /* Create the child_ready_event */
    waitlist[waitlist_ready] = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!waitlist[waitlist_ready]) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Could not create ready event for child process");
        apr_pool_destroy (ptemp);
        return -1;
    }

    /* Create the child_exit_event */
    hExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!hExitEvent) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Could not create exit event for child process");
        apr_pool_destroy(ptemp);
        CloseHandle(waitlist[waitlist_ready]);
        return -1;
    }

    /* Build the env array */
    for (envc = 0; _environ[envc]; ++envc) {
        ;
    }
    env = apr_palloc(ptemp, (envc + 2) * sizeof (char*));  
    memcpy(env, _environ, envc * sizeof (char*));
    apr_snprintf(pidbuf, sizeof(pidbuf), "AP_PARENT_PID=%i", parent_pid);
    env[envc] = pidbuf;
    env[envc + 1] = NULL;

    rv = apr_proc_create(&new_child, cmd, args, env, attr, ptemp);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                     "Parent: Failed to create the child process.");
        apr_pool_destroy(ptemp);
        CloseHandle(hExitEvent);
        CloseHandle(waitlist[waitlist_ready]);
        CloseHandle(new_child.hproc);
        return -1;
    }

    ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                 "Parent: Created child process %d", new_child.pid);

    if (send_handles_to_child(ptemp, waitlist[waitlist_ready], hExitEvent,
                              start_mutex, ap_scoreboard_shm,
                              new_child.hproc, new_child.in)) {
        /*
         * This error is fatal, mop up the child and move on
         * We toggle the child's exit event to cause this child
         * to quit even as it is attempting to start.
         */
        SetEvent(hExitEvent);
        apr_pool_destroy(ptemp);
        CloseHandle(hExitEvent);
        CloseHandle(waitlist[waitlist_ready]);
        CloseHandle(new_child.hproc);
        return -1;
    }

    /* Important:
     * Give the child process a chance to run before dup'ing the sockets.
     * We have already set the listening sockets noninheritable, but if
     * WSADuplicateSocket runs before the child process initializes
     * the listeners will be inherited anyway.
     */
    waitlist[waitlist_term] = new_child.hproc;
    rv = WaitForMultipleObjects(2, waitlist, FALSE, INFINITE);
    CloseHandle(waitlist[waitlist_ready]);
    if (rv != WAIT_OBJECT_0) {
        /*
         * Outch... that isn't a ready signal. It's dead, Jim!
         */
        SetEvent(hExitEvent);
        apr_pool_destroy(ptemp);
        CloseHandle(hExitEvent);
        CloseHandle(new_child.hproc);
        return -1;
    }

    if (send_listeners_to_child(ptemp, new_child.pid, new_child.in)) {
        /*
         * This error is fatal, mop up the child and move on
         * We toggle the child's exit event to cause this child
         * to quit even as it is attempting to start.
         */
        SetEvent(hExitEvent);
        apr_pool_destroy(ptemp);
        CloseHandle(hExitEvent);
        CloseHandle(new_child.hproc);
        return -1;
    }

    apr_file_close(new_child.in);

    *child_exit_event = hExitEvent;
    *child_proc = new_child.hproc;
    *child_pid = new_child.pid;

    return 0;
}
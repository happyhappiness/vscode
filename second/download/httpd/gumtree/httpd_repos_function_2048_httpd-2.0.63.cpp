static int create_process(apr_pool_t *p, HANDLE *child_proc, HANDLE *child_exit_event, 
                          DWORD *child_pid)
{
    /* These NEVER change for the lifetime of this parent 
     */
    static char **args = NULL;
    static char **env = NULL;
    static char pidbuf[28];

    apr_status_t rv;
    apr_pool_t *ptemp;
    apr_procattr_t *attr;
    apr_proc_t new_child;
    apr_file_t *child_out, *child_err;
    HANDLE hExitEvent;
    HANDLE waitlist[2];  /* see waitlist_e */
    char *cmd;
    char *cwd;

    apr_pool_sub_make(&ptemp, p, NULL);

    /* Build the command line. Should look something like this:
     * C:/apache/bin/apache.exe -f ap_server_confname 
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

    /* httpd-2.0/2.2 specific to work around apr_proc_create bugs */
    if (((rv = apr_file_open_stdout(&child_out, p))
            != APR_SUCCESS) ||
        ((rv = apr_procattr_child_out_set(attr, child_out, NULL))
            != APR_SUCCESS)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                     "Parent: Could not set child process stdout");
    }
    if (((rv = apr_file_open_stderr(&child_err, p))
            != APR_SUCCESS) ||
        ((rv = apr_procattr_child_err_set(attr, child_err, NULL))
            != APR_SUCCESS)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                     "Parent: Could not set child process stderr");
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

    if (!env) 
    {
        /* Build the env array, only once since it won't change 
         * for the lifetime of this parent process.
         */
        int envc;
        for (envc = 0; _environ[envc]; ++envc) {
            ;
        }
        env = malloc((envc + 2) * sizeof (char*));
        memcpy(env, _environ, envc * sizeof (char*));
        apr_snprintf(pidbuf, sizeof(pidbuf), "AP_PARENT_PID=%i", parent_pid);
        env[envc] = pidbuf;
        env[envc + 1] = NULL;
    }

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
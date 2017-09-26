
enum waitlist_e {
    waitlist_ready = 0,
    waitlist_term = 1
};

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
    apr_file_t *child_out;
    apr_file_t *child_err;
    apr_proc_t new_child;
    HANDLE hExitEvent;
    HANDLE waitlist[2];  /* see waitlist_e */
    char *cmd;
    char *cwd;

    apr_pool_create_ex(&ptemp, p, NULL, NULL);

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

    /* Open a null handle to soak info from the child */
    if (((rv = apr_file_open(&child_out, "NUL", APR_READ | APR_WRITE,
                             APR_OS_DEFAULT, ptemp)) != APR_SUCCESS)
        || ((rv = apr_procattr_child_out_set(attr, child_out, NULL))
                != APR_SUCCESS)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                        "Parent: Unable to connect child stdout to NUL.");
        apr_pool_destroy(ptemp);
        return -1;
    }

    /* Connect the child's initial stderr to our main server error log
     * or share our own stderr handle.
     */
    if (ap_server_conf->error_log) {
        child_err = ap_server_conf->error_log;
    }
    else {
        rv = apr_file_open_stderr(&child_err, ptemp);
    }
    if (rv == APR_SUCCESS) {
        if ((rv = apr_procattr_child_err_set(attr, child_err, NULL))
                != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                            "Parent: Unable to connect child stderr.");
            apr_pool_destroy(ptemp);
            return -1;
        }
    }

    /* Create the child_ready_event */
    waitlist[waitlist_ready] = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!waitlist[waitlist_ready]) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,

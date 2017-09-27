
    osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osver);

    /* AP_PARENT_PID is only valid in the child */
    pid = getenv("AP_PARENT_PID");
    if (pid)
    {
        /* This is the child */
        my_pid = GetCurrentProcessId();
        parent_pid = (DWORD) atol(pid);

        /* Prevent holding open the (nonexistant) console */
        ap_real_exit_code = 0;

        /* The parent is responsible for providing the
         * COMPLETE ARGUMENTS REQUIRED to the child.
         *
         * No further argument parsing is needed, but
         * for good measure we will provide a simple
         * signal string for later testing.
         */
        signal_arg = "runchild";
        return;
    }

    /* This is the parent, we have a long way to go :-) */
    parent_pid = my_pid = GetCurrentProcessId();

    /* This behavior is voided by setting real_exit_code to 0 */
    atexit(hold_console_open_on_error);

    /* Rewrite process->argv[];
     *
     * strip out -k signal into signal_arg
     * strip out -n servicename and set the names
     * add default -d serverroot from the path of this executable
     *
     * The end result will look like:
     *
     * The invocation command (%0)
     *     The -d serverroot default from the running executable
     *         The requested service's (-n) registry ConfigArgs
     *             The WinNT SCM's StartService() args
     */
    if ((rv = ap_os_proc_filepath(&binpath, process->pconf))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK,APLOG_CRIT, rv, NULL,
                     "Failed to get the full path of %s", process->argv[0]);
        exit(APEXIT_INIT);
    }
    /* WARNING: There is an implict assumption here that the
     * executable resides in ServerRoot or ServerRoot\bin
     */
    def_server_root = (char *) apr_filepath_name_get(binpath);
    if (def_server_root > binpath) {
        *(def_server_root - 1) = '\0';
        def_server_root = (char *) apr_filepath_name_get(binpath);
        if (!strcasecmp(def_server_root, "bin"))
            *(def_server_root - 1) = '\0';
    }
    apr_filepath_merge(&def_server_root, NULL, binpath,
                       APR_FILEPATH_TRUENAME, process->pool);

    /* Use process->pool so that the rewritten argv
     * lasts for the lifetime of the server process,
     * because pconf will be destroyed after the
     * initial pre-flight of the config parser.
     */
    mpm_new_argv = apr_array_make(process->pool, process->argc + 2,
                                  sizeof(const char *));
    *(const char **)apr_array_push(mpm_new_argv) = process->argv[0];
    *(const char **)apr_array_push(mpm_new_argv) = "-d";

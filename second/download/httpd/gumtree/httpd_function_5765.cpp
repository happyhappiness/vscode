static void winnt_rewrite_args(process_rec *process)
{
    /* Handle the following SCM aspects in this phase:
     *
     *   -k runservice [transition in service context only]
     *   -k install
     *   -k config
     *   -k uninstall
     *   -k stop
     *   -k shutdown (same as -k stop). Maintained for backward compatability.
     *
     * We can't leave this phase until we know our identity
     * and modify the command arguments appropriately.
     *
     * We do not care if the .conf file exists or is parsable when
     * attempting to stop or uninstall a service.
     */
    apr_status_t rv;
    char *def_server_root;
    char *binpath;
    char optbuf[3];
    const char *opt_arg;
    int fixed_args;
    char *pid;
    apr_getopt_t *opt;
    int running_as_service = 1;
    int errout = 0;
    apr_file_t *nullfile;

    pconf = process->pconf;

    osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osver);

    /* We wish this was *always* a reservation, but sadly it wasn't so and
     * we couldn't break a hard limit prior to NT Kernel 5.1
     */
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT
        && ((osver.dwMajorVersion > 5)
         || ((osver.dwMajorVersion == 5) && (osver.dwMinorVersion > 0)))) {
        stack_res_flag = STACK_SIZE_PARAM_IS_A_RESERVATION;
    }

    /* AP_PARENT_PID is only valid in the child */
    pid = getenv("AP_PARENT_PID");
    if (pid)
    {
        HANDLE filehand;
        HANDLE hproc = GetCurrentProcess();
        DWORD BytesRead;

        /* This is the child */
        my_pid = GetCurrentProcessId();
        parent_pid = (DWORD) atol(pid);

        /* Prevent holding open the (nonexistant) console */
        ap_real_exit_code = 0;

        /* The parent gave us stdin, we need to remember this
         * handle, and no longer inherit it at our children
         * (we can't slurp it up now, we just aren't ready yet).
         * The original handle is closed below, at apr_file_dup2()
         */
        pipe = GetStdHandle(STD_INPUT_HANDLE);
        if (DuplicateHandle(hproc, pipe,
                            hproc, &filehand, 0, FALSE,
                            DUPLICATE_SAME_ACCESS)) {
            pipe = filehand;
        }

        /* The parent gave us stdout of the NUL device,
         * and expects us to suck up stdin of all of our
         * shared handles and data from the parent.
         * Don't infect child processes with our stdin
         * handle, use another handle to NUL!
         */
        {
            apr_file_t *infile, *outfile;
            if ((apr_file_open_stdout(&outfile, process->pool) == APR_SUCCESS)
             && (apr_file_open_stdin(&infile, process->pool) == APR_SUCCESS))
                apr_file_dup2(infile, outfile, process->pool);
        }

        /* This child needs the existing stderr opened for logging,
         * already
         */

        /* Read this child's generation number as soon as now,
         * so that further hooks can query it.
         */
        if (!ReadFile(pipe, &my_generation, sizeof(my_generation),
                      &BytesRead, (LPOVERLAPPED) NULL)
                || (BytesRead != sizeof(my_generation))) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), NULL, APLOGNO(02965)
                         "Child: Unable to retrieve my generation from the parent");
            exit(APEXIT_CHILDINIT);
        }

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
        ap_log_error(APLOG_MARK,APLOG_CRIT, rv, NULL, APLOGNO(00432)
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
    *(const char **)apr_array_push(mpm_new_argv) = def_server_root;

    fixed_args = mpm_new_argv->nelts;

    optbuf[0] = '-';
    optbuf[2] = '\0';
    apr_getopt_init(&opt, process->pool, process->argc, process->argv);
    opt->errfn = NULL;
    while ((rv = apr_getopt(opt, "wn:k:" AP_SERVER_BASEARGS,
                            optbuf + 1, &opt_arg)) == APR_SUCCESS) {
        switch (optbuf[1]) {

        /* Shortcuts; include the -w option to hold the window open on error.
         * This must not be toggled once we reset ap_real_exit_code to 0!
         */
        case 'w':
            if (ap_real_exit_code)
                ap_real_exit_code = 2;
            break;

        case 'n':
            service_set = mpm_service_set_name(process->pool, &service_name,
                                               opt_arg);
            break;

        case 'k':
            signal_arg = opt_arg;
            break;

        case 'E':
            errout = 1;
            /* Fall through so the Apache main() handles the 'E' arg */
        default:
            *(const char **)apr_array_push(mpm_new_argv) =
                apr_pstrdup(process->pool, optbuf);

            if (opt_arg) {
                *(const char **)apr_array_push(mpm_new_argv) = opt_arg;
            }
            break;
        }
    }

    /* back up to capture the bad argument */
    if (rv == APR_BADCH || rv == APR_BADARG) {
        opt->ind--;
    }

    while (opt->ind < opt->argc) {
        *(const char **)apr_array_push(mpm_new_argv) =
            apr_pstrdup(process->pool, opt->argv[opt->ind++]);
    }

    /* Track the number of args actually entered by the user */
    inst_argc = mpm_new_argv->nelts - fixed_args;

    /* Provide a default 'run' -k arg to simplify signal_arg tests */
    if (!signal_arg)
    {
        signal_arg = "run";
        running_as_service = 0;
    }

    if (!strcasecmp(signal_arg, "runservice"))
    {
        /* Start the NT Service _NOW_ because the WinNT SCM is
         * expecting us to rapidly assume control of our own
         * process, the SCM will tell us our service name, and
         * may have extra StartService() command arguments to
         * add for us.
         *
         * The SCM will generally invoke the executable with
         * the c:\win\system32 default directory.  This is very
         * lethal if folks use ServerRoot /foopath on windows
         * without a drive letter.  Change to the default root
         * (path to apache root, above /bin) for safety.
         */
        apr_filepath_set(def_server_root, process->pool);

        /* Any other process has a console, so we don't to begin
         * a Win9x service until the configuration is parsed and
         * any command line errors are reported.
         *
         * We hold the return value so that we can die in pre_config
         * after logging begins, and the failure can land in the log.
         */
        if (!errout) {
            mpm_nt_eventlog_stderr_open(service_name, process->pool);
        }
        service_to_start_success = mpm_service_to_start(&service_name,
                                                        process->pool);
        if (service_to_start_success == APR_SUCCESS) {
            service_set = APR_SUCCESS;
        }

        /* Open a null handle to soak stdout in this process.
         * Windows service processes are missing any file handle
         * usable for stdin/out/err.  This was the cause of later
         * trouble with invocations of apr_file_open_stdout()
         */
        if ((rv = apr_file_open(&nullfile, "NUL",
                                APR_READ | APR_WRITE, APR_OS_DEFAULT,
                                process->pool)) == APR_SUCCESS) {
            apr_file_t *nullstdout;
            if (apr_file_open_stdout(&nullstdout, process->pool)
                    == APR_SUCCESS)
                apr_file_dup2(nullstdout, nullfile, process->pool);
            apr_file_close(nullfile);
        }
    }

    /* Get the default for any -k option, except run */
    if (service_set == SERVICE_UNSET && strcasecmp(signal_arg, "run")) {
        service_set = mpm_service_set_name(process->pool, &service_name,
                                           AP_DEFAULT_SERVICE_NAME);
    }

    if (!strcasecmp(signal_arg, "install")) /* -k install */
    {
        if (service_set == APR_SUCCESS)
        {
            ap_log_error(APLOG_MARK,APLOG_ERR, 0, NULL, APLOGNO(00433)
                 "%s: Service is already installed.", service_name);
            exit(APEXIT_INIT);
        }
    }
    else if (running_as_service)
    {
        if (service_set == APR_SUCCESS)
        {
            /* Attempt to Uninstall, or stop, before
             * we can read the arguments or .conf files
             */
            if (!strcasecmp(signal_arg, "uninstall")) {
                rv = mpm_service_uninstall();
                exit(rv);
            }

            if ((!strcasecmp(signal_arg, "stop")) ||
                (!strcasecmp(signal_arg, "shutdown"))) {
                mpm_signal_service(process->pool, 0);
                exit(0);
            }

            rv = mpm_merge_service_args(process->pool, mpm_new_argv,
                                        fixed_args);
            if (rv == APR_SUCCESS) {
                ap_log_error(APLOG_MARK,APLOG_INFO, 0, NULL, APLOGNO(00434)
                             "Using ConfigArgs of the installed service "
                             "\"%s\".", service_name);
            }
            else  {
                ap_log_error(APLOG_MARK,APLOG_WARNING, rv, NULL, APLOGNO(00435)
                             "No installed ConfigArgs for the service "
                             "\"%s\", using Apache defaults.", service_name);
            }
        }
        else
        {
            ap_log_error(APLOG_MARK,APLOG_ERR, service_set, NULL, APLOGNO(00436)
                 "No installed service named \"%s\".", service_name);
            exit(APEXIT_INIT);
        }
    }
    if (strcasecmp(signal_arg, "install") && service_set && service_set != SERVICE_UNSET)
    {
        ap_log_error(APLOG_MARK,APLOG_ERR, service_set, NULL, APLOGNO(00437)
             "No installed service named \"%s\".", service_name);
        exit(APEXIT_INIT);
    }

    /* Track the args actually entered by the user.
     * These will be used for the -k install parameters, as well as
     * for the -k start service override arguments.
     */
    inst_argv = (const char * const *)mpm_new_argv->elts
        + mpm_new_argv->nelts - inst_argc;

    /* Now, do service install or reconfigure then proceed to
     * post_config to test the installed configuration.
     */
    if (!strcasecmp(signal_arg, "config")) { /* -k config */
        /* Reconfigure the service */
        rv = mpm_service_install(process->pool, inst_argc, inst_argv, 1);
        if (rv != APR_SUCCESS) {
            exit(rv);
        }

        fprintf(stderr,"Testing httpd.conf....\n");
        fprintf(stderr,"Errors reported here must be corrected before the "
                "service can be started.\n");
    }
    else if (!strcasecmp(signal_arg, "install")) { /* -k install */
        /* Install the service */
        rv = mpm_service_install(process->pool, inst_argc, inst_argv, 0);
        if (rv != APR_SUCCESS) {
            exit(rv);
        }

        fprintf(stderr,"Testing httpd.conf....\n");
        fprintf(stderr,"Errors reported here must be corrected before the "
                "service can be started.\n");
    }

    process->argc = mpm_new_argv->nelts;
    process->argv = (const char * const *) mpm_new_argv->elts;
}
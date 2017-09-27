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
        if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
        {
            if (!errout) {
                mpm_nt_eventlog_stderr_open(service_name, process->pool);
            }
            service_to_start_success = mpm_service_to_start(&service_name,
                                                            process->pool);
            if (service_to_start_success == APR_SUCCESS) {
                service_set = APR_SUCCESS;
            }
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
            ap_log_error(APLOG_MARK,APLOG_ERR, 0, NULL,
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
                ap_log_error(APLOG_MARK,APLOG_INFO, 0, NULL,
                             "Using ConfigArgs of the installed service "
                             "\"%s\".", service_name);
            }

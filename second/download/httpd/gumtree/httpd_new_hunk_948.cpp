        {
            ap_log_error(APLOG_MARK,APLOG_ERR, service_set, NULL,
                 "No installed service named \"%s\".", service_name);
            exit(APEXIT_INIT);
        }
    }
    if (strcasecmp(signal_arg, "install") && service_set && service_set != SERVICE_UNSET)
    {
        ap_log_error(APLOG_MARK,APLOG_ERR, service_set, NULL,
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


static int winnt_pre_config(apr_pool_t *pconf_, apr_pool_t *plog, apr_pool_t *ptemp)
{
    /* Handle the following SCM aspects in this phase:
     *
     *   -k runservice [WinNT errors logged from rewrite_args]
     */

    /* Initialize shared static objects.
     * TODO: Put config related statics into an sconf structure.
     */
    pconf = pconf_;

    if (ap_exists_config_define("ONE_PROCESS") ||
        ap_exists_config_define("DEBUG"))
        one_process = -1;

    if (!strcasecmp(signal_arg, "runservice")
            && (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
            && (service_to_start_success != APR_SUCCESS)) {
        ap_log_error(APLOG_MARK,APLOG_CRIT, service_to_start_success, NULL,
                     "%s: Unable to start the service manager.",
                     service_name);
        exit(APEXIT_INIT);
    }

    /* Win9x: disable AcceptEx */

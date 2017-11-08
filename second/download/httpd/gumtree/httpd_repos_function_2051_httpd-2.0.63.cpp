static int winnt_pre_config(apr_pool_t *pconf_, apr_pool_t *plog, apr_pool_t *ptemp) 
{
    /* Handle the following SCM aspects in this phase:
     *
     *   -k runservice [WinNT errors logged from rewrite_args]
     */

    /* Initialize shared static objects. 
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
    else if (!one_process && !ap_my_generation) {
        /* Open a null handle to soak stdout in this process.
         * We need to emulate apr_proc_detach, unix performs this
         * same check in the pre_config hook (although it is
         * arguably premature).  Services already fixed this.
         */
        apr_file_t *nullfile;
        apr_status_t rv;
        apr_pool_t *pproc = apr_pool_parent_get(pconf);

        if ((rv = apr_file_open(&nullfile, "NUL",
                                APR_READ | APR_WRITE, APR_OS_DEFAULT,
                                pproc)) == APR_SUCCESS) {
            apr_file_t *nullstdout;
            if (apr_file_open_stdout(&nullstdout, pproc)
                    == APR_SUCCESS)
                apr_file_dup2(nullstdout, nullfile, pproc);
            apr_file_close(nullfile);
        }
    }

    /* Win9x: disable AcceptEx */
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
        use_acceptex = 0;
    }

    ap_listen_pre_config();
    ap_threads_per_child = DEFAULT_THREADS_PER_CHILD;
    ap_pid_fname = DEFAULT_PIDLOG;
    ap_max_requests_per_child = DEFAULT_MAX_REQUESTS_PER_CHILD;
#ifdef AP_MPM_WANT_SET_MAX_MEM_FREE
	ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
#endif

    apr_cpystrn(ap_coredump_dir, ap_server_root, sizeof(ap_coredump_dir));

    return OK;
}
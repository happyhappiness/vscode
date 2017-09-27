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
    /* use_acceptex which is enabled by default is not available on Win9x.
     */
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
        use_acceptex = 0;
    }

    apr_cpystrn(ap_coredump_dir, ap_server_root, sizeof(ap_coredump_dir));

    return OK;
}

static int winnt_post_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec* s)
{

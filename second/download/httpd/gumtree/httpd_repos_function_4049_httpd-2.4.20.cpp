void mpm_common_pre_config(apr_pool_t *pconf)
{
    ap_pid_fname = DEFAULT_PIDLOG;
    ap_max_requests_per_child = 0; /* unlimited */
    apr_cpystrn(ap_coredump_dir, ap_server_root, sizeof(ap_coredump_dir));
    ap_coredumpdir_configured = 0;
    ap_graceful_shutdown_timeout = 0; /* unlimited */
    ap_max_mem_free = ALLOCATOR_MAX_FREE_DEFAULT;
    ap_thread_stacksize = 0; /* use system default */
}
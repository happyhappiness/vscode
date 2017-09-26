
    /* Initialize cross-process accept lock */
    ap_lock_fname = apr_psprintf(_pconf, "%s.%" APR_PID_T_FMT,
                                 ap_server_root_relative(_pconf, ap_lock_fname),
                                 ap_my_pid);

    rv = apr_proc_mutex_create(&accept_mutex, ap_lock_fname,
                               ap_accept_lock_mech, _pconf);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
                     "Couldn't create accept lock (%s) (%d)",
                     ap_lock_fname, ap_accept_lock_mech);
        mpm_state = AP_MPMQ_STOPPING;
        return 1;
    }

#if APR_USE_SYSVSEM_SERIALIZE
    if (ap_accept_lock_mech == APR_LOCK_DEFAULT ||
        ap_accept_lock_mech == APR_LOCK_SYSVSEM) {
#else
    if (ap_accept_lock_mech == APR_LOCK_SYSVSEM) {
#endif
        rv = unixd_set_proc_mutex_perms(accept_mutex);
        if (rv != APR_SUCCESS) {

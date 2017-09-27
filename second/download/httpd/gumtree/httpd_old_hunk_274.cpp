
    rv = apr_proc_mutex_create(&accept_mutex, ap_lock_fname, 
                               ap_accept_lock_mech, _pconf);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
                     "Couldn't create accept lock");
        return 1;
    }

#if APR_USE_SYSVSEM_SERIALIZE
    if (ap_accept_lock_mech == APR_LOCK_DEFAULT || 
        ap_accept_lock_mech == APR_LOCK_SYSVSEM) {

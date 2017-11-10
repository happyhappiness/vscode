static int wd_pre_config_hook(apr_pool_t *pconf, apr_pool_t *plog,
                              apr_pool_t *ptemp)
{
    apr_status_t rv;
    ap_watchdog_t *w;

    ap_mpm_query(AP_MPMQ_IS_FORKED, &mpm_is_forked);
    if ((rv = ap_watchdog_get_instance(&w,
                AP_WATCHDOG_SINGLETON, 0, 1, pconf)) != APR_SUCCESS) {
        return rv;
    }
    if ((rv = ap_watchdog_get_instance(&w,
                AP_WATCHDOG_DEFAULT, 0, 0, pconf)) != APR_SUCCESS) {
        return rv;
    }
    if (mpm_is_forked == AP_MPMQ_NOT_SUPPORTED) {
        /* Create parent process watchdog for
         * non forked mpm's only.
         */
        if ((rv = ap_watchdog_get_instance(&w,
                    AP_WATCHDOG_DEFAULT, 1, 0, pconf)) != APR_SUCCESS) {
            return rv;
        }
    }

    if ((rv = ap_mutex_register(pconf, wd_proc_mutex_type, NULL,
                                APR_LOCK_DEFAULT, 0)) != APR_SUCCESS) {
        return rv;
    }

    return OK;
}
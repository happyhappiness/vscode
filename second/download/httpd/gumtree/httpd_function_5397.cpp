static void exipc_child_init(apr_pool_t *p, server_rec *s)
{
    apr_status_t rs;

    /*
     * Re-open the mutex for the child. Note we're reusing
     * the mutex pointer global here.
     */
    rs = apr_global_mutex_child_init(&exipc_mutex,
                                     apr_global_mutex_lockfile(exipc_mutex),
                                     p);
    if (APR_SUCCESS != rs) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rs, s,
                     "Failed to reopen mutex %s in child",
                     exipc_mutex_type);
        /* There's really nothing else we can do here, since This
         * routine doesn't return a status. If this ever goes wrong,
         * it will turn Apache into a fork bomb. Let's hope it never
         * will.
         */
        exit(1); /* Ugly, but what else? */
    }
}
    /* set up priv_setid for per-request use */
    priv_setid = priv_allocset();
    apr_pool_cleanup_register(pconf, NULL, privileges_term,
                              apr_pool_cleanup_null);
    priv_emptyset(priv_setid);
    if (priv_addset(priv_setid, PRIV_PROC_SETID) == -1) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, errno, ptemp,
                      "priv_addset");
        return !OK;
    }
    return OK;
}
static int privileges_init(apr_pool_t *pconf, apr_pool_t *plog,
                           apr_pool_t *ptemp)
{
    /* refuse to work if the MPM is threaded */
    int threaded;
    int rv = ap_mpm_query(AP_MPMQ_IS_THREADED, &threaded);
    if (rv != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_NOTICE, rv, ptemp,
                      "mod_privileges: unable to determine MPM characteristics."
                      "  Please ensure you are using a non-threaded MPM "
                      "with this module.");
    }
    if (threaded) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, ptemp,
                      "mod_privileges is not compatible with a threaded MPM.");
        return !OK;
    }
    return OK;
}
static void privileges_hooks(apr_pool_t *pool)

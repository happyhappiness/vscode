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
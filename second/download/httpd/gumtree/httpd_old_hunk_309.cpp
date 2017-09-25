#endif

    /* when `RewriteEngine off' was used in the per-server
     * context then the rewritemap-programs were not spawned.
     * In this case using such a map (usually in per-dir context)
     * is useless because it is not available.
     */
    if (fpin == NULL || fpout == NULL) {
        return NULL;
    }

    /* take the lock */

    if (rewrite_mapr_lock_acquire) {
        rv = apr_global_mutex_lock(rewrite_mapr_lock_acquire);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,

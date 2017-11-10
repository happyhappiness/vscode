static void init_child(apr_pool_t *p, server_rec *s)
{
    apr_status_t rv = 0; /* get a rid of gcc warning (REWRITELOG_DISABLED) */

    if (lockname != NULL && *(lockname) != '\0') {
        rv = apr_global_mutex_child_init(&rewrite_mapr_lock_acquire,
                                         lockname, p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                         "mod_rewrite: could not init rewrite_mapr_lock_acquire"
                         " in child");
        }
    }

#ifndef REWRITELOG_DISABLED
    rv = apr_global_mutex_child_init(&rewrite_log_lock, NULL, p);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "mod_rewrite: could not init rewrite log lock in child");
    }
#endif

    /* create the lookup cache */
    if (!init_cache(p)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "mod_rewrite: could not init map cache in child");
    }
}
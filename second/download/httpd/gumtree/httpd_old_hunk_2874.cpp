    apr_status_t rv = 0; /* get a rid of gcc warning (REWRITELOG_DISABLED) */

    if (rewrite_mapr_lock_acquire) {
        rv = apr_global_mutex_child_init(&rewrite_mapr_lock_acquire,
                 apr_global_mutex_lockfile(rewrite_mapr_lock_acquire), p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                         "mod_rewrite: could not init rewrite_mapr_lock_acquire"
                         " in child");
        }
    }

    /* create the lookup cache */
    if (!init_cache(p)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "mod_rewrite: could not init map cache in child");
    }
}


/*

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

                                      APR_LOCK_DEFAULT, p)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "mod_rewrite: could not create rewrite_log_lock");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

#if APR_USE_SYSVSEM_SERIALIZE
    rv = unixd_set_global_mutex_perms(rewrite_log_lock);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "mod_rewrite: Could not set permissions on "
                     "rewrite_log_lock; check User and Group directives");
        return HTTP_INTERNAL_SERVER_ERROR;
    }
#endif

    rv = rewritelock_create(s, p);
    if (rv != APR_SUCCESS) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    apr_pool_cleanup_register(p, (void *)s, rewritelock_remove, apr_pool_cleanup_null);

    /* step through the servers and
     * - open each rewriting logfile
     * - open the RewriteMap prg:xxx programs
     */
    for (; s; s = s->next) {
        open_rewritelog(s, p);
        if (!first_time) {
            if (run_rewritemap_programs(s, p) != APR_SUCCESS) {
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
    }
    return OK;
}


/*

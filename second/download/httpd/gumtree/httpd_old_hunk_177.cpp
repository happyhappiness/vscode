                                      APR_LOCK_DEFAULT, p)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "mod_rewrite: could not create rewrite_log_lock");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    rewritelock_create(s, p);
    apr_pool_cleanup_register(p, (void *)s, rewritelock_remove, apr_pool_cleanup_null);

    /* step through the servers and
     * - open each rewriting logfile
     * - open the RewriteMap prg:xxx programs
     */
    for (; s; s = s->next) {
        open_rewritelog(s, p);
        if (!first_time)
           run_rewritemap_programs(s, p);
    }
    return OK;
}


/*

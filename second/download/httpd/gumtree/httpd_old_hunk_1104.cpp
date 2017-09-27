                              apr_pool_cleanup_null, s->process->pool);
    }

    /* check if proxy module is available */
    proxy_available = (ap_find_linked_module("mod_proxy.c") != NULL);

#ifndef REWRITELOG_DISABLED
    /* create the rewriting lockfiles in the parent */
    if ((rv = apr_global_mutex_create(&rewrite_log_lock, NULL,
                                      APR_LOCK_DEFAULT, p)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "mod_rewrite: could not create rewrite_log_lock");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

#ifdef AP_NEED_SET_MUTEX_PERMS
    rv = unixd_set_global_mutex_perms(rewrite_log_lock);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "mod_rewrite: Could not set permissions on "
                     "rewrite_log_lock; check User and Group directives");
        return HTTP_INTERNAL_SERVER_ERROR;
    }
#endif /* perms */
#endif /* rewritelog */

    rv = rewritelock_create(s, p);
    if (rv != APR_SUCCESS) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    apr_pool_cleanup_register(p, (void *)s, rewritelock_remove,

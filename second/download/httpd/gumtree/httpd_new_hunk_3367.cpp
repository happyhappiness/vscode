    apr_pool_tag(pchild, "pchild");

#if APR_HAS_THREADS
    osthd = apr_os_thread_current();
    apr_os_thread_put(&thd, &osthd, pchild);
#endif

    apr_pool_create(&ptrans, pchild);
    apr_pool_tag(ptrans, "transaction");

    /* needs to be done before we switch UIDs so we have permissions */
    ap_reopen_scoreboard(pchild, NULL, 0);
    lockfile = apr_proc_mutex_lockfile(accept_mutex);
    status = apr_proc_mutex_child_init(&accept_mutex,
                                       lockfile,
                                       pchild);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf, APLOGNO(00155)
                     "Couldn't initialize cross-process lock in child "
                     "(%s) (%s)",
                     lockfile ? lockfile : "none",
                     apr_proc_mutex_name(accept_mutex));
        clean_child_exit(APEXIT_CHILDFATAL);
    }

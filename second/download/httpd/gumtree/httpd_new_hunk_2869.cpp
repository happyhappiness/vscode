    }

    /* give the lock back */
    if (rewrite_mapr_lock_acquire) {
        rv = apr_global_mutex_unlock(rewrite_mapr_lock_acquire);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00660)
                          "apr_global_mutex_unlock(rewrite_mapr_lock_acquire) "
                          "failed");
            return NULL; /* Maybe this should be fatal? */
        }
    }


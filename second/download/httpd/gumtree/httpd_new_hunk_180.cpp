        return NULL;
    }

    /* take the lock */

    if (rewrite_mapr_lock_acquire) {
        rv = apr_global_mutex_lock(rewrite_mapr_lock_acquire);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "apr_global_mutex_lock(rewrite_mapr_lock_acquire) "
                          "failed");
            return NULL; /* Maybe this should be fatal? */
        }
    }

    /* write out the request key */
#ifdef NO_WRITEV
    nbytes = strlen(key);
    apr_file_write(fpin, key, &nbytes);

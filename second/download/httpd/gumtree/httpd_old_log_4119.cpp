ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "apr_global_mutex_unlock(rewrite_mapr_lock_acquire) "
                          "failed");
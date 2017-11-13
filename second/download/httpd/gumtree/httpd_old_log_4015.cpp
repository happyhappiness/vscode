ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "apr_global_mutex_lock(rewrite_mapr_lock_acquire) "
                          "failed");
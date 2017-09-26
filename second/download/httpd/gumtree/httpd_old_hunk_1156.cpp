                           level,
                           perdir ? "[perdir " : "",
                           perdir ? perdir : "",
                           perdir ? "] ": "",
                           text);

    rv = apr_global_mutex_lock(rewrite_log_lock);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "apr_global_mutex_lock(rewrite_log_lock) failed");
        /* XXX: Maybe this should be fatal? */
    }

    nbytes = strlen(logline);
    apr_file_write(conf->rewritelogfp, logline, &nbytes);

    rv = apr_global_mutex_unlock(rewrite_log_lock);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "apr_global_mutex_unlock(rewrite_log_lock) failed");
        /* XXX: Maybe this should be fatal? */
    }

    return;
}
#endif /* !REWRITELOG_DISABLED */


/*

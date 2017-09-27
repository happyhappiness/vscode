    apr_pool_userdata_set(lockname, CACHE_LOCKNAME_KEY, NULL, r->pool);

    /* is an existing lock file too old? */
    status = apr_stat(&finfo, lockname,
                APR_FINFO_MTIME | APR_FINFO_NLINK, r->pool);
    if (!(APR_STATUS_IS_ENOENT(status)) && APR_SUCCESS != status) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00779)
                "Could not stat a cache lock file: %s",
                lockname);
        return status;
    }
    if ((status == APR_SUCCESS) && (((now - finfo.mtime) > conf->lockmaxage)
                                  || (now < finfo.mtime))) {

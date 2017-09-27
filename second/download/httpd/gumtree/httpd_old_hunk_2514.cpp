    dir[4] = 0;

    /* make the directories */
    path = apr_pstrcat(r->pool, conf->lockpath, dir, NULL);
    if (APR_SUCCESS != (status = apr_dir_make_recursive(path,
            APR_UREAD|APR_UWRITE|APR_UEXECUTE, r->pool))) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "Could not create a cache lock directory: %s",
                     path);
        return status;
    }
    lockname = apr_pstrcat(r->pool, path, "/", lockname, NULL);
    apr_pool_userdata_set(lockname, CACHE_LOCKNAME_KEY, NULL, r->pool);

    /* is an existing lock file too old? */
    status = apr_stat(&finfo, lockname,
                APR_FINFO_MTIME | APR_FINFO_NLINK, r->pool);
    if (!(APR_STATUS_IS_ENOENT(status)) && APR_SUCCESS != status) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_EEXIST, r->server,
                     "Could not stat a cache lock file: %s",
                     lockname);
        return status;
    }
    if ((status == APR_SUCCESS) && (((now - finfo.mtime) > conf->lockmaxage)
                                  || (now < finfo.mtime))) {
        ap_log_error(APLOG_MARK, APLOG_INFO, status, r->server,
                     "Cache lock file for '%s' too old, removing: %s",
                     r->uri, lockname);
        apr_file_remove(lockname, r->pool);
    }

    /* try obtain a lock on the file */
    if (APR_SUCCESS == (status = apr_file_open(&lockfile, lockname,
            APR_WRITE | APR_CREATE | APR_EXCL | APR_DELONCLOSE,

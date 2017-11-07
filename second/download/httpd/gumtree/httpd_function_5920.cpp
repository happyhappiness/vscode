apr_status_t cache_try_lock(cache_server_conf *conf, cache_request_rec *cache,
        request_rec *r)
{
    apr_status_t status;
    const char *lockname;
    const char *path;
    char dir[5];
    apr_time_t now = apr_time_now();
    apr_finfo_t finfo;
    apr_file_t *lockfile;
    void *dummy;

    finfo.mtime = 0;

    if (!conf || !conf->lock || !conf->lockpath) {
        /* no locks configured, leave */
        return APR_SUCCESS;
    }

    /* lock already obtained earlier? if so, success */
    apr_pool_userdata_get(&dummy, CACHE_LOCKFILE_KEY, r->pool);
    if (dummy) {
        return APR_SUCCESS;
    }

    /* create the key if it doesn't exist */
    if (!cache->key) {
        cache_generate_key(r, r->pool, &cache->key);
    }

    /* create a hashed filename from the key, and save it for later */
    lockname = ap_cache_generate_name(r->pool, 0, 0, cache->key);

    /* lock files represent discrete just-went-stale URLs "in flight", so
     * we support a simple two level directory structure, more is overkill.
     */
    dir[0] = '/';
    dir[1] = lockname[0];
    dir[2] = '/';
    dir[3] = lockname[1];
    dir[4] = 0;

    /* make the directories */
    path = apr_pstrcat(r->pool, conf->lockpath, dir, NULL);
    if (APR_SUCCESS != (status = apr_dir_make_recursive(path,
            APR_UREAD|APR_UWRITE|APR_UEXECUTE, r->pool))) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00778)
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
        ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_EEXIST, r, APLOGNO(00779)
                "Could not stat a cache lock file: %s",
                lockname);
        return status;
    }
    if ((status == APR_SUCCESS) && (((now - finfo.mtime) > conf->lockmaxage)
                                  || (now < finfo.mtime))) {
        ap_log_rerror(APLOG_MARK, APLOG_INFO, status, r, APLOGNO(00780)
                "Cache lock file for '%s' too old, removing: %s",
                r->uri, lockname);
        apr_file_remove(lockname, r->pool);
    }

    /* try obtain a lock on the file */
    if (APR_SUCCESS == (status = apr_file_open(&lockfile, lockname,
            APR_WRITE | APR_CREATE | APR_EXCL | APR_DELONCLOSE,
            APR_UREAD | APR_UWRITE, r->pool))) {
        apr_pool_userdata_set(lockfile, CACHE_LOCKFILE_KEY, NULL, r->pool);
    }
    return status;

}
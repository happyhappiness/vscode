
    /* Look up entity keyed to 'url' */
    if (strcasecmp(type, "disk")) {
	return DECLINED;
    }

    if (conf->cache_root == NULL) {
        if (!error_logged) {
            error_logged = 1;
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "disk_cache: Cannot cache files to disk without a CacheRoot specified.");
        }
        return DECLINED;
    }

    data = data_file(r->pool, conf->dirlevels, conf->dirlength, 
                     conf->cache_root, key);
    headers = header_file(r->pool, conf->dirlevels, conf->dirlength, 
                          conf->cache_root, key);

    /* Open the data file */
    rc = apr_file_open(&fd, data, APR_READ|APR_BINARY, 0, r->pool);
    if (rc != APR_SUCCESS) {
        /* XXX: Log message */
        return DECLINED;
    }

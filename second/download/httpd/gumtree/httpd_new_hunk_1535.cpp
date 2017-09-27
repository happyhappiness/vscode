     */
    flags |= ((coreconf->enable_sendfile == ENABLE_SENDFILE_OFF)
              ? 0 : APR_SENDFILE_ENABLED);
#endif
    rc = apr_file_open(&dobj->fd, dobj->datafile, flags, 0, r->pool);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
                 "disk_cache: Cannot open info header file %s",  dobj->datafile);
        return DECLINED;
    }

    rc = apr_file_info_get(&finfo, APR_FINFO_SIZE, dobj->fd);
    if (rc == APR_SUCCESS) {
        dobj->file_size = finfo.size;
    }

    /* Read the bytes to setup the cache_info fields */
    rc = file_cache_recall_mydata(dobj->hfd, info, dobj, r);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
                 "disk_cache: Cannot read header file %s",  dobj->hdrsfile);
        return DECLINED;
    }

    /* Initialize the cache_handle callback functions */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "disk_cache: Recalled cached URL info header %s",  dobj->name);

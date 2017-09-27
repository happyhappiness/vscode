
    rv = apr_file_mktemp(&dobj->hfd, dobj->tempfile,
                         APR_CREATE | APR_WRITE | APR_BINARY |
                         APR_BUFFERED | APR_EXCL, r->pool);

    if (rv != APR_SUCCESS) {
       ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
           "disk_cache: could not create temp file %s",
           dobj->tempfile);
        return rv;
    }

    disk_info.format = DISK_FORMAT_VERSION;
    disk_info.date = info->date;
    disk_info.expire = info->expire;


    rv = apr_file_mktemp(&dobj->hdrs.tempfd, dobj->hdrs.tempfile,
                         APR_CREATE | APR_WRITE | APR_BINARY |
                         APR_BUFFERED | APR_EXCL, dobj->hdrs.pool);

    if (rv != APR_SUCCESS) {
       ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00725)
                "could not create header file %s",
                dobj->hdrs.tempfile);
        return rv;
    }

    disk_info.format = DISK_FORMAT_VERSION;

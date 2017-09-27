        ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(00706)
                "Cannot read header file %s", dobj->hdrs.file);
        apr_file_close(dobj->hdrs.fd);
        return DECLINED;
    }

    apr_file_close(dobj->hdrs.fd);

    /* Is this a cached HEAD request? */
    if (dobj->disk_info.header_only && !r->header_only) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00707)
                "HEAD request cached, non-HEAD requested, ignoring: %s",
                dobj->hdrs.file);
        return DECLINED;
    }

    /* Open the data file */
    if (dobj->disk_info.has_body) {
        flags = APR_READ | APR_BINARY;

(dobj->disk_info.header_only && !r->header_only) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00707)
                "HEAD request cached, non-HEAD requested, ignoring: %s",
                dobj->hdrs.file);
        apr_file_close(dobj->hdrs.fd);
        return DECLINED;
    };
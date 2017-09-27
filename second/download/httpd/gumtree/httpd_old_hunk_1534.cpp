        if (rc != APR_SUCCESS) {
            return DECLINED;
        }
    }
    else if (format != DISK_FORMAT_VERSION) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "cache_disk: File '%s' has a version mismatch. File had version: %d.",
                     dobj->hdrsfile, format);
        return DECLINED;
    }
    else {
        apr_off_t offset = 0;
        /* This wasn't a Vary Format file, so we must seek to the

ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "cache_disk: File '%s' has a version mismatch. File had version: %d.",
                     dobj->hdrsfile, format);
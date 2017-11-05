ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "disk_cache: File '%s' has a version mismatch. File had version: %d.",
                     dobj->hdrsfile, format);
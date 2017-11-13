ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
               "disk_cache: could not write out-headers to header file %s",
               dobj->hdrsfile);
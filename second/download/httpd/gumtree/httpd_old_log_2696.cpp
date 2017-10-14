ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                    "disk_cache: rename tempfile to varyfile failed: %s -> %s",
                    dobj->tempfile, dobj->hdrsfile);
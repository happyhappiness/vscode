ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
                    "disk_cache: could not create temp file %s",
                    dobj->tempfile);
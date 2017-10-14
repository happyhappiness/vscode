ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
                         "disk_cache: rename tempfile to datafile failed:"
                         " %s -> %s", dobj->tempfile, dobj->datafile);
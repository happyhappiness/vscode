ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
                 "disk_cache: Cannot open info header file %s",  dobj->datafile);
ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                 "disk_cache: recalling headers; but no header fd for %s", dobj->name);
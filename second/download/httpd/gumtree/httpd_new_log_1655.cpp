ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "Copying local SGL of len %d for group %s into cache",
                             tmp_local_sgl->len, dn);
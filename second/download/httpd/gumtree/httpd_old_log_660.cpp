ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, r,
                      "File does not exist: %s",
                      apr_pstrcat(r->pool, r->filename, r->path_info, NULL));
ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00128)
                          "File does not exist: %s",
                          apr_pstrcat(r->pool, r->filename, r->path_info, NULL));
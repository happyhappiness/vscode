ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
                          "Script timed out before returning headers: %s",
                          apr_filepath_name_get(r->filename));
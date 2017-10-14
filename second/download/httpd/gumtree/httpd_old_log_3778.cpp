ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "mod_asis: ap_pass_brigade failed for file %s", r->filename);
ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "WriteClient ap_pass_brigade failed: %s",
                          r->filename);
ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "ISAPI: WriteClient ap_pass_brigade "
                          "failed: %s", r->filename);
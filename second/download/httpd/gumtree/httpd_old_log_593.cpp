ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "ISAPI: ap_pass_brigade failed to "
                          "complete the response: %s ", r->filename);
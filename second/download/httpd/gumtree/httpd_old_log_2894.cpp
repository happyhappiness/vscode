ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                              "ISAPI: ServerSupport function "
                              "HSE_REQ_SEND_RESPONSE_HEADER "
                              "ap_pass_brigade failed: %s", r->filename);
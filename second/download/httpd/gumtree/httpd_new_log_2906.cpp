ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                              "ServerSupport function "
                              "HSE_REQ_SEND_RESPONSE_HEADER_EX "
                              "ap_pass_brigade failed: %s", r->filename);
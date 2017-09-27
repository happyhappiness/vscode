ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                         "proxy: read zero bytes, expecting"
                         " %" APR_OFF_T_FMT " bytes",
                         content_length);
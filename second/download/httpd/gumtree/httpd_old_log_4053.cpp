ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "send_http_connect: the forward proxy returned code is '%s'",
                             code_str);
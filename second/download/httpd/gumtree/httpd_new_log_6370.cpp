ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(10034)
                     "The mpm module (%s) is not supported by mod_http2. The mpm determines "
                     "how things are processed in your server. HTTP/2 has more demands in "
                     "this regard and the currently selected mpm will just not do. "
                     "This is an advisory warning. Your server will continue to work, but "
                     "the HTTP/2 protocol will be inactive.", 
                     h2_conn_mpm_name());
ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "Replacing host header '%s' with host '%s' given "
                          "in the request uri", host_header, repl);
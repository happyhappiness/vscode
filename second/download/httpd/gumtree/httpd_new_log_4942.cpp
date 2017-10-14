ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00124)
                              "Request exceeded the limit of %d internal "
                              "redirects due to probable configuration error. "
                              "Use 'LimitInternalRecursion' to increase the "
                              "limit if necessary. Use 'LogLevel debug' to get "
                              "a backtrace.", rlimit);
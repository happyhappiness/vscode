ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "setsockopt(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
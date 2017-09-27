ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "insecure SSL re-negotiation required, but "
                              "a pipelined request is present; keepalive "
                              "disabled");
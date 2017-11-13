ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                          "proxy: could not parse request Content-Length (%s)",
                          old_cl_val);
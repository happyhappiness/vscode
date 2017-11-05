ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01086)
                          "read more bytes of request body than expected "
                          "(got %" APR_OFF_T_FMT ", expected %" APR_OFF_T_FMT ")",
                          bytes_streamed, cl_val);
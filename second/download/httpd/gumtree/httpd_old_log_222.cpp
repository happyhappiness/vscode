ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, f->r,
                          "Requested content-length of %" APR_OFF_T_FMT 
                          " is larger than the configured limit"
                          " of %" APR_OFF_T_FMT, ctx->remaining, ctx->limit);
ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "apr_brigade_partition() failed on kept_body at %" APR_OFF_T_FMT, ctx->offset);
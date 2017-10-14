ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01415)
                      "apr_brigade_partition() failed on kept_body at %" APR_OFF_T_FMT, ctx->offset + readbytes);
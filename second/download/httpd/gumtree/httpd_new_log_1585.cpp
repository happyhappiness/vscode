ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, 
                            "Inflated content length of %" APR_OFF_T_FMT
                            " is larger than the configured limit"
                            " of %" APR_OFF_T_FMT, 
                            ctx->inflate_total, inflate_limit);
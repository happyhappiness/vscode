ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r,
                                      "Read content length of "
                                      "%" APR_OFF_T_FMT " is larger than the "
                                      "configured limit of %" APR_OFF_T_FMT,
                                      ctx->limit_used, ctx->limit);
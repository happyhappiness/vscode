ap_log_perror(APLOG_MARK, APLOG_TRACE1, APR_EINVAL, ctx->p,
                          "h2_request: head field '%s: %s' has invalid char %s", 
                          key, value, p);
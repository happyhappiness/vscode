ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                     "Heartmonitor: Failed to set APR_SO_REUSEADDR to 1 on socket.");
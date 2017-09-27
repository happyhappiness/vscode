ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ctx->s,
                     "Heartmonitor: malformed message from %pI",
                     from);
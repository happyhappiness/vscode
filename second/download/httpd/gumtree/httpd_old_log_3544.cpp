ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                             "Heartmonitor: Unable to read from file: %s", ctx->storage_path);
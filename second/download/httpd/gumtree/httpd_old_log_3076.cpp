ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s,
                     "Heartmonitor: %pI busy=%s ready=%s", from,
                     apr_table_get(tbl, "busy"), apr_table_get(tbl, "ready"));
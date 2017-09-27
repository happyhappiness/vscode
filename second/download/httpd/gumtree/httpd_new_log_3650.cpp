ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(02086)
                     "%pI busy=%s ready=%s", from,
                     apr_table_get(tbl, "busy"), apr_table_get(tbl, "ready"));
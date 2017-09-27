ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, ctx->owner, APLOGNO(03352)
                      "H2: failed to make connection to backend: %s",
                      ctx->p_conn->hostname);
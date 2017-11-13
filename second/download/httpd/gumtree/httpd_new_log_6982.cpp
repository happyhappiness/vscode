ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, s, APLOGNO(10019)
                         "Missing unique per-server context: %s (%pp:%pp) (no hchecks)",
                         s->server_hostname, s, ctx->s);
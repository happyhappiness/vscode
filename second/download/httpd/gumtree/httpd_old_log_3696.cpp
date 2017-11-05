ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: roundrobin index: %d (%d)",
                 ctx->index, (int)getpid());
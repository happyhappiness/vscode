ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(03248)
                     "Creating hc worker %pp for %s://%s:%d",
                     worker, worker->s->scheme, worker->s->hostname,
                     (int)port);
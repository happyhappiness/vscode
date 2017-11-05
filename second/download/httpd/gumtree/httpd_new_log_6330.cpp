ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(03311)
                     "Updating hc worker %pp for %s://%s:%d",
                     worker, worker->s->scheme, worker->s->hostname,
                     (int)port);
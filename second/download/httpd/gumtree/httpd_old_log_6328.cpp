ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(03311)
                     "Updating hc worker %s for %s://%s:%d",
                     wptr, worker->s->scheme, worker->s->hostname,
                     (int)port);
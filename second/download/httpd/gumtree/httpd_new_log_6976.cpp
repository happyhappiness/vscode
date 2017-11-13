ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, ctx->s,
                     "Response status %i for %s (%s): failed", r->status,
                     hc->s->name, worker->s->name);
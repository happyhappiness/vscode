ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01172)
                  "%s: worker (%s) rewritten to %s",
                  (*balancer)->s->name, (*worker)->s->name, *url);
ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "%s: found worker %s for %s",
                          (*worker)->s->scheme, (*worker)->s->name, *url);
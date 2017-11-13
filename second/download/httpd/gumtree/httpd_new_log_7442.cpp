ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02596)
                                  "RewriteRule '%s' and URI '%s' exceeded "
                                  "maximum number of rounds (%d) via the [N] flag", 
                                  p->pattern, r->uri, p->maxrounds);
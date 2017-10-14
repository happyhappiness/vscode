ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01169)
                      "%s: Unlock failed for pre_request",
                      (*balancer)->s->name);
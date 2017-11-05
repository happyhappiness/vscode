ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01168)
                              "%s: Unlock failed for pre_request",
                              (*balancer)->s->name);
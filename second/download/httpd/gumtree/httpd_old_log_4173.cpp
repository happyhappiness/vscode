ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: bytraffic selected worker \"%s\" : busy %" APR_SIZE_T_FMT,
                     mycandidate->name, mycandidate->s->busy);
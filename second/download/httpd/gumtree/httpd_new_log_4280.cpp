ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01210)
                     "proxy: bytraffic selected worker \"%s\" : busy %" APR_SIZE_T_FMT,
                     mycandidate->s->name, mycandidate->s->busy);
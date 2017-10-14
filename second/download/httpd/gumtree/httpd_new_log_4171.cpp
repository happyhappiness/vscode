ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01208)
                     "proxy: byrequests selected worker \"%s\" : busy %" APR_SIZE_T_FMT " : lbstatus %d",
                     mycandidate->s->name, mycandidate->s->busy, mycandidate->s->lbstatus);
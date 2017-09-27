ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01180)
                             "mutex creation of %s : %s failed", balancer_mutex_type,
                             balancer->s->sname);
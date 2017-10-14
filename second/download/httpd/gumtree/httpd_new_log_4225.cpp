ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01165)
                         "%s: Forcing recovery for worker (%s)",
                         balancer->s->name, (*worker)->s->hostname);
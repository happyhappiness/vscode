ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00897)
                              "cping/cpong failed to %pI (%s)",
                              worker->cp->addr, worker->s->hostname);
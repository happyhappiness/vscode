ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00892)
                      "got response from %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->s->hostname);
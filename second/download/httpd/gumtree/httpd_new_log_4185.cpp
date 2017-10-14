ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00868)
                      "request failed to %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->s->hostname);
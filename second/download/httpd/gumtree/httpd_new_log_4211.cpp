ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00893)
                      "dialog to %pI (%s) failed",
                      conn->worker->cp->addr,
                      conn->worker->s->hostname);
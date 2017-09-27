ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00878)
                      "read response failed from %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->s->hostname);
ap_log_perror(APLOG_MARK, APLOG_ERR, 0, conn->pool, APLOGNO(00923)
                      "Pooled connection 0x%pp for worker %s has been"
                      " already returned to the connection pool.", conn,
                      worker->s->name);
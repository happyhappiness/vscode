    }
    else {
        user = "anonymous";
        password = "apache-proxy@";
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01036)
                  "connecting %s to %s:%d", url, connectname, connectport);

    if (worker->s->is_address_reusable) {
        if (!worker->cp->addr) {
            if ((err = PROXY_THREAD_LOCK(worker->balancer)) != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, err, r, APLOGNO(01037) "lock");
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
        connect_addr = worker->cp->addr;
        address_pool = worker->cp->pool;
    }
